import math, sys

def printmatr(matr):
    for i in range(len(matr)):
        for j in range(len(matr[0])):
            print(matr[i][j], end = " ")
        print()
    print()

def Livenstein_matr(s1, s2):
    l1 = len(s1)
    l2 = len(s2)
    matr = [[i + j for i in range(l2 + 1)] for j in range(l1 + 1)]
    
    for i in range(1, l1 + 1):
        for j in range(1, l2 + 1):
            opt1 = matr[i][j - 1] + 1
            opt2 = matr[i - 1][j] + 1
            opt3 = matr[i - 1][j - 1] + (0 if s1[i - 1] == s2[j - 1] else 1)
            matr[i][j] = min(opt1, opt2, opt3 )

    res = matr[l1][l2]
    return res

def Livenstein_Damerau_matr(s1, s2):
    l1 = len(s1)
    l2 = len(s2)
    matr = [[i + j for i in range(l2 + 1)] for j in range(l1 + 1)]
    
    for i in range(1, l1 + 1):
        for j in range(1, l2 + 1):
            opt4 = math.inf
            opt1 = matr[i][j - 1] + 1
            opt2 = matr[i - 1][j] + 1
            opt3 = matr[i - 1][j - 1] + (0 if s1[i - 1] == s2[j - 1] else 1)
            if i > 1 and j > 1 and s1[i - 2] == s2[j - 1] and s1[i - 1] == s2[j - 2]:
                opt4 = matr[i - 2][j - 2] + 1
            
            matr[i][j] = min(opt1, opt2, opt3, opt4)
    res = matr[l1][l2]
    return res

def Livenstein_Damerau_recur(s1, s2):
    if s1 == "" and s2 == "":
        return 0
    elif s1 != "" and s2 == "":
        return len(s1)
    elif s1 == "" and s2 != "":
        return len(s2)
        
    l1 = len(s1)
    l2 = len(s2)

    opt4 = math.inf
    opt1 = Livenstein_Damerau_recur(s1, s2[:-1]) + 1
    opt2 = Livenstein_Damerau_recur(s1[:-1], s2) + 1
    opt3 = Livenstein_Damerau_recur(s1[:-1], s2[:-1]) + (0 if s1[l1 - 1] == s2[l2 - 1] else 1)
    if l1 > 1 and l2 > 1 and s1[l1 - 1] == s2[l2 - 2] and s1[l1 - 2] == s2[l2 - 1]:
        opt4 = Livenstein_Damerau_recur(s1[:-2], s2[:-2]) + 1
        
    res = min(opt1, opt2, opt3, opt4)
    return res

funcs = [Livenstein_matr, Livenstein_Damerau_matr, Livenstein_Damerau_recur]
  
if __name__ == "__main__":
    s1 = input("Введите первое слово: ")
    s2 = input("Введите второе слово: ")
    try:
        i = int(input("Выберите пункт: \n0 - Ливенштейн(итеративно) \n1 - Ливенштейн-Дамерау(итеративно) \n2 - Ливенштейн-Дамерау(рекурсивно): "))
    except ValueError:
        print("Вы ввели не целое число!")
    else:
        if i > 2 or i < 0:
            print("Неверное число!")
        else:
            d = funcs[i](s1, s2)
            print("Штраф: ", d)
