import re
import enum


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


class Automat(enum.Enum):
    start = 0
    #########
    ch = 1
    ch_e = 2
    ch_e_k = 3
    ch_k = 4
    ch_i = 5
    ch_i_k = 6
    #########
    e = 7
    e_c = 8
    e_c_k = 9
    e_n = 10
    e_n_soft = 11
    e_n_soft_k = 12
    #########
    o = 13
    o_k = 14
    o_ch = 15
    o_ch_k = 16
    #########
    i = 17
    i_sh = 18
    i_sh_k = 19
    i_c = 20
    i_k = 21
    i_ch = 22
    i_ch_k = 23
    #########
    u = 24
    u_r = 25
    u_r_k = 26
    u_sh = 27
    u_sh_k = 28
    #########
    finish = 29


def check_words(word, automat):
    current_state = automat.start

    return_flag = False
    a = 0
    word = word.lower()

    while a <= len(word):
        try:
            i = word[a]
        except:
            i = None
            pass

        # print(i)
        if current_state == automat.start:
            if i == 'ч' and a:
                current_state = automat.ch
            elif i == 'о' and a:
                current_state = automat.o
            elif i == 'у' and a:
                current_state = automat.u
            elif i == 'и' and a:
                current_state = automat.i
            elif i == 'е' and a:
                current_state = automat.e

        elif current_state != automat.finish:
            if current_state == automat.ch:
                if i == 'ч':
                    pass
                elif i == 'е':
                    current_state = automat.ch_e
                elif i == 'и':
                    current_state = automat.ch_i
                elif i == 'к':
                    current_state = automat.ch_k
                else:
                    current_state = automat.start
                    a -= 1

            elif current_state == automat.ch_e:
                if i == 'к':
                    current_state = automat.ch_e_k
                else:
                    current_state = automat.start
                    a -= 2

            elif current_state == automat.ch_e_k:
                current_state = automat.finish

            elif current_state == automat.ch_k:
                current_state = automat.finish

            elif current_state == automat.ch_i:
                if i == 'к':
                    current_state = automat.ch_i_k
                else:
                    current_state = automat.start
                    a -= 2

            elif current_state == automat.ch_i_k:
                current_state = automat.finish

            elif current_state == automat.o:
                if i == 'ч':
                    current_state = automat.o_ch
                elif i == 'к':
                    current_state = automat.o_k
                elif i == 'о':
                    pass
                else:
                    current_state = automat.start
                    a -= 1

            elif current_state == automat.o_k:
                current_state = automat.finish

            elif current_state == automat.o_ch:
                if i == 'к':
                    current_state = automat.o_ch_k
                else:
                    current_state = automat.start
                    a -= 2

            elif current_state == automat.o_ch_k:
                current_state = automat.finish

            elif current_state == automat.u:
                if i == 'у':
                    pass
                elif i == 'р':
                    current_state = automat.u_r
                elif i == 'ш':
                    current_state = automat.u_sh
                else:
                    current_state = automat.start
                    a -= 1

            elif current_state == automat.u_r:
                if i == 'к':
                    current_state = automat.u_r_k
                else:
                    current_state = automat.start
                    a -= 2

            elif current_state == automat.u_r_k:
                current_state = automat.finish

            elif current_state == automat.u_sh:
                if i == 'к':
                    current_state = automat.u_sh_k
                else:
                    current_state = automat.start
                    a -= 2

            elif current_state == automat.u_sh_k:
                current_state = automat.finish

            elif current_state == automat.i:
                if i == 'ч':
                    current_state = automat.i_ch
                elif i == 'к':
                    current_state = automat.i_k
                elif i == 'ш':
                    current_state = automat.i_sh
                elif i == 'ц':
                    current_state = automat.i_c
                elif i == 'и':
                    pass
                else:
                    current_state = automat.start
                    a -= 1

            elif current_state == automat.i_sh:
                if i == 'к':
                    current_state = automat.i_sh_k
                else:
                    current_state = automat.start
                    a -= 2

            elif current_state == automat.i_sh_k:
                current_state = automat.finish

            elif current_state == automat.i_c:
                current_state = automat.finish

            elif current_state == automat.i_k:
                current_state = automat.finish

            elif current_state == automat.i_ch:
                if i == 'к':
                    current_state = automat.i_ch_k
                else:
                    current_state = automat.start
                    a -= 2

            elif current_state == automat.i_ch_k:
                current_state = automat.finish

            elif current_state == automat.e:
                if i == 'е':
                    pass
                elif i == 'н':
                    current_state = automat.e_n
                else:
                    current_state = automat.start
                    a -= 1

            elif current_state == automat.e_n:
                if i == 'ь':
                    current_state = automat.e_n_soft
                else:
                    current_state = automat.start
                    a -= 2

            elif current_state == automat.e_n_soft:
                if i == 'к':
                    current_state = automat.e_n_soft_k
                else:
                    current_state = automat.start
                    a -= 3

            elif current_state == automat.e_n_soft_k:
                current_state = automat.finish

        else:
            break

        a += 1

    if current_state == automat.finish:
        return_flag = True

    return return_flag


def find_suffixes(words, automat):
    res = []
    for i in words:
        if check_words(i, automat):
            res.append(i)

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

    print('Даты в формате dd.mm.yyyy:')
    print(res_re_ru_date)
    print('Даты в формате mm.dd.yyyy:')
    print(res_re_us_date)
    print('Даты в текстовом формате:')
    print(res_re_text_date)


    all_words = re.findall(r"\b\w+", text)

    # res_automat = find_suffixes(all_words, Automat)

    # print(res_automat)



main()
