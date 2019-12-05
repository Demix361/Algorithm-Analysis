from func import create_table, dijkstra
from parser_v2 import get_stations
from graphviz import render


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
            print(path[i].name, ' (', path[i].branch, ') -> [', path_distance[i], '] -> ', end='', sep='')
        else:
            print(path[i].name, ' (', path[i].branch, ')', sep='')

    return path


def st_name(st):
    return '\"' + st.name + ' (' + st.branch + ')' + '\"'


def write_gv(fname, table, stations, colors):
    n = len(table)

    with open(fname, 'w') as f:
        f.write('graph mygraph {\n')

        for i in range(n - 1):
            for j in range(i + 1, n, 1):
                if table[i][j] != 0:
                    if stations[i].branch == stations[j].branch:
                        f.write(
                            '\t' + st_name(stations[i]) + ' -- ' + st_name(stations[j])
                            + ' [label = ' + str(table[i][j]) + ', color = ' +
                            colors[stations[i].branch] + ', style = bold];\n')
                    else:
                        f.write(
                            '\t' + st_name(stations[i]) + ' -- ' + st_name(stations[j])
                            + ' [label = ' + str(table[i][j]) + ', style = bold];\n')

        f.write('}')


def main():
    stations = get_stations('wiki.txt', 9, 'mck.txt', 8)
    table = create_table(stations)
    br_names = {'1': 'Сокольническая (красная)',
                '2': 'Замоскворецкая (зеленая)',
                '3': 'Арбатско-Покровская (синяя)',
                '4': 'Филёвская (голубая)',
                '5': 'Кольцевая (коричневая)',
                '6': 'Калужско-Рижская (оранжевая)',
                '7': 'Таганско-Краснопресненская (фиолетовая)',
                '8': 'Калининская (желтая)',
                '9': 'Серпуховско-Тимирязевская (серая)',
                '10': 'Люблинско-Дмитровская (салатовая)',
                '11А': 'Каховская (бирюзовая)',
                '12': 'Бутовская (серо-голубая)',
                '14': 'МЦК',
                '15': 'Некрасовская (розовая)',
                }
    br_colors = {'1': '\"#CD0506\"',
                 '2': '\"#0A6F20\"',
                 '3': '\"#072889\"',
                 '4': '\"#069CD3\"',
                 '5': '\"#7F0000\"',
                 '6': '\"#FF7F00\"',
                 '7': '\"#92007B\"',
                 '8': '\"#FFDD03\"',
                 '9': '\"#A2A5B4\"',
                 '10': '\"#8CCE3A\"',
                 '11А': '\"#C9EBE9\"',
                 '12': '\"#B2DAE7\"',
                 '14': '\"#F76093\"',
                 '15': '\"#D765A3\"',
                 }

    write_gv('metro_graph.gv', table, stations, br_colors)
    render('dot', 'png', 'metro_graph.gv')

    while True:
        options = []

        st_1_name = input('Станция отправления: ')

        for st in stations:
            if st.name.lower() == st_1_name.lower():
                options.append(st)

        if len(options) == 0:
            print('Станция с таким названием не найдена.')
        elif len(options) == 1:
            st_1 = options[0]
            break
        else:
            print('Есть несколько станций с таким названием: ')
            for i in range(len(options)):
                print(str(i + 1) + '. ' + options[i].name + ' - ' + br_names[options[i].branch])

            while True:
                ch = input('Выберите номер нужной станции: ')
                try:
                    ch = int(ch)
                    if 1 <= ch <= len(options):
                        st_1 = options[ch - 1]
                        break
                    else:
                        print('Неверный выбор, пожалуйста повторите ввод.')
                except ValueError:
                    print('Неверный выбор, пожалуйста повторите ввод.')
            break
    print()

    while True:
        options = []

        st_1_name = input('Станция прибытия: ')

        for st in stations:
            if st.name.lower() == st_1_name.lower():
                options.append(st)

        if len(options) == 0:
            print('Станция с таким названием не найдена.')
        elif len(options) == 1:
            st_2 = options[0]
            break
        else:
            print('Есть несколько станций с таким названием: ')
            for i in range(len(options)):
                print(str(i + 1) + '. ' + options[i].name + ' - ' + br_names[options[i].branch])

            while True:
                ch = input('Выберите номер нужной станции: ')
                try:
                    ch = int(ch)
                    if 1 <= ch <= len(options):
                        st_2 = options[ch - 1]
                        break
                    else:
                        print('Неверный выбор, пожалуйста повторите ввод.')
                except ValueError:
                    print('Неверный выбор, пожалуйста повторите ввод.')
            break
    print()

    distance, paths = dijkstra(table, stations.index(st_1))

    print_path(st_1, st_2, distance, paths, stations, table)


if __name__ == '__main__':
    main()
