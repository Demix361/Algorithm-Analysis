

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

                    Transition(100, 1, [], 'not', 'r')  # Продолжаем поиск
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
    c = 300

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

        # января, янв
        Transition(a, 6, ['я'], 'in', 'r'),
        Transition(6, 7, ['н'], 'in', 'r'),
        Transition(7, 8, ['в'], 'in', 'r'),
        Transition(8, 9, ['а'], 'in', 'r'),
        Transition(9, 10, ['р'], 'in', 'r'),
        Transition(10, 11, ['я'], 'in', 'r'),
        Transition(11, b, [' '], 'in', 'r'),
        Transition(8, b, [' '], 'in', 'r'),

        Transition(a, 1, ['я', 'ф', 'м', 'а', 'и', 'с', 'о', 'н', 'д'], 'not', 'r'),
        Transition(6, 1, ['н'], 'not', 'r'),
        Transition(7, 1, ['в'], 'not', 'r'),
        Transition(8, 1, ['а', ' '], 'not', 'r'),
        Transition(9, 1, ['р'], 'not', 'r'),
        Transition(10, 1, ['я'], 'not', 'r'),
        Transition(11, 1, [' '], 'not', 'r'),

        # февраля, фев
        Transition(a, 12, ['ф'], 'in', 'r'),
        Transition(12, 13, ['е'], 'in', 'r'),
        Transition(13, 14, ['в'], 'in', 'r'),
        Transition(14, 15, ['р'], 'in', 'r'),
        Transition(15, 16, ['а'], 'in', 'r'),
        Transition(16, 17, ['л'], 'in', 'r'),
        Transition(17, 18, ['я'], 'in', 'r'),
        Transition(18, b, [' '], 'in', 'r'),
        Transition(14, b, [' '], 'in', 'r'),

        Transition(12, 1, ['е'], 'not', 'r'),
        Transition(13, 1, ['в'], 'not', 'r'),
        Transition(14, 1, ['р', ' '], 'not', 'r'),
        Transition(15, 1, ['а'], 'not', 'r'),
        Transition(16, 1, ['л'], 'not', 'r'),
        Transition(17, 1, ['я'], 'not', 'r'),
        Transition(18, 1, [' '], 'not', 'r'),

        # марта, мар
        Transition(a, 19, ['м'], 'in', 'r'),
        Transition(19, 20, ['а'], 'in', 'r'),
        Transition(20, 21, ['р'], 'in', 'r'),
        Transition(21, 22, ['т'], 'in', 'r'),
        Transition(22, 23, ['а'], 'in', 'r'),
        Transition(23, b, [' '], 'in', 'r'),
        Transition(21, b, [' '], 'in', 'r'),

        Transition(19, 1, ['а'], 'not', 'r'),
        Transition(20, 1, ['р', 'я'], 'not', 'r'),
        Transition(21, 1, ['т', ' '], 'not', 'r'),
        Transition(22, 1, ['а'], 'not', 'r'),
        Transition(23, 1, [' '], 'not', 'r'),

        # апреля, апр
        Transition(a, 24, ['а'], 'in', 'r'),
        Transition(24, 25, ['п'], 'in', 'r'),
        Transition(25, 26, ['р'], 'in', 'r'),
        Transition(26, 27, ['е'], 'in', 'r'),
        Transition(27, 28, ['л'], 'in', 'r'),
        Transition(28, 29, ['я'], 'in', 'r'),
        Transition(29, b, [' '], 'in', 'r'),
        Transition(26, b, [' '], 'in', 'r'),

        Transition(24, 1, ['п', 'в'], 'not', 'r'),
        Transition(25, 1, ['р'], 'not', 'r'),
        Transition(26, 1, ['е', ' '], 'not', 'r'),
        Transition(27, 1, ['л'], 'not', 'r'),
        Transition(28, 1, ['я'], 'not', 'r'),
        Transition(29, 1, [' '], 'not', 'r'),

        # мая
        # Transition(,, ['м'], 'in', 'r'),
        # Transition(,, ['а'], 'in', 'r'),
        Transition(20, 30, ['я'], 'in', 'r'),
        Transition(30, b, [' '], 'in', 'r'),

        Transition(30, 1, [' '], 'not', 'r'),

        # июня, июн
        Transition(a, 31, ['и'], 'in', 'r'),
        Transition(31, 32, ['ю'], 'in', 'r'),
        Transition(32, 33, ['н'], 'in', 'r'),
        Transition(33, 34, ['я'], 'in', 'r'),
        Transition(34, b, [' '], 'in', 'r'),
        Transition(33, b, [' '], 'in', 'r'),

        Transition(31, 1, ['ю'], 'not', 'r'),
        Transition(32, 1, ['н', 'л'], 'not', 'r'),
        Transition(33, 1, ['я', ' '], 'not', 'r'),
        Transition(34, 1, [' '], 'not', 'r'),

        # июля, июл
        # Transition(, , ['и'], 'in', 'r'),
        # Transition(, , ['ю'], 'in', 'r'),
        Transition(32, 35, ['л'], 'in', 'r'),
        Transition(35, 36, ['я'], 'in', 'r'),
        Transition(36, b, [' '], 'in', 'r'),
        Transition(35, b, [' '], 'in', 'r'),

        Transition(35, 1, ['я', ' '], 'not', 'r'),
        Transition(36, 1, [' '], 'not', 'r'),

        # августа, авг
        # Transition(,, ['а'], 'in', 'r'),
        Transition(24, 37, ['в'], 'in', 'r'),
        Transition(37, 38, ['г'], 'in', 'r'),
        Transition(38, 39, ['у'], 'in', 'r'),
        Transition(39, 40, ['с'], 'in', 'r'),
        Transition(40, 41, ['т'], 'in', 'r'),
        Transition(41, 42, ['а'], 'in', 'r'),
        Transition(42, b, [' '], 'in', 'r'),
        Transition(38, b, [' '], 'in', 'r'),

        Transition(37, 1, ['г'], 'not', 'r'),
        Transition(38, 1, ['у', ' '], 'not', 'r'),
        Transition(39, 1, ['с'], 'not', 'r'),
        Transition(40, 1, ['т'], 'not', 'r'),
        Transition(41, 1, ['а'], 'not', 'r'),
        Transition(42, 1, [' '], 'in', 'r'),

        # сентября, сен // 43 - отсутствует
        Transition(a, 44, ['с'], 'in', 'r'),
        Transition(44, 45, ['е'], 'in', 'r'),
        Transition(45, 46, ['н'], 'in', 'r'),
        Transition(46, 47, ['т'], 'in', 'r'),
        Transition(47, 48, ['я'], 'in', 'r'),
        Transition(48, 49, ['б'], 'in', 'r'),
        Transition(49, 50, ['р'], 'in', 'r'),
        Transition(50, 51, ['я'], 'in', 'r'),
        Transition(51, b, [' '], 'in', 'r'),
        Transition(46, b, [' '], 'in', 'r'),

        Transition(44, 1, ['е'], 'not', 'r'),
        Transition(45, 1, ['н'], 'not', 'r'),
        Transition(46, 1, ['т', ' '], 'not', 'r'),
        Transition(47, 1, ['я'], 'not', 'r'),
        Transition(48, 1, ['б'], 'not', 'r'),
        Transition(49, 1, ['р'], 'not', 'r'),
        Transition(50, 1, ['я'], 'not', 'r'),
        Transition(51, 1, [' '], 'not', 'r'),

        # октября, окт // 52 - отсутствует
        Transition(a, 53, ['о'], 'in', 'r'),
        Transition(53, 54, ['к'], 'in', 'r'),
        Transition(54, 55, ['т'], 'in', 'r'),
        Transition(55, 56, ['я'], 'in', 'r'),
        Transition(56, 57, ['б'], 'in', 'r'),
        Transition(57, 58, ['р'], 'in', 'r'),
        Transition(58, 59, ['я'], 'in', 'r'),
        Transition(59, b, [' '], 'in', 'r'),
        Transition(55, b, [' '], 'in', 'r'),

        Transition(53, 1, ['к'], 'not', 'r'),
        Transition(54, 1, ['т'], 'not', 'r'),
        Transition(55, 1, ['я', ' '], 'not', 'r'),
        Transition(56, 1, ['б'], 'not', 'r'),
        Transition(57, 1, ['р'], 'not', 'r'),
        Transition(58, 1, ['я'], 'not', 'r'),
        Transition(59, 1, [' '], 'not', 'r'),

        # ноября, ноя // 60 - отсутствует
        Transition(a, 61, ['н'], 'in', 'r'),
        Transition(61, 62, ['о'], 'in', 'r'),
        Transition(62, 63, ['я'], 'in', 'r'),
        Transition(63, 64, ['б'], 'in', 'r'),
        Transition(64, 65, ['р'], 'in', 'r'),
        Transition(65, 66, ['я'], 'in', 'r'),
        Transition(66, b, [' '], 'in', 'r'),
        Transition(63, b, [' '], 'in', 'r'),

        Transition(61, 1, ['о'], 'not', 'r'),
        Transition(62, 1, ['я'], 'not', 'r'),
        Transition(63, 1, ['б', ' '], 'not', 'r'),
        Transition(64, 1, ['р'], 'not', 'r'),
        Transition(65, 1, ['я'], 'not', 'r'),
        Transition(66, 1, [' '], 'not', 'r'),

        # декабря, дек // 67 - отсутствует
        Transition(a, 68, ['д'], 'in', 'r'),
        Transition(68, 69, ['е'], 'in', 'r'),
        Transition(69, 70, ['к'], 'in', 'r'),
        Transition(70, 71, ['а'], 'in', 'r'),
        Transition(71, 72, ['б'], 'in', 'r'),
        Transition(72, 73, ['р'], 'in', 'r'),
        Transition(73, 74, ['я'], 'in', 'r'),
        Transition(74, b, [' '], 'in', 'r'),
        Transition(70, b, [' '], 'in', 'r'),

        Transition(68, 1, ['е'], 'not', 'r'),
        Transition(69, 1, ['к'], 'not', 'r'),
        Transition(70, 1, ['а', ' '], 'not', 'r'),
        Transition(71, 1, ['б'], 'not', 'r'),
        Transition(72, 1, ['р'], 'not', 'r'),
        Transition(73, 1, ['я'], 'not', 'r'),
        Transition(74, 1, [' '], 'not', 'r'),

        # Год
        Transition(b, 81, ['1'], 'in', 'r'),  # Первая цифра года
        Transition(b, 82, ['2'], 'in', 'r'),
        Transition(b, 1, ['1', '2'], 'not', 'r'),

        Transition(81, 83, ['0', '1', '2', '3', '4', '5', '6', '7', '8', '9'], 'in', 'r'),  # 1000 - 1999
        Transition(83, 84, ['0', '1', '2', '3', '4', '5', '6', '7', '8', '9'], 'in', 'r'),
        Transition(84, c, ['0', '1', '2', '3', '4', '5', '6', '7', '8', '9'], 'in', 'r'),
        Transition(81, 1, ['0', '1', '2', '3', '4', '5', '6', '7', '8', '9'], 'not', 'r'),
        Transition(83, 1, ['0', '1', '2', '3', '4', '5', '6', '7', '8', '9'], 'not', 'r'),
        Transition(84, 1, ['0', '1', '2', '3', '4', '5', '6', '7', '8', '9'], 'not', 'r'),

        Transition(82, 85, ['0', '1'], 'in', 'r'),  # 2000 - 2199
        Transition(85, 86, ['0', '1', '2', '3', '4', '5', '6', '7', '8', '9'], 'in', 'r'),
        Transition(86, c, ['0', '1', '2', '3', '4', '5', '6', '7', '8', '9'], 'in', 'r'),
        Transition(82, 1, ['0', '1'], 'not', 'r'),
        Transition(85, 1, ['0', '1', '2', '3', '4', '5', '6', '7', '8', '9'], 'not', 'r'),
        Transition(86, 1, ['0', '1', '2', '3', '4', '5', '6', '7', '8', '9'], 'not', 'r'),

        Transition(c, 1, [], 'not', 'r')
    ]

    final_state = c
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
        # print(state, text[pos])
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
