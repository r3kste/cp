def summation(n):
    return n * (n + 1) // 2


def test():
    n = int(input())

    res, n_ops = 0, 2 * n
    res += n * summation(n) + sum(summation(n - i) for i in range(1, n))

    print(res, n_ops)

    for i in range(n, 0, -1):
        print(f"1 {i}", *list(range(1, n + 1)))
        print(f"2 {i}", *list(range(1, n + 1)))


for _ in range(int(input())):
    test()
