

def fu(a):
    fir = 1
    sec = 1
    print("1, ")
    for i in range(a):
        print(f"{fir + sec}, ")
        temp = sec
        sec = fir
        fir = fir + temp

        a = int(input("введите число: "))
        fu(a)