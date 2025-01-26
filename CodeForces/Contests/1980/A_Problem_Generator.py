t = int(input())
for _ in range(t):
    n, m = input().split(" ")
    n, m = int(n), int(m)

    s = input()

    freq = {c: 0 for c in "ABCDEFG"}

    for c in s:
        freq[c] += 1

    res = 0
    for k, v in freq.items():
        if v < m:
            res += m - v

    print(res)
