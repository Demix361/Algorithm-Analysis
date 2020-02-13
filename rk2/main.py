import re
from automat import date_ru_automat, date_us_automat


def get_months_str(months):
    res = ''

    for i in range(len(months)):
        if i != len(months) - 1:
            res += months[i] + '|'
        else:
            res += months[i]

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
    text = load_text('text_3.txt')

    months = ['января', 'янв',
              'февраля', 'фев',
              'марта', 'мар',
              'апреля', 'апр',
              'мая',
              'июня', 'июн',
              'июля', 'июл',
              'августа', 'авг',
              'сентября', 'сен',
              'октября', 'окт',
              'ноября', 'ноя',
              'декабря', 'дек']

    months_str = get_months_str(months)

    res_re_ru_date = re.findall(r'(0[1-9]|[12][0-9]|3[01])[-/.](0[1-9]|1[0-2])[-/.](1\d\d\d|2[01]\d\d)', text)
    res_re_us_date = re.findall(r'(0[1-9]|1[0-2])[-/.](0[1-9]|[12][0-9]|3[01])[-/.](1\d\d\d|2[01]\d\d)', text)
    res_re_text_date = re.findall(r'([1-9]|[12][0-9]|3[01]) (' + months_str + r') (1\d\d\d|2[01]\d\d)', text)

    res_re_ru_date = format_re_output(res_re_ru_date, '.')
    res_re_us_date = format_re_output(res_re_us_date, '.')
    res_re_text_date = format_re_output(res_re_text_date, ' ')

    res_auto_ru_date = date_ru_automat(text)
    res_auto_us_date = date_us_automat(text)

    print('Даты в формате dd.mm.yyyy')
    print('Регулярное выражение:')
    print(res_re_ru_date)
    print('Конечный автомат:')
    print(res_auto_ru_date)
    print()

    print('Даты в формате mm.dd.yyyy:')
    print('Регулярное выражение:')
    print(res_re_us_date)
    print('Конечный автомат:')
    print(res_auto_us_date)
    print()

    print('Даты в текстовом формате:')
    print(res_re_text_date)


if __name__ == '__main__':
    main()
