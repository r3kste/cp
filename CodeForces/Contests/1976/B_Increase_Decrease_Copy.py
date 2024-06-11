t = int(input())
for _ in range(t):
    n = int(input())
    a = [int(x) for x in input().split()]
    b = [int(x) for x in input().split()]

    last = b[-1]

    closest = -1000000000
    for i in range(n):
        if a[i] <= last <= b[i] or b[i] <= last <= a[i]:
            closest = last
            break
        else:
            if abs(a[i] - last) < abs(b[i] - last):
                if abs(a[i] - last) < abs(closest - last):
                    closest = a[i]
            else:
                if abs(b[i] - last) < abs(closest - last):
                    closest = b[i]
    a.append(closest)
    res = 0
    for i in range(n + 1):
        res += abs(a[i] - b[i])

    print(res + 1)
