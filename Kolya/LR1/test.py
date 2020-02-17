from main import Livenstein_matr, Livenstein_Damerau_matr, Livenstein_Damerau_recur

def proc_line(line):
    arr = line[:-1].split("\t")
    return arr[0], arr[1], int(arr[2]), int(arr[3])

def test(s1, s2, res_l_expect, res_d_l_expect):
    res_l = Livenstein_matr(s1, s2)
    res_d_l_m = Livenstein_Damerau_matr(s1, s2)
    res_d_l_r = Livenstein_Damerau_recur(s1, s2)
    print("\n==============================================================================")
    print("s1: `", s1, "` s2: `", s2, "`")
    
    if res_l == res_l_expect:
        print("Тест на Левенштейне(итеративном) успешен!")        
    else:
        print("Тест на Левенштейне(итеративном) провален. Ожидаемый результат: ", res_l_expect, "реальный результат: ", res_l)
    
    if res_d_l_expect == res_d_l_m == res_d_l_r:
        print("Тест на Левенштейне-Дамороу успешен!")
    else:
        print("Тест на Левенштейне-Дамороу провален. Ожидаемый результат: ", res_d_l_expect, "итеративный: ", res_d_l_m, "рекурсивный: ", res_d_l_r)
    print("==============================================================================\n")
    
if __name__ == "__main__":
    f = open("test.txt", "r")
    lines = f.readlines()
    for line in lines:
        s1, s2, res_l, res_d_l = proc_line(line)
        test(s1, s2, res_l, res_d_l)
