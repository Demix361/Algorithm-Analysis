

# Класс инструкции автомата
class Transition:
    def __init__(self, state_1, state_2, symbols, sym_ins, direction):
        self.state_1 = state_1
        self.state_2 = state_2
        self.symbols = symbols
        self.sym_ins = sym_ins
        self.direction = direction


# Автомат для поиска даты в формате dd.mm.yyyy
def date_ru_automat(text):
    instructions = [Transition(1, 2, ['0'], 'in', 'r'),  # Первая цифра дня
                    Transition(1, 3, ['1', '2'], 'in', 'r'),
                    Transition(1, 4, ['3'], 'in', 'r'),
                    Transition(1, 1, ['0', '1', '2', '3'], 'not', 'r'),

                    Transition(2, 5, ['1', '2', '3', '4', '5', '6', '7', '8', '9'], 'in', 'r'),  # Вторая цифра дня
                    Transition(3, 5, ['0', '1', '2', '3', '4', '5', '6', '7', '8', '9'], 'in', 'r'),
                    Transition(4, 5, ['0', '1'], 'in', 'r'),
                    Transition(2, 1, ['1', '2', '3', '4', '5', '6', '7', '8', '9'], 'not', 'r'),
                    Transition(3, 1, ['0', '1', '2', '3', '4', '5', '6', '7', '8', '9'], 'not', 'r'),
                    Transition(4, 1, ['0', '1'], 'not', 'r'),

                    Transition(5, 6, ['.', '-', '/'], 'in', 'r'),  # Разделитель
                    Transition(5, 1, ['.', '-', '/'], 'not', 'r'),

                    Transition(6, 7, ['0'], 'in', 'r'),  # Первая цифра месяца
                    Transition(6, 8, ['1'], 'in', 'r'),
                    Transition(6, 1, ['0', '1'], 'not', 'r'),

                    Transition(7, 9, ['1', '2', '3', '4', '5', '6', '7', '8', '9'], 'in', 'r'),  # Вторая цифра месяца
                    Transition(8, 9, ['0', '1', '2'], 'in', 'r'),
                    Transition(7, 1, ['1', '2', '3', '4', '5', '6', '7', '8', '9'], 'not', 'r'),
                    Transition(8, 1, ['0', '1', '2'], 'not', 'r'),

                    Transition(9, 10, ['.', '-', '/'], 'in', 'r'),  # Разделитель
                    Transition(9, 1, ['.', '-', '/'], 'not', 'r'),

                    Transition(10, 11, ['1'], 'in', 'r'),  # Первая цифра года
                    Transition(10, 12, ['2'], 'in', 'r'),
                    Transition(10, 1, ['1', '2'], 'not', 'r'),

                    Transition(11, 13, ['0', '1', '2', '3', '4', '5', '6', '7', '8', '9'], 'in', 'r'),  # 1000 - 1999
                    Transition(13, 14, ['0', '1', '2', '3', '4', '5', '6', '7', '8', '9'], 'in', 'r'),
                    Transition(14, 100, ['0', '1', '2', '3', '4', '5', '6', '7', '8', '9'], 'in', 'r'),
                    Transition(11, 1, ['0', '1', '2', '3', '4', '5', '6', '7', '8', '9'], 'not', 'r'),
                    Transition(13, 1, ['0', '1', '2', '3', '4', '5', '6', '7', '8', '9'], 'not', 'r'),
                    Transition(14, 1, ['0', '1', '2', '3', '4', '5', '6', '7', '8', '9'], 'not', 'r'),

                    Transition(12, 15, ['0', '1'], 'in', 'r'),  # 2000 - 2199
                    Transition(15, 16, ['0', '1', '2', '3', '4', '5', '6', '7', '8', '9'], 'in', 'r'),
                    Transition(16, 100, ['0', '1', '2', '3', '4', '5', '6', '7', '8', '9'], 'in', 'r'),
                    Transition(12, 1, ['0', '1'], 'not', 'r'),
                    Transition(15, 1, ['0', '1', '2', '3', '4', '5', '6', '7', '8', '9'], 'not', 'r'),
                    Transition(16, 1, ['0', '1', '2', '3', '4', '5', '6', '7', '8', '9'], 'not', 'r'),

                    Transition(100, 1, [], 'not', 'r'),  # Продолжаем поиск
    ]

    final_state = 100
    found = run_automat(instructions, text, final_state)
    res = []

    for couple in found:
        res.append(text[couple[0]:couple[1]])

    return res


# Автомат для поиска даты в формате mm.dd.yyyy
def date_us_automat(text):
    instructions = [
                    Transition(1, 2, ['0'], 'in', 'r'),  # Первая цифра месяца
                    Transition(1, 3, ['1'], 'in', 'r'),
                    Transition(1, 1, ['0', '1'], 'not', 'r'),

                    Transition(2, 4, ['1', '2', '3', '4', '5', '6', '7', '8', '9'], 'in', 'r'),  # Вторая цифра месяца
                    Transition(3, 4, ['0', '1', '2'], 'in', 'r'),
                    Transition(2, 1, ['1', '2', '3', '4', '5', '6', '7', '8', '9'], 'not', 'r'),
                    Transition(3, 1, ['0', '1', '2'], 'not', 'r'),

                    Transition(4, 5, ['.', '-', '/'], 'in', 'r'),  # Разделитель
                    Transition(4, 1, ['.', '-', '/'], 'not', 'r'),

                    Transition(5, 6, ['0'], 'in', 'r'),  # Первая цифра дня
                    Transition(5, 7, ['1', '2'], 'in', 'r'),
                    Transition(5, 8, ['3'], 'in', 'r'),
                    Transition(5, 1, ['0', '1', '2', '3'], 'not', 'r'),

                    Transition(6, 9, ['1', '2', '3', '4', '5', '6', '7', '8', '9'], 'in', 'r'),  # Вторая цифра дня
                    Transition(7, 9, ['0', '1', '2', '3', '4', '5', '6', '7', '8', '9'], 'in', 'r'),
                    Transition(8, 9, ['0', '1'], 'in', 'r'),
                    Transition(6, 1, ['1', '2', '3', '4', '5', '6', '7', '8', '9'], 'not', 'r'),
                    Transition(7, 1, ['0', '1', '2', '3', '4', '5', '6', '7', '8', '9'], 'not', 'r'),
                    Transition(8, 1, ['0', '1'], 'not', 'r'),

                    Transition(9, 10, ['.', '-', '/'], 'in', 'r'),  # Разделитель
                    Transition(9, 1, ['.', '-', '/'], 'not', 'r'),

                    Transition(10, 11, ['1'], 'in', 'r'),  # Первая цифра года
                    Transition(10, 12, ['2'], 'in', 'r'),
                    Transition(10, 1, ['1', '2'], 'not', 'r'),

                    Transition(11, 13, ['0', '1', '2', '3', '4', '5', '6', '7', '8', '9'], 'in', 'r'),  # 1000 - 1999
                    Transition(13, 14, ['0', '1', '2', '3', '4', '5', '6', '7', '8', '9'], 'in', 'r'),
                    Transition(14, 100, ['0', '1', '2', '3', '4', '5', '6', '7', '8', '9'], 'in', 'r'),
                    Transition(11, 1, ['0', '1', '2', '3', '4', '5', '6', '7', '8', '9'], 'not', 'r'),
                    Transition(13, 1, ['0', '1', '2', '3', '4', '5', '6', '7', '8', '9'], 'not', 'r'),
                    Transition(14, 1, ['0', '1', '2', '3', '4', '5', '6', '7', '8', '9'], 'not', 'r'),

                    Transition(12, 15, ['0', '1'], 'in', 'r'),  # 2000 - 2199
                    Transition(15, 16, ['0', '1', '2', '3', '4', '5', '6', '7', '8', '9'], 'in', 'r'),
                    Transition(16, 100, ['0', '1', '2', '3', '4', '5', '6', '7', '8', '9'], 'in', 'r'),
                    Transition(12, 1, ['0', '1'], 'not', 'r'),
                    Transition(15, 1, ['0', '1', '2', '3', '4', '5', '6', '7', '8', '9'], 'not', 'r'),
                    Transition(16, 1, ['0', '1', '2', '3', '4', '5', '6', '7', '8', '9'], 'not', 'r'),

                    Transition(100, 1, [], 'not', 'r'),  # Продолжаем поиск
    ]

    final_state = 100
    found = run_automat(instructions, text, final_state)
    res = []

    for couple in found:
        res.append(text[couple[0]:couple[1]])

    return res


# Автомат для поиска даты в текстовом формате

def date_text_automat(text):
    a = 5
    b = 200

    instructions = [
        Transition(1, 2, ['1', '2'], 'in', 'r'),
        Transition(1, 3, ['3'], 'in', 'r'),
        Transition(1, 4, ['4', '5', '6', '7', '8', '9'], 'in', 'r'),
        Transition(2, 4, ['0', '1', '2', '3', '4', '5', '6', '7', '8', '9'], 'in', 'r'),
        Transition(2, a, [' '], 'in', 'r'),
        Transition(3, 4, ['0', '1'], 'in', 'r'),
        Transition(3, a, [' '], 'in', 'r'),
        Transition(4, a, [' '], 'in', 'r'),

        Transition(1, 1, ['1', '2', '3', '4', '5', '6', '7', '8', '9'], 'not', 'r'),
        Transition(2, 1, ['0', '1', '2', '3', '4', '5', '6', '7', '8', '9', ' '], 'not', 'r'),
        Transition(3, 1, ['0', '1', ' '], 'not', 'r'),
        Transition(4, 1, [' '], 'not', 'r'),

        Transition(a, 6, ['я'], 'in', 'r'), # январь, янв
        Transition(6, 7, ['н'], 'in', 'r'),
        Transition(7, 8, ['в'], 'in', 'r'),
        Transition(8, 9, ['а'], 'in', 'r'),
        Transition(9, 10, ['р'], 'in', 'r'),
        Transition(10, 11, ['я'], 'in', 'r'),
        Transition(11, b, [' '], 'in', 'r'),
        Transition(8, b, [' '], 'in', 'r'),

        Transition(a, 12, ['ф'], 'in', 'r'), # февраль, фев
        Transition(12, 13, ['е'], 'in', 'r'),
        Transition(13, 14, ['в'], 'in', 'r'),
        Transition(14, 15, ['р'], 'in', 'r'),
        Transition(15, 16, ['а'], 'in', 'r'),
        Transition(16, 17, ['л'], 'in', 'r'),
        Transition(17, 18, ['я'], 'in', 'r'),
        Transition(18, b, [' '], 'in', 'r'),
        Transition(19, b, [' '], 'in', 'r'),

        Transition(a, , ['м'], 'in', 'r'),
        Transition(, , ['а'], 'in', 'r'),
        Transition(, , ['р'], 'in', 'r'),
        Transition(, , ['т'], 'in', 'r'),
        Transition(, , ['а'], 'in', 'r'),
        Transition(, , [' '], 'in', 'r'),
        Transition(, , [' '], 'in', 'r'),

        Transition(,, ['а'], 'in', 'r'),
        Transition(,, ['п'], 'in', 'r'),
        Transition(,, ['р'], 'in', 'r'),
        Transition(,, ['е'], 'in', 'r'),
        Transition(,, ['л'], 'in', 'r'),
        Transition(,, ['я'], 'in', 'r'),
        Transition(,, [' '], 'in', 'r'),
        Transition(,, [' '], 'in', 'r'),

        Transition(,, ['м'], 'in', 'r'),
        Transition(,, ['а'], 'in', 'r'),
        Transition(,, ['я'], 'in', 'r'),
        Transition(,, [' '], 'in', 'r'),

        Transition(,, ['и'], 'in', 'r'),
        Transition(,, ['ю'], 'in', 'r'),
        Transition(,, ['н'], 'in', 'r'),
        Transition(,, ['я'], 'in', 'r'),
        Transition(,, [' '], 'in', 'r'),
        Transition(,, [' '], 'in', 'r'),

        Transition(,, ['и'], 'in', 'r'),
        Transition(,, ['ю'], 'in', 'r'),
        Transition(,, ['л'], 'in', 'r'),
        Transition(,, ['я'], 'in', 'r'),
        Transition(,, [' '], 'in', 'r'),
        Transition(,, [' '], 'in', 'r'),

        Transition(,, ['а'], 'in', 'r'),
        Transition(,, ['в'], 'in', 'r'),
        Transition(,, ['г'], 'in', 'r'),
        Transition(,, ['у'], 'in', 'r'),
        Transition(,, ['с'], 'in', 'r'),
        Transition(,, ['т'], 'in', 'r'),
        Transition(,, ['а'], 'in', 'r'),
        Transition(,, [' '], 'in', 'r'),
        Transition(,, [' '], 'in', 'r'),

        Transition(,, ['с'], 'in', 'r'),
        Transition(,, ['е'], 'in', 'r'),
        Transition(,, ['н'], 'in', 'r'),
        Transition(,, ['т'], 'in', 'r'),
        Transition(,, ['я'], 'in', 'r'),
        Transition(,, ['б'], 'in', 'r'),
        Transition(,, ['р'], 'in', 'r'),
        Transition(,, ['я'], 'in', 'r'),
        Transition(,, [' '], 'in', 'r'),
        Transition(,, [' '], 'in', 'r'),

        Transition(,, ['о'], 'in', 'r'),
        Transition(,, ['к'], 'in', 'r'),
        Transition(,, ['т'], 'in', 'r'),
        Transition(,, ['я'], 'in', 'r'),
        Transition(,, ['б'], 'in', 'r'),
        Transition(,, ['р'], 'in', 'r'),
        Transition(,, ['я'], 'in', 'r'),
        Transition(,, [' '], 'in', 'r'),
        Transition(,, [' '], 'in', 'r'),

        Transition(,, ['н'], 'in', 'r'),
        Transition(,, ['о'], 'in', 'r'),
        Transition(,, ['я'], 'in', 'r'),
        Transition(,, ['б'], 'in', 'r'),
        Transition(,, ['р'], 'in', 'r'),
        Transition(,, ['я'], 'in', 'r'),
        Transition(,, [' '], 'in', 'r'),
        Transition(,, [' '], 'in', 'r'),

        Transition(,, ['д'], 'in', 'r'),
        Transition(,, ['е'], 'in', 'r'),
        Transition(,, ['к'], 'in', 'r'),
        Transition(,, ['а'], 'in', 'r'),
        Transition(,, ['б'], 'in', 'r'),
        Transition(,, ['р'], 'in', 'r'),
        Transition(,, ['я'], 'in', 'r'),
        Transition(,, [' '], 'in', 'r'),
        Transition(,, [' '], 'in', 'r'),


        Transition(,, [], '', 'r'),


    ]

    final_state = 5
    found = run_automat(instructions, text, final_state)
    res = []

    for couple in found:
        res.append(text[couple[0]:couple[1]])

    return res



# Возвращает массив пар индексов поддходящих условию подстрок
def run_automat(instructions, text, final_state):
    pos = 0
    end = len(text)
    state = 1
    start_pos = 0
    found = []

    while pos != end:
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


aaa = date_text_automat('hadufgildfg 32 0 2 3 4 31 20 26 19 15 10 9  udgflidufghli ')
print(aaa)