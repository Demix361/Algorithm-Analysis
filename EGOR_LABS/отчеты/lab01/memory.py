
for i in range (1, 202, 2):
    print(i, "/", end="")
    res = 24 + 24 *(i + 1) + 4*(i + 1)*(i + 1) + 3 * 4
    print(res, "/", end="")
    res = 0
    res = (32*2 + i + i + 8*3 + 7*4)*2*i
    k = 0
    for j in range (0,2*i):
        k += j
    res -= k
    print(res)

    

##for i in range (100, 1000, 100):
##    res = 24 + 24 *(i + 1) + 4*(i + 1)*(i + 1) + 3 * 4
##    print(res, ' ', end='')
##    res = 0
##    for j in range (0, i):
##        res += 32 * 2 + i + i - j + 8 * 3 + 7 * 4
##    print(res)
