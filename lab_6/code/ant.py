

class Ant:
    def __init__(self, node):
        self.cur_node = node
        self.visited = [node]


def ant_algorithm(graph, alpha, beta, q, ro, max_its):
    n = len(graph)
    pheromone = [[1 for j in range(n)] for i in range(n)]

    for it in range(max_its):
        ants = [Ant(i) for i in range(n)]

        for ant in ants:
            while len(ant.visited) != n:
                next_nodes = []
                prob_parts = []
                probs = []

                for i in range(n):
                    if i not in ant.visited:
                        next_nodes.append(i)

                for node in next_nodes:
                    prob_parts.append((pheromone[ant.cur_node][node] ** alpha) * ((1 / graph[ant.cur_node][node]) ** beta))

                for i in range(len(next_nodes)):
                    p = prob_parts[i] / sum(prob_parts)
                    probs.append(p)

                best_node = next_nodes[probs.index(max(probs))]

                pheromone[ant.cur_node][best_node] = (1 - ro) * pheromone[ant.cur_node][best_node] + q / graph[ant.cur_node][best_node]

                ant.cur_node = best_node
                ant.visited.append(best_node)

    return pheromone








