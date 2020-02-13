

class Transition:
    def __init__(self, state_1, state_2, symbols, sym_ins, direction):
        self.state_1 = state_1
        self.state_2 = state_2
        self.symbols = symbols
        self.sym_ins = sym_ins
        self.direction = direction


def date_ru_automat(word):
    instructions = [Transition(1, 2, ['0'], 'in', 'r'), # Первая цифра дня
                    Transition(1, 3, ['1', '2'], 'in', 'r'),
                    Transition(1, 4, ['3'], 'in', 'r'),
                    Transition(1, 1, ['0', '1', '2', '3'], 'not', 'r'),

                    Transition(2, 5, ['1', '2', '3', '4', '5', '6', '7', '8', '9'], 'in', 'r'), # Вторая цифра дня
                    Transition(3, 5, ['0', '1', '2', '3', '4', '5', '6', '7', '8', '9'], 'in', 'r'),
                    Transition(4, 5, ['0', '1'], 'in', 'r'),
                    Transition(2, 1, ['1', '2', '3', '4', '5', '6', '7', '8', '9'], 'not', 'r'),
                    Transition(3, 1, ['0', '1', '2', '3', '4', '5', '6', '7', '8', '9'], 'not', 'r'),
                    Transition(4, 1, ['0', '1'], 'not', 'r'),

                    Transition(5, 6, ['.', '-', '/'], 'in', 'r'), # Разделитель
                    Transition(5, 1, ['.', '-', '/'], 'not', 'r'),

                    Transition(6, 7, ['0'], 'in', 'r'), # Первая цифра месяца
                    Transition(6, 8, ['1'], 'in', 'r'),
                    Transition(6, 1, ['0', '1'], 'not', 'r'),

                    Transition(7, 9, ['1', '2', '3', '4', '5', '6', '7', '8', '9'], 'in', 'r'), # Вторая цифра месяца
                    Transition(8, 9, ['0', '1', '2'], 'in', 'r'),
                    Transition(7, 1, ['1', '2', '3', '4', '5', '6', '7', '8', '9'], 'not', 'r'),
                    Transition(8, 1, ['0', '1', '2'], 'not', 'r'),

                    Transition(9, 10, ['.', '-', '/'], 'in', 'r'),  # Разделитель
                    Transition(9, 1, ['.', '-', '/'], 'not', 'r'),

                    Transition(10, 11, ['1'], 'in', 'r'), # Первая цифра года
                    Transition(10, 12, ['2'], 'in', 'r'),
                    Transition(10, 1, ['1', '2'], 'not', 'r'),

                    Transition(11, 13, ['0', '1', '2', '3', '4', '5', '6', '7', '8', '9'], 'in', 'r'), # 1000 - 1999
                    Transition(13, 14, ['0', '1', '2', '3', '4', '5', '6', '7', '8', '9'], 'in', 'r'),
                    Transition(14, 20, ['0', '1', '2', '3', '4', '5', '6', '7', '8', '9'], 'in', 'r'),
                    Transition(11, 1, ['0', '1', '2', '3', '4', '5', '6', '7', '8', '9'], 'not', 'r'),
                    Transition(13, 1, ['0', '1', '2', '3', '4', '5', '6', '7', '8', '9'], 'not', 'r'),
                    Transition(14, 1, ['0', '1', '2', '3', '4', '5', '6', '7', '8', '9'], 'not', 'r'),

                    Transition(12, 15, ['0', '1'], 'in', 'r'), # 2000 - 2199
                    Transition(15, 16, ['0', '1', '2', '3', '4', '5', '6', '7', '8', '9'], 'in', 'r'),
                    Transition(16, 20, ['0', '1', '2', '3', '4', '5', '6', '7', '8', '9'], 'in', 'r'),
                    Transition(12, 1, ['0', '1'], 'not', 'r'),
                    Transition(15, 1, ['0', '1', '2', '3', '4', '5', '6', '7', '8', '9'], 'not', 'r'),
                    Transition(16, 1, ['0', '1', '2', '3', '4', '5', '6', '7', '8', '9'], 'not', 'r')

    ]

    res = run_automat(instructions, word)
    print(res)


def test_automat(word):
    instructions = [Transition(1, 2, ['a'], 'in', 'r'),
                    Transition(1, 1, ['a'], 'not', 'r'),
                    Transition(2, 3, ['b'], 'in', 'r'),
                    Transition(2, 1, ['b'], 'not', 'r'),
                    Transition(3, 4, ['c'], 'in', 's'),
                    Transition(3, 1, ['c'], 'not', 'r')]

    res = run_automat(instructions, word)
    print()
    print(res)


def run_automat(instructions, word):
    pos = 0
    end = len(word)
    state = 1
    start_pos = 0

    while pos != end:
        print(state, word[pos])

        tran = find_transition(state, word[pos], instructions)
        if tran is None:
            return start_pos, pos

        if tran.state_1 == 1 and tran.state_2 != 1:
            start_pos = pos

        if tran.direction == 'r':
            pos += 1
        elif tran.direction == 'l':
            pos -= 1

        state = tran.state_2

    return None


def find_transition(state, sym, instructions):
    for i in instructions:
        if i.state_1 == state:
            if i.sym_ins == 'in':
                if sym in i.symbols:
                    return i
            elif i.sym_ins == 'not':
                if sym not in i.symbols:
                    return i
    return None

date_ru_automat('hadufgildfg 30.12.2100 udgflidufghli aj d abc')