from random import randint


def ind(stations, branch, number):
    i = 0

    for st in stations:
        if st.branch == branch and st.number == number:
            return i
        i += 1

    return None


def create_table(stations):
    n = len(stations)

    table = [[0 for j in range(n)] for i in range(n)]

    for i in range(n - 1):
        if stations[i].branch == stations[i + 1].branch and stations[i].branch != '4':
            cost = randint(1, 5)
            table[i][i + 1] = cost
            table[i + 1][i] = cost

    cost = randint(1, 5)
    table[ind(stations, '5', '01')][ind(stations, '5', '12')] = cost
    table[ind(stations, '5', '12')][ind(stations, '5', '01')] = cost

    cost = randint(1, 5)
    table[ind(stations, '14', '01')][ind(stations, '14', '31')] = cost
    table[ind(stations, '14', '31')][ind(stations, '14', '01')] = cost

    x = ind(stations, '4', '01')
    for i in range(6):
        cost = randint(1, 5)
        table[x][x + 1] = cost
        table[x + 1][x] = cost
        x += 1

    x = ind(stations, '4', '08')
    for i in range(5):
        cost = randint(1, 5)
        table[x][x + 1] = cost
        table[x + 1][x] = cost
        x += 1

    cost = randint(1, 5)
    table[ind(stations, '4', '07')][ind(stations, '4', '10')] = cost
    table[ind(stations, '4', '10')][ind(stations, '4', '07')] = cost

    for st in stations:
        for tr in st.transfers:
            for i in range(n):
                if tr[0] == stations[i].branch and tr[1] == stations[i].name:
                    cost = randint(1, 3)
                    table[i][ind(stations, st.branch, st.number)] = cost
                    table[ind(stations, st.branch, st.number)][i] = cost

    return table


def dijkstra(matrix, start):
    n = len(matrix)
    inf_num = 10000

    u = [False for i in range(n)]
    d = [inf_num for i in range(n)]
    d[start] = 0
    paths = [-1 for i in range(n)]

    for i in range(n):
        cur_d = inf_num + 1
        cur_p = -1

        for j in range(n):
            if not u[j] and d[j] < cur_d:
                cur_d = d[j]
                cur_p = j

        u[cur_p] = True

        for j in range(n):
            if matrix[cur_p][j] != 0:
                old_d = d[j]
                d[j] = min(d[j], d[cur_p] + matrix[cur_p][j])
                if d[j] != old_d:
                    paths[j] = cur_p
    return d, paths