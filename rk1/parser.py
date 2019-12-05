class Station:
    def __init__(self):
        self.state = None
        self.branch = None
        self.number = None
        self.name = None
        self.transfers = []


# Возвращает массив с информацией о всех станциях, получает имя файла и количество строк с данными
def parse_wiki(fname, line_amount):
    info = []
    i = 0

    with open(fname, 'r') as f:
        for line in f:
            if i == 0:
                st = Station()

            if i == 0:
                if len(line) == 3:
                    st.state = 'open'
                else:
                    st.state = 'closed'
            elif i == 1:
                d = line[line.find('icon'):]
                s = d.split('}}{{')
                st.branch = s[0].split('|')[1]
                st.number = s[1][3:5]
            elif i == 2:
                if line[2] == '{':
                    opt_1 = line.find('}')
                    opt_2 = line[9:].find('|')
                    if opt_2 == -1:
                        opt_2 = 100000
                    else:
                        opt_2 += 9

                    end = min(opt_1, opt_2)
                    st.name = line[9:end]
                else:
                    opt_1 = line.find(']')
                    opt_2 = line.find(' (')
                    if opt_2 == -1:
                        opt_2 = 100000

                    end = min(opt_1, opt_2)
                    st.name = line[4:end]
            elif i == 4:
                a = line.find('{')
                if a != -1:
                    if line.find(' | ') != -1:
                        b = line[line.find(' | ') + 3:]
                    else:
                        b = line[1:]

                    c = b.split('}}')[:-1]

                    for tr in c:
                        tr = tr[tr.find('|') + 1:]
                        br = tr[:tr.find('|')]

                        tr = tr[tr.find('|'):]
                        while tr[0] == '|':
                            tr = tr[1:]

                        opt_1 = tr.find('|')
                        opt_2 = tr.find(' (')

                        if opt_1 == -1 and opt_2 == -1:
                            tr_name = tr
                        elif opt_1 == -1:
                            tr_name = tr[:opt_2]
                        elif opt_2 == -1:
                            tr_name = tr[:opt_1]
                        else:
                            tr_name = tr[:min(opt_1, opt_2)]

                        st.transfers.append((br, tr_name))

            i += 1

            if i == line_amount:
                i = 0
                info.append(st)

    return info


def print_stations(stations):
    for st in stations:
        print(st.state)
        print(st.branch)
        print(st.number)
        print(st.name)
        print(st.transfers)
        print('------------------------------------------------------------------------')


def print_station(station):
    print(station.state)
    print(station.branch)
    print(station.number)
    print(station.name)
    print(station.transfers)
    print('------------------------------------------------------------------------')


def get_branches(stations):
    branches = []

    for st in stations:
        if st.branch not in branches:
            branches.append(st.branch)

    return branches


def get_stations(f_mtr, size_mtr, f_mck, size_mck):
    stations = parse_wiki(f_mtr, size_mtr)
    mck = parse_wiki(f_mck, size_mck)
    stations += mck

    # Нужно удалить 11, 8А, 13, КСЛ ветки и все пересадки на эти ветки
    new_stations = []
    for st in stations:
        if st.branch != '11' and st.branch != '8А' and st.branch != '13' and st.branch != 'КСЛ':
            new_stations.append(st)

    stations = new_stations

    for st in stations:
        new_transfers = []
        for tr in st.transfers:
            if tr[0] != '11' and tr[0] != '8А' and tr[0] != 'КСЛ' and tr[0] != '13':
                new_transfers.append(tr)
        st.transfers = new_transfers
