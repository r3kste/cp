t = int(input())
for _ in range(t):
    n = int(input())
    s = input()

    done = False
    found_letter = False
    res = "YES"
    for c in s:
        if c.isalpha():
            found_letter = True
        if c.isdigit():
            if found_letter:
                res = "NO"
                done = True

    if not done:
        letters_only = [c for c in s if c.isalpha()]
        sorted_letters = sorted(letters_only)
        if any([a != b for a, b in zip(letters_only, sorted_letters)]):
            res = "NO"
            done = True
        if not done:
            digits_only = [c for c in s if c.isdigit()]
            sorted_digits = sorted(digits_only)
            if any([a != b for a, b in zip(digits_only, sorted_digits)]):
                res = "NO"
                done = True

    print(res)
