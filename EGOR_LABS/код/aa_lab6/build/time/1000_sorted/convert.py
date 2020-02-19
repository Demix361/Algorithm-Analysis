import xlwt

print("TEST")

file_names = ['insertion_sort_time.txt', 'shell_sort_time.txt', 'timsort_time.txt']

wb = xlwt.Workbook()
ws = wb.add_sheet('Test')

ws.write(0, 0, 'Размер')
ws.write(0, 1, 'Вставки')
ws.write(0, 2, 'Шелл')
ws.write(0, 3, 'Тимсорт')

j = 1
for i in range(100, 1001, 100):
  ws.write(j, 0, i)
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
    ws.write(j, k, num)
    j += 1

wb.save('SORTED.xls')

print("Table was written")
