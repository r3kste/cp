t = int(input())
for _ in range(t):
    n = int(input())
    s = input()
    r = sorted(list(set(list(s))))
    decode = {}
    l = len(r)
    for i in range(len(r)):
        decode[r[i]] = r[l - 1 - i]
    for i in range(n):
        print(decode[s[i]], end="")
    print()
