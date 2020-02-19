import xlwt

print("TEST")

# file_names = ['shell_sort_time.txt', 'timsort_time.txt']
file_names = ['BILLION_SHELL.txt', 'BILLION_TIM.txt']

wb = xlwt.Workbook()
ws = wb.add_sheet('Test')

ws.write(1, 0, 'Шелл')
ws.write(2, 0, 'Тимсорт')

j = 1
for i in range(50000, 1000001, 50000):
  ws.write(0, j, i)
  j += 1

k = 0
for name in file_names:
  k += 1
  j = 1

  f = open(name, 'r')
  text = [line for line in f if '{' not in line]
  f.close()

  for line in text:
    num = float(line)
    ws.write(k, j, num)
    j += 1

wb.save('BILLION.xls')

print("Table was written")
