import math
for _ in range(int(input())):
    s = input()
    s = int(s)

    sqrt_s = math.sqrt(s)

    if sqrt_s == int(sqrt_s):
        print(0, int(sqrt_s))
    else:
        print(-1)
