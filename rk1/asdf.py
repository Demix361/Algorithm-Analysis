

a = ['1', '2', '3', '4', '5', '6']

for b in a:
    if b == 1 or b == 4 or b == 6:
        a.remove(b)

print(a)