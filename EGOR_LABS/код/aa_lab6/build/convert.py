file_name = 'RES_10x10.txt'

f = open(file_name, 'r')
text = [line for line in f if 'alpha' not in line]
f.close()

alpha_ = []
rho_ = []
t_ = []
ans_ = []
aco_min_ = []
aco_max_ = []

i = 0
while i < (len(text)):

    alpha = []
    rho = []
    t = []
    ans = []
    aco_min = []
    aco_max = []

    if '{' in text[i]:
        i += 1
        while i < len(text) and '{' not in text[i]:
            line = list(map(float, text[i].split()))
            alpha.append(line[0])
            rho.append(line[1])
            t.append(line[2])
            ans.append(line[3])
            aco_min.append(line[4])
            aco_max.append(line[5])
            i += 1
    
    alpha_.append(alpha)
    rho_.append(rho)
    t_.append(t)
    ans_.append(ans)
    aco_min_.append(aco_min)
    aco_max_.append(aco_max)


# f = open('gr2.csv', 'w')
# f.write(';Ответ;Муравьи\n')
# for i in range(1, len(alpha_)):
for i in range(len(alpha_)):
    name = '_resimg_{0}.csv'.format(i + 1)
    f = open(name, 'w')
    f.write(';Ответ;Муравьи\n')
    alpha = alpha_[i]
    rho = rho_[i]
    t = t_[i]
    ans = ans_[i]
    aco_min = aco_min_[i]
    aco_max = aco_max_[i]

    for j in range(len(alpha)):
        string = 'a={0}, r={1}, t={2}'.format(alpha[j], rho[j], int(t[j]))
        f.write('{0};{1};{2}\n'.format(string, int(ans[j]), int(aco_min[j])))

    f.close()

info = []

f = open('new_info_res_with_2_min.txt', 'w')
for i in range(len(alpha_)):
    f.write('\nDATA ')
    f.write(str(i + 1))
    f.write('\n')

    alpha = alpha_[i]
    rho = rho_[i]
    t = t_[i]
    ans = ans_[i]
    aco_min = aco_min_[i]
    aco_max = aco_max_[i]

    min_res = min(aco_min)
    min_res_2 = min(x for x in aco_min if x != min_res)
    correct = set()

    for j in range(len(alpha)):
        if min_res == aco_min[j]:
            correct.add((alpha[j], rho[j], t[j]))
            f.write('({0}; {1}; {2})\n'.format(alpha[j], rho[j], t[j]))
        elif min_res_2 == aco_min[j]:
            correct.add((alpha[j], rho[j], t[j]))
            f.write('({0}; {1}; {2})\n'.format(alpha[j], rho[j], t[j]))
    
    info.append(correct)
f.close()

for x in info:
    print(len(x))
common = info[0]
for i in range(1, len(info)):
    common &= info[i]

common = list(common)
common.sort()
for x in common:
    print('{0};{1};{2}'.format(x[0], x[1], int(x[2])))




'''
def info(arr):
    print(len(arr))
    for i in range(len(arr)):
        print(i, '=', len(arr[i]))

print('Alpha')
info(alpha_)

print('Rho')
info(rho_)

print('T')
info(t_)

print('Ans')
info(ans_)

print('AcoMin')
info(aco_min_)

print('AcoMax')
info(aco_max_)

# print('stat')
# for i in range(len(alpha_)):
#     print('A', i)
#     alpha = 0
#     while alpha <= 1:
#         print(round(alpha, 2), ':', alpha_[i].count(round(alpha, 2)))
#         alpha += 0.1

# for alpha in range(0, 1.1, 0.1):
#     for rho in range(0.1, 1, 0.1):
#         for t in range(10, 201, 10):
'''
