import numpy as np
from wumpus import Actions, Percepts, Orientation

class PriorityQueue:
    def __init__(self):
        self.queue = []

    def push(self, priority, cost_so_far, state, path):
        entry = [priority, cost_so_far, state, path]
        self.queue.append(entry)
        self._up_heap(len(self.queue) - 1)

    def pop(self):
        if not self.queue:
            raise ValueError("pop from empty PQ")
        top = self.queue[0]
        last = self.queue.pop()
        if self.queue:
            self.queue[0] = last
            self._down_heap(0)
        return top

    def is_empty(self):
        return len(self.queue)==0

    def _up_heap(self, idx):
        item = self.queue[idx]
        while idx>0:
            parent = (idx-1)>>1
            parent_item = self.queue[parent]
            if item[0]>=parent_item[0]:
                break
            self.queue[idx]=parent_item
            idx=parent
        self.queue[idx]=item

    def _down_heap(self, idx):
        item=self.queue[idx]
        n=len(self.queue)
        child=2*idx+1
        while child<n:
            right=child+1
            if right<n and self.queue[right][0]<self.queue[child][0]:
                child=right
            if self.queue[child][0]>=item[0]:
                break
            self.queue[idx]=self.queue[child]
            idx=child
            child=2*idx+1
        self.queue[idx]=item

def a_star_search(start, goal, neighbors_fn, cost_fn, heuristic_fn):
    pq = PriorityQueue()
    g_start=0
    h_start=heuristic_fn(start, goal)
    pq.push(h_start,g_start,start,[start])
    best_g={}

    while not pq.is_empty():
        f_val,g_val,cur, path = pq.pop()
        if cur==goal:
            return g_val,path
        if cur in best_g and g_val>best_g[cur]:
            continue
        best_g[cur]=g_val

        for nbr in neighbors_fn(cur):
            new_g=g_val+cost_fn(cur,nbr)
            if (nbr not in best_g) or (new_g<best_g[nbr]):
                f_new=new_g+heuristic_fn(nbr,goal)
                pq.push(f_new,new_g,nbr,path+[nbr])

    raise ValueError("No path found by A*")

def manhattan_heuristic(a,b):
    return abs(a[0]-b[0]) + abs(a[1]-b[1])

class Agent:
    def __init__(self, size=(4,4)):
        self.size=size
        self.width,self.height=size
        self.reset_knowledge()

    def reset_knowledge(self):
        self.pos=(0,0)
        self.orientation=Orientation.NORTH
        self.has_gold=False
        self.has_arrow=True

        self.possible_pit=np.ones((self.width,self.height),dtype=bool)
        self.possible_wumpus=np.ones((self.width,self.height),dtype=bool)

        self.possible_pit[0,0]=False
        self.possible_wumpus[0,0]=False

        self.visited=set()
        self.visited.add((0,0))

        self.action_plan=[]

    def new_episode(self):
        self.reset_knowledge()

    def get_action(self, percept, reward):
        if self.action_plan:
            return self.action_plan.pop(0)

        self._update_knowledge(percept)

        if percept[Percepts.GLITTER]==1:
            self.has_gold=True
            return Actions.GRAB

        if self.has_gold and self.pos==(0,0):
            return Actions.CLIMB

        if percept[Percepts.SCREAM]==1:
            self.possible_wumpus[:,:]=False

        if self.has_arrow:
            shoot_plan=self._maybe_shoot(percept)
            if shoot_plan:
                self.action_plan=shoot_plan
                return self.action_plan.pop(0)

        target=self._pick_safe_unvisited()
        if target is None:
            if self.pos==(0,0):
                return Actions.CLIMB
            self.action_plan=self._plan_path(self.pos,(0,0))
            if not self.action_plan:
                return Actions.CLIMB
            return self.action_plan.pop(0)

        self.action_plan=self._plan_path(self.pos,target)
        if not self.action_plan:
            return Actions.CLIMB
        return self.action_plan.pop(0)

    def _neighbors(self,x,y):
        res=[]
        if x+1<self.width:  res.append((x+1,y))
        if x-1>=0:          res.append((x-1,y))
        if y+1<self.height: res.append((x,y+1))
        if y-1>=0:          res.append((x,y-1))
        return res

    def _update_knowledge(self, percept):
        x,y=self.pos
        stench=(percept[Percepts.STENCH]==1)
        breeze=(percept[Percepts.BREEZE]==1)
        bump=(percept[Percepts.BUMP]==1)

        self.visited.add((x,y))

        if not breeze:
            for (nx,ny) in self._neighbors(x,y):
                self.possible_pit[nx,ny]=False
        else:
            neighbors=self._neighbors(x,y)
            unknown_nbrs=[(nx,ny) for (nx,ny) in neighbors if self.possible_pit[nx,ny]]
            if len(unknown_nbrs)==1:
                # must be a pit
                pitX,pitY=unknown_nbrs[0]
                self._mark_as_pit(pitX,pitY)

        if not stench:
            for (nx,ny) in self._neighbors(x,y):
                self.possible_wumpus[nx,ny]=False
        else:
            neighbors=self._neighbors(x,y)
            unknown_w_nbrs=[(nx,ny) for (nx,ny) in neighbors if self.possible_wumpus[nx,ny]]
            if len(unknown_w_nbrs)==1:
                wX,wY=unknown_w_nbrs[0]
                self._mark_as_wumpus(wX,wY)

        self.possible_pit[x,y]=False
        self.possible_wumpus[x,y]=False

    def _mark_as_pit(self, px,py):
        self.possible_pit[px,py]=True
        self.possible_wumpus[px,py]=False

    def _mark_as_wumpus(self, wx,wy):
        self.possible_wumpus[wx,wy]=True
        self.possible_pit[wx,wy]=False

    def _maybe_shoot(self, percept):
        stench=(percept[Percepts.STENCH]==1)
        if not stench: return None
        if not self.has_arrow: return None

        front=self._square_in_front()
        if front is None: return None
        fx,fy=front
        if 0<=fx<self.width and 0<=fy<self.height:
            if self.possible_wumpus[fx,fy]:
                plan=[]
                desired=self._orientation_to(front)
                if desired!=self.orientation:
                    plan+=self._turn_to_orientation(self.orientation, desired)
                plan.append(Actions.SHOOT)
                self.has_arrow=False
                return plan
        return None

    def _square_in_front(self):
        x,y=self.pos
        if self.orientation==Orientation.NORTH:
            return (x,y+1)
        if self.orientation==Orientation.SOUTH:
            return (x,y-1)
        if self.orientation==Orientation.EAST:
            return (x+1,y)
        return (x-1,y)

    def _orientation_to(self, sq):
        x0,y0=self.pos
        dx=sq[0]-x0
        dy=sq[1]-y0
        if dx==1:   return Orientation.EAST
        if dx==-1:  return Orientation.WEST
        if dy==1:   return Orientation.NORTH
        return Orientation.SOUTH

    def _pick_safe_unvisited(self):
        (cx,cy)=self.pos
        best_dist=999999
        best_sq=None
        for xx in range(self.width):
            for yy in range(self.height):
                if (xx,yy) not in self.visited:
                    if (not self.possible_pit[xx,yy]) and (not self.possible_wumpus[xx,yy]):
                        dist=abs(xx-cx)+abs(yy-cy)
                        if dist<best_dist:
                            best_dist=dist
                            best_sq=(xx,yy)
        return best_sq

    def _plan_path(self, start, goal):
        def neighbors_fn(s):
            xx,yy=s
            result=[]
            if xx+1<self.width:
                if (not self.possible_pit[xx+1,yy]) and (not self.possible_wumpus[xx+1,yy]):
                    result.append((xx+1,yy))
            if xx-1>=0:
                if (not self.possible_pit[xx-1,yy]) and (not self.possible_wumpus[xx-1,yy]):
                    result.append((xx-1,yy))
            if yy+1<self.height:
                if (not self.possible_pit[xx,yy+1]) and (not self.possible_wumpus[xx,yy+1]):
                    result.append((xx,yy+1))
            if yy-1>=0:
                if (not self.possible_pit[xx,yy-1]) and (not self.possible_wumpus[xx,yy-1]):
                    result.append((xx,yy-1))
            return result

        def cost_fn(u,v):
            return 1

        try:
            cost_val, squares_path=a_star_search(start, goal, neighbors_fn, cost_fn, manhattan_heuristic)
        except ValueError:
            return []
        return self._positions_to_actions(squares_path)

    def _positions_to_actions(self, squares_path):
        actions=[]
        curr_pos=self.pos
        curr_ori=self.orientation

        for i in range(1,len(squares_path)):
            (nx,ny)=squares_path[i]
            dx=nx-curr_pos[0]
            dy=ny-curr_pos[1]
            desired=None
            if dx==1:   desired=Orientation.EAST
            elif dx==-1:desired=Orientation.WEST
            elif dy==1: desired=Orientation.NORTH
            else:       desired=Orientation.SOUTH

            # turn
            actions+=self._turn_to_orientation(curr_ori, desired)
            # forward
            actions.append(Actions.FORWARD)

            curr_pos=(nx,ny)
            curr_ori=desired
            self.visited.add(curr_pos)
            self.possible_pit[nx,ny]=False
            self.possible_wumpus[nx,ny]=False

        self.pos=curr_pos
        self.orientation=curr_ori
        return actions

    def _turn_to_orientation(self, current, target):
        acts=[]
        while current!=target:
            diff=(target-current)%4
            if diff==1:
                acts.append(Actions.RIGHT)
                current=(current+1)%4
            elif diff==3:
                acts.append(Actions.LEFT)
                current=(current-1)%4
            else:
                acts.append(Actions.RIGHT)
                current=(current+1)%4
        return acts
