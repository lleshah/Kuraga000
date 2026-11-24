c = int(input())
a, b = 1, 1
for _ in range(c):
    print(a)
    a, b = b, a + b
    