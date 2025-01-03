def _mex(arr):
    mex = 0
    while mex in arr:
        mex += 1
    return mex


def test():
    n, x, y = map(int, input().split())
    mex = [-1] * n
    friends = [set() for _ in range(n)]

    for i in range(n):
        friends[i].add((i + 1) % n)
        friends[i].add((i - 1 + n) % n)

    friends[x - 1].add(y - 1)
    friends[y - 1].add(x - 1)

    for i in range(n):
        neighbors = set()
        for friend in friends[i]:
            if mex[friend] != -1:
                neighbors.add(mex[friend])

        mex[i] = _mex(neighbors)

    return mex


output = []
for _ in range(int(input())):
    output.append(test())

for stuff in output:
    for thing in stuff:
        print(thing, end=" ")
    print()
