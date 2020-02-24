import re
from automat import suff_automat


def get_re(ends):
    beg = r'\w+'
    end = r'\W'
    res = r''

    for i in range(len(ends)):
        if i != len(ends) - 1:
            res += beg
            res += ends[i]
            res += end
            res += '|'
        else:
            res += beg
            res += ends[i]
            res += end

    return res


def load_text(fname):
    text = ''

    with open(fname, 'r', encoding='utf-8') as f:
        for line in f:
            text += line

    return text


def format_re_output(dates, sep):
    res = []

    for d in dates:
        res.append(d[0] + sep + d[1] + sep + d[2])

    return res


def main():
    #text = load_text('text_3.txt')

    text = 'Вернувшись из университета домой, я не снимая ботинки пошел на кухню. Там, достав свиные уши из холодильника, ' \
           'я пуская слюни, приступил к трапезе. Наевшись досыта и помыв посуду, я начал делать лабораторную работу, ' \
           'параллельно размышляя о том, как я буду сдавать ее завтра.'

    endings = ['а', 'я', 'ясь', 'ась', 'учи', 'ючи', 'шись', 'ши', 'в']
    res = get_re(endings)

    res_re = re.findall(res, text)

    res_auto = suff_automat(text)


    print('Деепричастия')
    print('Регулярное выражение:')
    print(res_re)
    print('Конечный автомат:')
    print(res_auto)
    print()




if __name__ == '__main__':
    main()
