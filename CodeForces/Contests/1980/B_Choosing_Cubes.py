t = int(input())
for _ in range(t):
    n, f, k = input().split(" ")
    n, f, k = int(n), int(f), int(k)

    a = list(map(int, input().split(" ")))

    element = a[f - 1]

    a.sort(reverse=True)

    res = "NO"
    for i in range(k):
        if a[i] == element:
            res = "YES"
            break

    if k < n and res == "YES":
        if a[k] == element:
            res = "MAYBE"

    print(res)
