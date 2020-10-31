def fat(s, x):
    if s[x] == -1:
        return x
    s[x] = fat(s, s[x])
    return s[x]

def uni(s, x, y):
    x = fat(s, x)
    y = fat(s, y)
    if x == y:
        return False
    s[x] = y
    return True

def create_bc(n):
    s = [-1 for i in range(n)]
    _fat = lambda x: fat(s, x)
    _uni = lambda x, y: uni(s, x, y)
    return _fat, _uni

def get_ind_func(m):
    return lambda x, y: x * m + y

def get_check_func(n, m):
    def check(x, y):
        if x < 0 or x >= n or y < 0 or y >= m:
            return 1
        if x == 0 or x == n-1 or y == 0 or y == m-1:
            return 0
        return -1
    return check

class Solution:
    def trapRainWater(self, heightMap: List[List[int]]) -> int:
        n = len(heightMap)
        m = len(heightMap[0])
        ind = get_ind_func(m)
        check = get_check_func(n, m)
        fat, uni = create_bc(n*m)
        
        h = [-1 for i in range(n*m)]
        s = []
        for i in range(n):
            for j in range(m):
                s.append((i,j, heightMap[i][j]))
                if check(i,j) == 0:
                    x = ind(i, j)
                    h[x] = heightMap[i][j]
                        
        s = sorted(s, key=lambda p: p[2])

        dx = [-1, 1, 0, 0]
        dy = [0, 0, -1, 1]
        for x,y,z in s:
            i = ind(x,y)
            nps = []
            for k in range(4):
                nx = x + dx[k]
                ny = y + dy[k]
                if check(nx, ny) == 1:
                    continue
                if heightMap[nx][ny] > z:
                    continue
                j = ind(nx, ny)
                nps.append((nx, ny, fat(j)))
            done = False if h[i] == -1 else True
            for nx, ny, j in nps:
                if h[j] != -1:
                    done = True
            
            if done:
                for nx, ny, j in nps:
                    if h[j] == -1:
                        h[j] = z
                if h[i] == -1:
                    h[i] = z
            else:
                for nx, ny, j in nps:
                    uni(j, i)
        ans = 0
        for x in range(n):
            for y in range(m):
                i = fat(ind(x,y))
                ans += h[i] - heightMap[x][y]
        return ans
                
                
            
            
