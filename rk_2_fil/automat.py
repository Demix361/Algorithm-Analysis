

# Класс инструкции автомата
class Transition:
    def __init__(self, state_1, state_2, symbols, sym_ins, direction):
        self.state_1 = state_1
        self.state_2 = state_2
        self.symbols = symbols
        self.sym_ins = sym_ins
        self.direction = direction


def alph(abc, without=None):
    res = []

    for a in abc:
        if without:
            if a not in without:
                res.append(a)
        else:
            res.append(a)

    return res


# Автомат для поиска даты в формате dd.mm.yyyy
def suff_automat(text):
    text = text.lower()
    abc_str = 'йцукенгшщзхъфывапролджэячсмитьбюё'
    abc = alph(abc_str)
    beta = ['а', 'я', 'в', 'ш', 'у', 'ю']

    f = 100


    instructions = [
        Transition(1, 2, abc, 'in', 'r'),  # Хотя бы 1 буква
        Transition(1, 1, abc, 'not', 'r'),

        Transition(2, 2, alph(abc_str, beta), 'in', 'r'),  # не первая буква суффиксов
        Transition(2, 1, abc, 'not', 'r'),  # не буква
        Transition(2, 3, ['а'], 'in', 'r'),  # а - первая буква суффикса
        Transition(2, 6, ['я'], 'in', 'r'),  # я - первая буква суффикса
        Transition(2, 7, ['в'], 'in', 'r'),  # в - первая буква суффикса
        Transition(2, 8, ['ш'], 'in', 'r'),  # ш - первая буква суффикса
        Transition(2, 10, ['у', 'ю'], 'in', 'r'),  # у, ю - первая буква суффикса

        Transition(3, 2, alph(abc_str, beta + ['c']), 'in', 'r'),
        Transition(3, 2, beta, 'in', 's'),
        Transition(3, 4, ['с'], 'in', 'r'),
        Transition(3, f, abc, 'not', 'r'),

        Transition(4, 2, alph(abc_str, ['ь']), 'in', 'r'),
        Transition(4, 5, ['ь'], 'in', 'r'),
        Transition(4, 1, abc, 'not', 'r'),

        Transition(5, 2, abc, 'in', 'r'),
        Transition(5, f, abc, 'not', 'r'),

        Transition(6, 2, alph(abc_str, beta + ['с']), 'in', 'r'),
        Transition(6, 4, beta, 'in', 's'),
        Transition(6, 4, ['с'], 'in', 'r'),
        Transition(6, f, abc, 'not', 'r'),

        Transition(7, 2, beta, 'in', 's'),
        Transition(7, 2, alph(abc_str, beta), 'in', 'r'),
        Transition(7, f, abc, 'not', 'r'),

        Transition(8, 2, alph(abc_str, beta + ['и']), 'in', 'r'),
        Transition(8, 2, beta, 'in', 's'),
        Transition(8, 9, ['и'], 'in', 'r'),
        Transition(8, 1, abc, 'not', 'r'),

        Transition(9, 2, alph(abc_str, ['с']), 'in', 'r'),
        Transition(9, 4, ['с'], 'in', 'r'),
        Transition(9, f, abc, 'not', 'r'),

        Transition(10, 2, alph(abc_str, ['ч']), 'in', 'r'),
        Transition(10, 11, ['ч'], 'in', 'r'),
        Transition(10, 1, abc, 'not', 'r'),

        Transition(11, 2, alph(abc_str, ['и']), 'in', 'r'),
        Transition(11, 12, ['и'], 'in', 'r'),
        Transition(11, 1, abc, 'not', 'r'),

        Transition(12, 2, abc, 'in', 'r'),
        Transition(12, f, abc, 'not', 'r'),

        Transition(f, 1, [], 'not', 's')
    ]

    final_state = 100
    found = run_automat(instructions, text, final_state)
    res = []

    for couple in found:
        res.append(text[couple[0]:couple[1]])

    return res


# Возвращает массив пар индексов подходящих условию подстрок
def run_automat(instructions, text, final_state):
    pos = 0
    end = len(text)
    state = 1
    start_pos = 0
    found = []

    while pos != end:
        print(state, text[pos], end='')
        tran = find_transition(state, text[pos], instructions)

        if tran is None:
            print('exit 1')
            print('!!!!!!!!!!!!!!!!!')
            return None

        if tran.state_1 == 1 and tran.state_2 != 1:
            start_pos = pos

        if tran.state_2 == final_state:
            found.append((start_pos, pos + 1))

        if tran.direction == 'r':
            pos += 1
        elif tran.direction == 'l':
            pos -= 1

        state = tran.state_2
        print(' --> ' + str(state))

    return found


# Возвращает нужную инструкцию из массива инструкций
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
