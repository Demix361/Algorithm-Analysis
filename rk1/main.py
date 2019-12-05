
from func import create_table, dijkstra
from parser import get_stations


def main():
    stations = get_stations('wiki.txt', 9, 'mck.txt', 8)
    table = create_table(stations)

    while True:
        options = []

        st_1 = input('Станция отправления: ')

        for st in stations:
            if st.name.lower() == st_1.lower():
                options.append(st)

        print(len(options))

    distance, paths = dijkstra(table, 7)
    print(distance)
    print(paths)


if __name__ == '__main__':
    main()