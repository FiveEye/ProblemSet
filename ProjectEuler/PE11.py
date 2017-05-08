s = []
dir = [[0,1],[1,0],[1,1],[-1,1]]

for i in range(20):
    s.append(list(map(int, input().split())))

print(s)

ans = 0

def f(x, y, dx, dy):
    global ans
    ret = 1
    for i in range(4):
        if x >= 20 or y >= 20: return
        ret *= s[x][y]
        x += dx
        y += dy
    if ret > ans: ans = ret


for i in range(20):
    for j in range(20):
        for l in range(len(dir)):
            f(i, j, dir[l][0], dir[l][1])

print("ans = ", ans)
