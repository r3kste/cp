def test():
    n = int(input())
    s = list(input())
    if s[0] == "s":
        s[0] = "."
    if s[-1] == "p":
        s[-1] = "."

    return "YES" if (all(e in ("p", ".") for e in s) or all(e in ("s", ".") for e in s)) else "NO"


output = []
for _ in range(int(input())):
    output.append(test())

for stuff in output:
    print(stuff)
