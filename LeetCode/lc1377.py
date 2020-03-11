def dfs(g, par, cur, target, t):
    if par == -1:
        m = len(g[cur])
    else:
        m = len(g[cur]) - 1
    if t == 0 or m == 0:
        if cur == target:
            return 1.0
        else:
            return 0.0
    for nxt in g[cur]:
        if nxt == par:
            continue
        ret = dfs(g, cur, nxt, target, t - 1)
        if ret > 0:
            return 1.0 / m * ret
    return 0.0
class Solution:

    def frogPosition(self, n: int, edges: List[List[int]], t: int, target: int) -> float:
        g = {}
        for i in range(n):
            g[i+1] = []
        
        for e in edges:
            g[e[0]].append(e[1])
            g[e[1]].append(e[0])
        print(g)    
        return dfs(g, -1, 1, target, t)
        
