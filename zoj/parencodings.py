import sys
t = int(raw_input())
for i in range(t):
    n = int(raw_input())
    p = list(map(int,raw_input().split(" ")))
    s = ""
    for j in range(len(p)):
        if j == 0:
            s = s + ("(" * p[j])
        else:
            s = s + ("(" * (p[j] - p[j - 1]))
        s = s + ")"
    w = []
    for j in range(len(s)):
        if s[j] == ")":
            rp = 1
            res = 1
            for k in range(j - 1,-1,-1):
                if rp == 0:
                    break
                if s[k] == "(":
                    rp = rp - 1
                else:
                    rp = rp + 1
                    res = res + 1
            w.append(res)
    for j in range(len(w)):
        if j == len(w) - 1:
            #print w[j]
            sys.stdout.write(str(w[j]) + "\n")
        else:
            sys.stdout.write(str(w[j]) + " ")
            #print w[j],'',
