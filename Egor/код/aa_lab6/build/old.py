import pylab
from mpl_toolkits.mplot3d import Axes3D
from matplotlib.colors import LinearSegmentedColormap
from matplotlib import cm
import numpy
import matplotlib.pyplot as plt

# def makeData ():
#     x = numpy.arange (-10, 10, 0.1)
#     y = numpy.arange (-10, 10, 0.1)
#     xgrid, ygrid = numpy.meshgrid(x, y)

#     zgrid = numpy.sin (xgrid) * numpy.sin (ygrid) / (xgrid * ygrid)
#     return xgrid, ygrid, zgrid

# x, y, z = makeData()

# fig = pylab.figure()
# axes = Axes3D(fig)

# axes.plot_surface(x, y, z, rstride=4, cstride=4, cmap = cm.jet)

# pylab.show()

file_name = "research.txt"

f = open(file_name, 'r')
text = [line for line in f]
f.close()

x = []
y = []
z = []

n = 0
for line in text:
  n += 1
  alpha, rho, t, res = map(float, line.split())
  if res:
    x.append(alpha)
    y.append(rho)
    z.append(t)

print(n)
print(len(x))

fig = plt.figure()
ax = fig.add_subplot(111, projection='3d')
ax.scatter(x, y, z)

plt.show()

import xlwt

file_name = 'TEST_MAX.txt'

alpha = [x for x in range(0, 1, 0.1)]
rho = [x for x in range(0, 0.9, 0.1)]
t = []
ans = [x for x in range(5)]
aco_min = []
aco_max = []

sizes = []
for i in range(100, 1001, 100):
  sizes.append(i)
  sizes.append(i + 1)

wb = xlwt.Workbook()
ws = wb.add_sheet('Test')

test_num = 0

f = open(file_name, 'r')
text = [line for line in f if 'alpha' not in line]
f.close()

alpha_ = []
rho_ = []
t_ = []
ans_ = []
aco_min_ = []
aco_max_ = []

for i in range(len(text)):

    alpha = []
    rho = []
    t = []
    ans = []
    aco_min = []
    aco_max = []

    if '{' in text[i]:
        i += 1
        while '{' not in text[i]:
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




ws.write(test_num + 1, 0, 'Стандартный')
ws.write(test_num + 2, 0, 'Виноград')
ws.write(test_num + 3, 0, 'Виноград (опт.)')

index = 0
for line in text:
    start = line.find(':') + 2

    if 'STD' in line:
        ws.write(test_num, index + 1, sizes[index]) # write size
        num = float(line[start:-1])
        ws.write(test_num + 1, index + 1, num)
    elif 'MOD_VINOGRAD' in line:
        num = float(line[start:-1])
        ws.write(test_num + 3, index + 1, num)
        index += 1
    else:
        num = float(line[start:-1])
        ws.write(test_num + 2, index + 1, num)

test_num += 5

wb.save('last_test.xls')
