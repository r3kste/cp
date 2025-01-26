def test():
    n, m = map(int, input().split())
    return max(n, m) + 1


output = []
for _ in range(int(input())):
    output.append(test())

for stuff in output:
    print(stuff)
