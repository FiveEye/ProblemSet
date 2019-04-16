xs = {}
ys = {}
fs = {}
ss = {}
grid = {}

def checkdic(xs, x):
    if x not in xs:
        xs[x] = set()

def checkempty(xs, x):
    if x not in xs:
        return 1
    if len(xs[x]) == 0:
        return 1
    return 0

def remove(x, y):
    if x not in grid:
        return
    if y not in grid[x]:
        return
    grid[x].remove(y)
    xs[x].remove((x,y))
    ys[y].remove((x,y))
    fs[x+y].remove((x,y))
    ss[x-y].remove((x,y))

class Solution:
    def gridIllumination(self, N: int, lamps: List[List[int]], queries: List[List[int]]) -> List[int]:
        global xs, ys, fs, ss, grid
        xs = {}
        ys = {}
        fs = {}
        ss = {}
        grid = {}
        n = len(lamps)
        for l in lamps:
            x = l[0]
            y = l[1]
            if x not in grid:
                grid[x] = {y}
            else:
                grid[x].add(y)
            checkdic(xs, x)
            checkdic(ys, y)
            checkdic(fs, x + y)
            checkdic(ss, x - y)
            xs[x].add((x,y))
            ys[y].add((x,y))
            fs[x+y].add((x,y))
            ss[x-y].add((x,y))
        ans = []
        for q in queries:
            x = q[0]
            y = q[1]
            tmp = checkempty(xs, x) and checkempty(ys, y) and checkempty(fs, x+y) and checkempty(ss, x-y)
            if tmp:
                ans.append(0)
            else:
                ans.append(1)
            remove(x, y-1)
            remove(x, y)
            remove(x, y+1)
            remove(x-1, y-1)
            remove(x-1, y)
            remove(x-1, y+1)
            remove(x+1, y-1)
            remove(x+1, y)
            remove(x+1, y+1)
            
        return ans
            
