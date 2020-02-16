from math import factorial
from random import randint
from itertools import permutations, product
from ant import ant_algorithm


def load_graph(fname):
    res = []

    with open(fname, 'r') as f:
        for line in f:
            nums = list(map(int, line.split()))
            res.append(nums)

    return res


def gen_graph(size):
    res = []

    for i in range(size):
        res.append([])
        for j in range(size):
            if i != j:
                res[-1].append(randint(1, 10))
            else:
                res[-1].append(100000)

    return res


def print_graph(graph):
    for i in range(len(graph)):
        for j in range(len(graph[0])):
            print(graph[i][j], end='  ')
        print()
    print()


def full_search(graph):
    n = len(graph)
    a = []

    for i in permutations([j for j in range(n)]):
        a.append(i)

    res_min = 100000000000
    comb_min = None
    res = 0

    for comb in a:
        res = 0
        for j in range(-1, n - 1, 1):
            res += graph[comb[j]][comb[j + 1]]
        if res < res_min:
            res_min = res
            comb_min = comb

    return res, comb_min



def main():
    #graph = load_graph('graph_2.txt')
    graph = gen_graph(4)
    print_graph(graph)

    print(full_search(graph))

    # size = 4, a = 1, b = 5, ro = 0.1, its = 7
    pheromone = ant_algorithm(graph, 1, 5, 5, 0.1, 7)

    print_graph(pheromone)



main()