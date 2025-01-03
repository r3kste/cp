output = []
for _ in range(int(input())):
    n = int(input())
    a = list(map(int, input().split()))
    if all(e == 0 for e in a):
        output.append(0)
        continue
    no_of_segments = 0
    for i in range(1, n):
        if a[i] == 0:
            continue
        if a[i] != 0 and a[i - 1] == 0:
            no_of_segments += 1
    if a[0] != 0:
        no_of_segments += 1

    res = min(no_of_segments, 2)
    output.append(res)


for stuff in output:
    print(stuff)
