

def dijkstra(S, matrix):
    n = len(matrix)

    for i in range(len(matrix)):
        for j in range(len(matrix[i])):
            if matrix[i][j] == 0:
                matrix[i][j] = 1000000

    valid = [True] * n
    weight = [1000000] * n
    weight[S] = 0

    for i in range(n):
        min_weight = 1000001
        ID_min_weight = -1

        for i in range(n):
            if valid[i] and weight[i] < min_weight:
                min_weight = weight[i]
                ID_min_weight = i

        for i in range(n):
            if weight[ID_min_weight] + matrix[ID_min_weight][i] < weight[i]:
                weight[i] = weight[ID_min_weight] + matrix[ID_min_weight][i]
        valid[ID_min_weight] = False

    return weight
