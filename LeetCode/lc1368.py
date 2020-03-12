def dfs(grid, step, y, x, k):
    n = len(grid)
    m = len(grid[0])
    dy = [0, 0, -1, 1]
    dx = [-1, 1, 0, 0]
    for i in range(4):
        ny = y + dy[i]
        nx = x + dx[i]
        if nx < 0 or nx >= m or ny < 0 or ny >= n:
            continue
        if grid[ny][nx] != i+1:
            if step[ny][nx] == -1:
                step[ny][nx] = k+1
        else:
            if step[ny][nx] >= 0 and step[ny][nx] <= k:
                continue
            step[ny][nx] = k
            dfs(grid, step, ny, nx, k)
    
class Solution:
    def minCost(self, grid: List[List[int]]) -> int:
        n = len(grid)
        m = len(grid[0])
        step = [[-1 for _ in range(m)] for _ in range(n)]
        step[-1][-1] = 0
        k = 0
        while step[0][0] == -1:
            for i in range(n):
                for j in range(m):
                    if step[i][j] == k:
                        dfs(grid, step, i, j, k)
            #print(k, step)
            k += 1
        
        return step[0][0]
