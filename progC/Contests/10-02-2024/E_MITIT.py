t=int(input())
for _ in range(t):
    s=input()
    n=len(s)
    found=False
    for i in range (n):
        a=s[0:i]
        if (len(a)==0):
            continue
        b=s[i:]
        half = len(b) // 2
        b1 = b[:half]
        b2 = b[half:]
        if (b1==b2):
            print("YES")
            found=True
            break
    if (not found):
        print("NO")