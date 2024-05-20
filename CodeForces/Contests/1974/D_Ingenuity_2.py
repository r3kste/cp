t = int(input())
for _ in range(t):
    n = int(input())
    s = input()

    freq = {c: 0 for c in "NESW"}
    for c in s:
        freq[c] += 1

    y1 = min(freq["N"], freq["S"])
    y2 = max(freq["N"], freq["S"])
    y1_key = "N" if freq["N"] < freq["S"] else "S"
    y2_key = "N" if freq["N"] >= freq["S"] else "S"

    x1 = min(freq["E"], freq["W"])
    x2 = max(freq["E"], freq["W"])
    x1_key = "E" if freq["E"] < freq["W"] else "W"
    x2_key = "E" if freq["E"] >= freq["W"] else "W"

    if (y2 - y1) % 2 == 0 and (x2 - x1) % 2 == 0:
        y1_list, y2_list, x1_list, x2_list = [], [], [], []

        for i in range(y1 - 1):
            y1_list.append("R")
            y2_list.append("R")

        if y1 > 0:
            y1_list.append("H")
            y2_list.append("H")

        for i in range((y2 - y1) // 2):
            y2_list.append("R")
            y2_list.append("H")

        for i in range(x1 - 1):
            x1_list.append("H")
            x2_list.append("H")

        if x1 > 0:
            x1_list.append("R")
            x2_list.append("R")

        for i in range((x2 - x1) // 2):
            x2_list.append("R")
            x2_list.append("H")

        output = ""
        for c in s:
            if c == y1_key:
                output += y1_list.pop(0)
            elif c == y2_key:
                output += y2_list.pop(0)
            elif c == x1_key:
                output += x1_list.pop(0)
            elif c == x2_key:
                output += x2_list.pop(0)

        if output.count("R") == 0 or output.count("H") == 0:
            print("NO")
        else:
            print(output)

    else:
        print("NO")
