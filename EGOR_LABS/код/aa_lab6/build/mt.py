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
    break


# f = open('gr2.csv', 'w')
# f.write(';Ответ;Муравьи\n')
# for i in range(1, len(alpha_)):
for i in range(len(alpha_)):
    name = 'mt.csv'
    f = open(name, 'w')
    f.write('№;alpha;rho;t;Ответ;Муравьи\n')
    alpha = alpha_[i]
    rho = rho_[i]
    t = t_[i]
    ans = ans_[i]
    aco_min = aco_min_[i]
    aco_max = aco_max_[i]

    for j in range(len(alpha)):
        string = 'a={0}, r={1}, t={2}'.format(alpha[j], rho[j], int(t[j]))
        f.write('{0};{1};{2};{3};{4};{5}\n'.format(j, alpha[j], rho[j], t[j], int(ans[j]), int(aco_min[j])))

    f.close()
