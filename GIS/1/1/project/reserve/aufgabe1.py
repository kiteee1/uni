import argparse
import yaml
import os

# Custom PriorityQueue Class: Wird in allen Teilaufgaben verwendet
class PriorityQueue:
    def __init__(self):
        self.queue = []
        self.entry_finder = {}
        self.REMOVED = '<removed_task>'

    def push(self, priority, cost_so_far, city, path):
        if city in self.entry_finder:
            self.remove_task(city)
        entry = [priority, cost_so_far, city, path]
        self.entry_finder[city] = entry
        self.queue.append(entry)
        self._up_heap(len(self.queue) - 1)

    def remove_task(self, city):
        entry =  self.entry_finder.pop(city)
        entry[-2] = self.REMOVED

    def pop(self):
        while self.queue:
            entry = self.queue[0]
            end = self.queue.pop()
            if self.queue:
                self.queue[0] = end
                self._down_heap(0)
            if entry[-2] != self.REMOVED:
                del self.entry_finder[entry[-2]]
                return  entry[0], entry[1], entry[2], entry[3]
        raise ValueError("pop: PQ leer")

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
        return not self.entry_finder


def parse_arguments():
    parser = argparse.ArgumentParser()
    parser.add_argument('filename', type=str)
    return parser.parse_args()


def read_problem(filename):
    if not os.path.isfile(filename):
        raise ValueError(f"Input file '{filename}' does not exist")
    try:
        with open(filename, 'r') as file:
            data = yaml.safe_load(file)
        problem = data.get('problem', {})
        additional_info = data.get('additional_information', {})
        return problem, additional_info
    except Exception as e:
        raise ValueError(f"Error reading input file: {e}")


def build_graph(problem):
    graph = {}
    cities = problem.get('cities', [])
    for city in cities:
        city_key = f'city_{city}'
        city_info = problem.get(city_key, {})
        connections = city_info.get('connects_to', {})
        connections = {str(k): float(v) for k, v in connections.items()}
        graph[city] = connections
    return graph

# Teilaufgabe 1: h(n) = 0 (Uniform Cost Search)
def get_uniform_heuristic(graph):
    return {f'city_{city}': 0.0 for city in graph.keys()}

# Teilaufgabe 2: A* mit line_of_sight Heuristic
def get_line_of_sight_heuristic(additional_info):
    heuristic = {}
    for city_key, info in additional_info.items():
        heuristic_value = float(info.get('line_of_sight_distance', 0.0))
        heuristic[city_key] = heuristic_value
    return heuristic

# Teilaufgabe 3: A* mit line_of_sight und altitude_difference
def get_improved_heuristic(additional_info, goal_city):
    heuristic = {}
    goal_altitude = float(additional_info.get(f'city_{goal_city}', {}).get('altitude_difference', 0.0))
    for city_key, info in additional_info.items():
        line_of_sight = float(info.get('line_of_sight_distance', 0.0))
        altitude_difference = abs(float(info.get('altitude_difference', 0.0)) - goal_altitude)
        heuristic_value = line_of_sight + altitude_difference
        heuristic[city_key] = heuristic_value
    return heuristic


#A* Suche: Wird in allen Teilaufgaben verwendet
def a_star_search(graph, start, goal, heuristic):
    frontier = PriorityQueue()
    start_key = f'city_start_{start}'
    frontier.push(heuristic.get(start_key, 0.0), 0, start, [start])
    explored = {}
    expanded_nodes = 0

    while not frontier.is_empty():
        entry = frontier.pop()
        estimated_total_cost, cost_so_far, current_city, path = entry

        if current_city == goal:
            return cost_so_far, path, expanded_nodes

        if current_city not in explored or cost_so_far < explored[current_city]:
            explored[current_city] = cost_so_far
            expanded_nodes += 1
            for neighbor, neighbor_cost in graph.get(current_city, {}).items():
                total_cost_so_far = cost_so_far + neighbor_cost
                if neighbor_cost in explored and total_cost_so_far >= explored[neighbor]:
                    continue
                neighbor_key = f'city_{neighbor}'
                estimated_cost = total_cost_so_far + heuristic.get(neighbor_key, 0.0)
                frontier.push(estimated_cost, total_cost_so_far, neighbor, path + [neighbor])
    raise ValueError("Das Problem ist nicht loesbar")


def solve_teilaufgabe(additional_info, graph, start, goal, heuristic_function, output_filename):
    heuristic_params = heuristic_function.__code__.co_varnames[:heuristic_function.__code__.co_argcount]

    args = []
    if 'additional_info' in heuristic_params:
        args.append(additional_info)
    if 'graph' in heuristic_params:
        args.append(graph)
    if 'goal_city' in heuristic_params:
        args.append(goal)

    heuristic = heuristic_function(*args)
    total_cost, path, expanded_nodes = a_star_search(graph, start, goal, heuristic)

    output_data = {
        'solution': {
            'cost': total_cost,
            'expanded_nodes': expanded_nodes,
            'heuristic': heuristic,
            'path': path
        }
    }

    with open(output_filename, 'w') as outfile:
        yaml.dump(output_data, outfile, sort_keys=False)

def main():
    args = parse_arguments()
    problem_file = args.filename

    try:
        problem, additional_info = read_problem(problem_file)
        graph = build_graph(problem)
        start = problem.get('city_start')
        goal = problem.get('city_end')

        if start not in graph or goal not in graph:
            raise ValueError("Start or goal city not in the graph")



        # Teilaufgabe 1: h(n) = 0 (Uniform Cost Search)
        solve_teilaufgabe(
            additional_info, graph, start, goal,
            heuristic_function = get_uniform_heuristic,
            output_filename = 'aufgabe1-1.yaml'
        )

        # Teilaufgabe 2: A* mit line_of_sight Heuristic
        solve_teilaufgabe(
            additional_info, graph, start, goal,
            heuristic_function=get_line_of_sight_heuristic,
            output_filename='aufgabe1-2.yaml'
        )

        # Teilaufgabe 3: A* mit line_of_sight und altitude_difference
        solve_teilaufgabe(
            additional_info, graph, start, goal,
            heuristic_function=get_improved_heuristic,
            output_filename='aufgabe1-3.yaml'
        )


    except ValueError as ve:
        raise ValueError(str(ve))
    except Exception as e:
        raise ValueError(f"Unexpected Error: {e}")


if __name__ == '__main__':
    main()


