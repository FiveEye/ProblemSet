def fat(bc, x):
    if bc[x] == -1:
        return x
    bc[x] = fat(bc, bc[x])
    return bc[x]
def uni(bc, x, y):
    x = fat(bc, x)
    y = fat(bc, y)
    if x == y:
        return
    bc[x] = y
class Solution:
    def getSkyline(self, buildings: List[List[int]]) -> List[List[int]]:
        buildings = sorted(buildings, key=lambda x: x[2], reverse=True)
        xs = set()
        for x, y, c in buildings:
            xs.add(x)
            xs.add(y)
        #print(xs)
        xs = sorted(list(xs))
        N = len(xs) + 1
        dm = {}
        for i, x in enumerate(xs):
            dm[x] = i
        
        h = [0 for i in range(N)]
        bc = [-1 for i in range(N)]
        
        for _x, _y, c in buildings:
            x = dm[_x]
            y = dm[_y]
            x = fat(bc, x)
            while x < y:
                h[x] = c
                uni(bc, x, x+1)
                x = fat(bc, x)
        ans = []
        c = 0
        for i in range(N):
            if h[i] != c:
                ans.append([xs[i], h[i]])
                c = h[i]
        return ans
