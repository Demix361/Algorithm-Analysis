from random import randint


# Алгоритм Дийкстры
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


# Добавляет в массив соединения между станциями одной ветки и их стоимость
def add_branch(scheme, branch):
    for i in range(len(branch) - 1):
        scheme.append((branch[i], branch[i + 1], randint(2, 4)))


# Добавляет в массив соединения между станциями одной кольцевой ветки и их стоимость
def add_loop(scheme, branch):
    for i in range(len(branch) - 1):
        scheme.append((branch[i], branch[i + 1], randint(2, 4)))
    scheme.append((branch[-1], branch[0], randint(2, 4)))


# Возвращает массив с названиями станций одной ветки
def branch_names(name, length):
    return [name + '_' + str(i + 1) for i in range(length)]


# Пишет граф в gv файл
def write_gv(fname, table, stations):
    n = len(table)

    with open(fname, 'w') as f:
        f.write('graph mygraph {\n')

        for i in range(n - 1):
            for j in range(i + 1, n, 1):
                if table[i][j] != 0:
                    if stations[i][:stations[i].find('_')] == stations[j][:stations[j].find('_')]:
                        f.write(
                            '\t' + stations[i] + ' -- ' + stations[j] + ' [label = ' + str(table[i][j]) + ', color = ' +
                            stations[i][:stations[i].find('_')] + ', style = bold];\n')
                    else:
                        f.write(
                            '\t' + stations[i] + ' -- ' + stations[j] + ' [label = ' + str(
                                table[i][j]) + ', style = bold];\n')

        f.write('}')


# Возвращает граф в виде матрицы и названия станций
def create_metro():
    scheme = []

    red_names = branch_names('red', 26)
    green_names = branch_names('green', 24)
    blue_names = branch_names('blue', 22)
    violet_names = branch_names('violet', 23)
    orange_names = branch_names('orange', 24)
    brown_names = branch_names('brown', 12)
    grey_names = branch_names('grey', 25)

    add_branch(scheme, red_names)
    add_branch(scheme, green_names)
    add_branch(scheme, blue_names)
    add_branch(scheme, violet_names)
    add_branch(scheme, orange_names)
    add_branch(scheme, grey_names)
    add_loop(scheme, brown_names)

    scheme.append((red_names[13], brown_names[0], 1))
    scheme.append((red_names[15], blue_names[12], 1))
    scheme.append((red_names[16], blue_names[13], 1))
    scheme.append((red_names[16], green_names[12], 1))
    scheme.append((red_names[17], violet_names[11], 1))
    scheme.append((red_names[18], orange_names[14], 1))
    scheme.append((red_names[20], brown_names[6], 1))

    scheme.append((green_names[10], brown_names[9], 1))
    scheme.append((green_names[11], orange_names[12], 1))
    scheme.append((green_names[12], blue_names[13], 1))
    scheme.append((green_names[13], violet_names[12], 1))
    scheme.append((green_names[15], brown_names[3], 1))

    scheme.append((blue_names[10], brown_names[1], 1))
    scheme.append((blue_names[14], brown_names[7], 1))

    scheme.append((violet_names[9], brown_names[8], 1))
    scheme.append((violet_names[10], orange_names[13], 1))
    scheme.append((violet_names[13], brown_names[2], 1))

    scheme.append((orange_names[11], brown_names[11], 1))
    scheme.append((orange_names[16], brown_names[5], 1))

    scheme.append((grey_names[11], brown_names[10], 1))
    scheme.append((grey_names[13], red_names[15], 1))
    scheme.append((grey_names[13], blue_names[12], 1))
    scheme.append((grey_names[14], green_names[13], 1))
    scheme.append((grey_names[14], violet_names[12], 1))
    scheme.append((grey_names[16], brown_names[4], 1))

    stations = red_names + green_names + blue_names + violet_names + orange_names + brown_names + grey_names

    n = len(stations)
    table = [[0 for j in range(n)] for i in range(n)]

    for i in range(len(scheme)):
        pair = scheme[i]

        for j in range(len(stations)):
            if stations[j] == pair[0]:
                ind_1 = j
                break

        for j in range(len(stations)):
            if stations[j] == pair[1]:
                ind_2 = j
                break

        table[ind_1][ind_2] = pair[2]
        table[ind_2][ind_1] = pair[2]

    return table, stations


def print_path(beg, end, distance, paths, stations, table):
    path = [end]
    path_distance = []

    cur = paths[stations.index(end)]
    while cur != stations.index(beg):
        path.append(stations[cur])
        cur = paths[cur]

    path.append(beg)
    path = path[::-1]

    for i in range(len(path) - 1):
        path_distance.append(table[stations.index(path[i])][stations.index(path[i + 1])])

    print('Время маршрута:', distance[stations.index(end)])
    print('Маршрут:')

    for i in range(len(path)):
        if i != len(path) - 1:
            print(path[i], ' -> [', path_distance[i], '] -> ', end='', sep='')
        else:
            print(path[i])

    return path


def main():
    table, stations = create_metro()
    write_gv('metro_graph.gv', table, stations)

    beg = input('Откуда: ')
    end = input('Куда: ')

    distance, paths = dijkstra(table, stations.index(beg))

    print_path(beg, end, distance, paths, stations, table)


if __name__ == '__main__':
    main()
