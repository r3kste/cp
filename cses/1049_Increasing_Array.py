_, a = input(), list(map(int, input().split()))
current, res = a[0], 0
for i in range(1, len(a)):
    if a[i] < current:
        res += current - a[i]
    else:
        current = a[i]
print(res)
