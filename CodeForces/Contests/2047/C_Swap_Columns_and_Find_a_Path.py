def test():
    n = int(input())
    a = list(map(int, input().split()))
    b = list(map(int, input().split()))

    sum_ = 0
    for ae, be in zip(a, b):
        sum_ += max(ae, be)
    
    res = float("-inf")
    for ae, be in zip(a, b):
        res = max(res, sum_ + min(ae, be))

    return res


output = []
for _ in range(int(input())):
    output.append(test())

for stuff in output:
    print(stuff)
