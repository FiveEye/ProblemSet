def Prime(a):
    p = []
    N = len(a)
    for i in range(N):
        a[i] = 0
    num = 0
    for i in range(2,N):
        if a[i] == 0:
            a[i] = i
            p.append(i)
            num += 1
        j = 0
        while j < num and i * p[j] < N:
            a[i * p[j]] = p[j]
            if i % p[j] == 0:
                break
            j += 1
    return p

N = 28124

a = [0 for i in range(N+10)]
p = Prime(a)

def f(n):
    ret = 1
    for i in p:
        tmp = i
        while n % tmp == 0:
            tmp *= i
        ret *= (tmp - 1) // (i - 1)
    return ret - n

ans = 0

s = [0 for i in range(N)]
for i in range(1, N):
    if f(i) > i:
        s[i] = 1

for i in range(1, 28124):
    flag = 1
    for j in range(1, i//2 + 1):
        if s[j] + s[i - j] == 2: 
            flag = 0
            break
    if flag == 1:
        ans += i

print(ans)
