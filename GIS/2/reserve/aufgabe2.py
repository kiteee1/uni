from wumpus import Actions, Percepts, Orientation

class PriorityQueue:
    def __init__(self):
        self.queue = []

    def push(self, priority, cost_so_far, city, path):
        entry = [priority, cost_so_far, city, path]
        self.queue.append(entry)
        self._up_heap(len(self.queue) - 1)

    def pop(self):
        if not self.queue:
            raise ValueError("pop: PQ leer (empty)")
        top = self.queue[0]
        last = self.queue.pop()
        if self.queue:
            self.queue[0] = last
            self._down_heap(0)
        return top

    def _up_heap(self, idx):
        item = self.queue[idx]
        while idx > 0:
            parent = (idx - 1) >> 1
            parent_item = self.queue[parent]
            if item[0] >= parent_item[0]:
                break
            self.queue[idx] = parent_item
            idx = parent
        self.queue[idx] = item

    def _down_heap(self, idx):
        item = self.queue[idx]
        n = len(self.queue)
        child = 2 * idx + 1
        while child < n:
            right = child + 1
            if right < n and self.queue[right][0] < self.queue[child][0]:
                child = right
            if self.queue[child][0] >= item[0]:
                break
            self.queue[idx] = self.queue[child]
            idx = child
            child = 2 * idx + 1
        self.queue[idx] = item

    def is_empty(self):
        return len(self.queue) == 0

def manhattan_heuristic(a, b):
    return abs(a[0] -b[0]) + abs(a[1] - b[1])


def a_star_search(start, goal, neighbors_fn, cost_fn, heuristic_fn):
    frontier = PriorityQueue()
    g_start = 0
    h_start = heuristic_fn(start, goal)
    frontier.push(priority=h_start, cost_so_far=g_start, city=start, path=[start])
    explored = {}

    while not frontier.is_empty():
        f_val, cost_so_far, current, path = frontier.pop()

        if current == goal:
            return cost_so_far, path

        if current in explored and cost_so_far > explored[current]:
            continue

        explored[current] = cost_so_far

        for neighbor in neighbors_fn(current):
            step_cost = cost_fn(current, neighbor)
            new_g = cost_so_far + step_cost
            if (neighbor not in explored) or (new_g < explored[neighbor]):
                new_f = new_g + heuristic_fn(neighbor, goal)
                new_path = path + [neighbor]
                frontier.push(priority=new_f, cost_so_far=new_g, city=neighbor, path=new_path)
    raise ValueError("No path found by A*")



class Agent:
    def __init__(self, size=(4,4)):
        self.size = size
        self.width, self.height = size
        self.reset_knowledge()

    def reset_knowledge(self):
        self.pos = (0, 0)
        self.orientation = Orientation.NORTH

        self.has_gold = False
        self.has_arrow = True

        self.observations = {}

        self.visited = set()

        self.action_plan = []

        self.consistent_worlds = self._initialize_worlds()

        self.visited.add((0, 0))
        self.observations[(0,0)] = (False, False)

    def new_episode(self):
        self.reset_knowledge()

    def get_action(self, percept, reward):
        if self.action_plan:
            return self.action_plan.pop(0)

        self._update_knowledge(percept)

        if percept[Percepts.GLITTER] == 1:
            self.has_gold = True
            return Actions.GRAB

        if self.has_gold and self.pos == (0,0):
            return Actions.CLIMB

        if percept[Percepts.SCREAM] == 1:
            new_worlds = []
            for (pitSet, wPos) in self.consistent_worlds:
                new_worlds.append((pitSet, None))
            self.consistent_worlds = self._filter_inconsistent(new_worlds)

        if self.has_arrow:
            shoot_plan = self._maybe_shoot()
            if shoot_plan:
                self.action_plan = shoot_plan
                return self.action_plan.pop(0)

        next_target = self._pick_safe_unvisited()

        if next_target is None:
            if self.pos == (0,0):
                return Actions.CLIMB
            self.action_plan = self._plan_path(self.pos, (0,0))
            if not self.action_plan:
                return Actions.CLIMB
            return self.action_plan.pop(0)

        self.action_plan = self._plan_path(self.pos, next_target)
        if not self.action_plan:
            return Actions.CLIMB

        return self.action_plan.pop(0)


    def _update_knowledge(self, percept):
        x, y = self.pos

        stench = bool(percept[Percepts.STENCH])
        breeze = bool(percept[Percepts.BREEZE])
        bump = bool(percept[Percepts.BUMP])

        if bump: pass

        self.visited.add((x, y))
        self.observations[(x, y)] = (stench, breeze)

        if not breeze:
            for nx, ny in self._neighbors(x, y):
                self._mark_square_pitfree(nx, ny)
        if not stench:
            for nx, ny in self._neighbors(x, y):
                self._mark_square_wumpusfree(nx, ny)


        self.consistent_worlds = self._filter_inconsistent(self.consistent_worlds)

    def _mark_square_pitfree(self, x, y):
        new_worlds = []
        for (pitSet, wPos) in self.consistent_worlds:
            if (x, y) in pitSet:
                new_pitset = set(pitSet)
                new_pitset.remove((x, y))
                new_worlds.append((frozenset(new_pitset), wPos))
            else:
                # no change needed
                new_worlds.append((pitSet, wPos))
        self.consistent_worlds = self._filter_inconsistent(new_worlds)

    def _mark_square_wumpusfree(self, x, y):
        new_worlds = []
        for (pitSet, wPos) in self.consistent_worlds:
            if wPos == (x, y):
                continue
            new_worlds.append((pitSet, wPos))
        self.consistent_worlds = self._filter_inconsistent(new_worlds)

    def _initialize_worlds(self):
        squares = []

        for x in range(self.width):
            for y in range(self.height):
                if (x,y) != (0,0):
                    squares.append((x,y))
        n = len(squares)

        all_worlds = []
        for mask in range(1<<n):
            pit_list = []
            for i in range(n):
                if (mask & (1<<i)) !=0:
                    pit_list.append(squares[i])
            pit_set = frozenset(pit_list)

            free_squares = []
            for sq in squares:
                if sq not in pit_set:
                    free_squares.append(sq)

            for wSq in free_squares:
                all_worlds.append((pit_set, wSq))

        return all_worlds

    def _filter_inconsistent(self, world_list):
        new_list = []
        for (pitSet, wPos) in world_list:
            if (0,0) in pitSet:
                continue
            if wPos == (0,0):
                continue

            consistent = True
            for (sq, (stench, breeze)) in self.observations.items():
                if sq in pitSet:
                    consistent = False
                    break
                if wPos is not None:
                    dist = abs(sq[0]-wPos[0]) + abs(sq[1] - wPos[1])
                    stench_should = (dist <= 1)
                else:
                    stench_should = False

                if stench and not stench_should:
                    consistent = False
                    break
                if (not stench) and stench_should:
                    consistent = False
                    break

                neighbors = self._neighbors(sq[0], sq[1])
                breeze_should = False
                for nb in neighbors:
                    if nb in pitSet:
                        breeze_should = True
                        break
                if breeze and not breeze_should:
                    consistent = False
                    break
                if (not breeze) and breeze_should:
                    consistent = False
                    break

            if consistent:
                new_list.append((pitSet, wPos))
        return new_list

    def _neighbors(self, x, y):
        candidates = [(x + 1, y), (x - 1, y), (x, y + 1), (x, y - 1)]
        valid = []
        for (xx, yy) in candidates:
            if 0 <= xx < self.width and 0 <= yy < self.height:
                valid.append((xx, yy))
        return valid

    def _is_square_safe_in_all_worlds(self, sq):
        for (pitSet, wPos) in self.consistent_worlds:
            if sq in pitSet:
                return False
            if wPos == sq:
                return False
        return True

    def _pick_safe_unvisited(self):
        candidates = []
        for xx in range(self.width):
            for yy in range(self.height):
                if (xx, yy) not in self.visited:
                    if self._is_square_safe_in_all_worlds((xx,yy)):
                        candidates.append((xx, yy))
        if not candidates:
            return None

        x0, y0 = self.pos
        best_sq = None
        best_dist = 999
        for (cx, cy) in candidates:
            dist = abs(cx - x0) + abs(cy - y0)
            if dist < best_dist:
                best_dist = dist
                best_sq = (cx, cy)
        return best_sq


    def _maybe_shoot(self):
        if not self.has_arrow:
            return None

        if not self.consistent_worlds:
            return None

        first = True
        w_set = set()

        for(pitSet, wPos) in self.consistent_worlds:
            if wPos is None:
                return None
            if first:
                w_set =  {wPos}
                first = False
            else:
                if wPos in w_set:
                    w_set = { wPos }
                else:
                    w_set = set()
            if not w_set:
                return None

        if len(w_set) != 1:
            return None
        (wx, wy) = list(w_set)[0]
        (cx, cy) = self.pos
        if (wx != cx) and (wy != cy):
            return None

        plan = []
        desired = None
        if wy==cy:
            if wx>cx:
                desired = Orientation.EAST
            elif wx<cx:
                desired = Orientation.WEST
        else:
            if wy>cy:
                desired = Orientation.NORTH
            else:
                desired = Orientation.SOUTH

        if (desired is not None) and (desired !=self.orientation):
            plan += self._turn_to_orientation(self.orientation, desired)
        plan.append(Actions.SHOOT)
        self.has_arrow = False
        return plan



    def _plan_path(self, start, goal):
        def neighbors_fn(s):
            x, y = s
            nbrs = []
            # Check each direction carefully
            if x + 1 < self.width:
                if self._is_square_safe_in_all_worlds((x + 1, y)):
                    nbrs.append((x + 1, y))
            if x - 1 >= 0:
                if self._is_square_safe_in_all_worlds((x - 1, y)):
                    nbrs.append((x - 1, y))
            if y + 1 < self.height:
                if self._is_square_safe_in_all_worlds((x, y + 1)):
                    nbrs.append((x, y + 1))
            if y - 1 >= 0:
                if self._is_square_safe_in_all_worlds((x, y - 1)):
                    nbrs.append((x, y - 1))
            return nbrs
        def cost_fn(u, v):
            return 1

        try:
            cost_so_far, path_positions = a_star_search(
                start, goal, neighbors_fn, cost_fn, manhattan_heuristic
            )
        except ValueError:
            return []

        actions = self._positions_to_actions(path_positions)
        return actions

    def _positions_to_actions(self, positions):
        actions = []
        curr_pos = self.pos
        curr_ori = self.orientation

        for i in range(1, len(positions)):
            nx, ny = positions[i]
            dx = nx - curr_pos[0]
            dy = ny - curr_pos[1]

            desired_orient = None
            if dx == 1: desired_orient = Orientation.EAST
            elif dx == -1: desired_orient = Orientation.WEST
            elif dy == 1: desired_orient = Orientation.NORTH
            else: desired_orient = Orientation.SOUTH

            turn_seq = self._turn_to_orientation(curr_ori, desired_orient)
            actions += turn_seq

            actions.append(Actions.FORWARD)

            curr_ori = desired_orient
            curr_pos = (nx, ny)

        self.pos = curr_pos
        self.orientation = curr_ori
        return actions

    def _turn_to_orientation(self, current, target):
        actions = []

        while current != target:
            diff = (target - current) % 4
            if diff == 1:
                actions.append(Actions.RIGHT)
                current = (current + 1) % 4
            elif diff == 3:
                actions.append(Actions.LEFT)
                current = (current - 1) % 4
            else:
                actions.append(Actions.RIGHT)
                current = (current + 1) % 4
        return actions

