import queue
dpm = []
dpc = []
dp = []
cm = []
cc = []
c = []
n = 0



def init(graph):
    global dp, dpc, dpm, cm, cc, c, n
    n = len(graph)
    dpm = [ [0 for _ in range(n)] for _ in range(n) ]
    dpc = [ [0 for _ in range(n)] for _ in range(n) ]
    cm = [ [0 for _ in range(n)] for _ in range(n) ]
    cc = [ [0 for _ in range(n)] for _ in range(n) ]
    dp = [dpm, dpc]
    c = [cm, cc]
    
def solve(graph):
    global dp, dpc, dpm, cm, cc, c, n

    q = queue.Queue()
    
    for i in range(0, n):
        dp[0][0][i] = 1
        dp[0][i][0] = 1
        dp[1][0][i] = -1
        
    for i in range(0, n):
        for j in range(0, n):
            for x in graph[i]:
                if dpc[j][x] == 0:
                    cm[i][j] += 1
                if dpm[j][x] == 0:
                    cc[i][j] += 1

    for i in range(1,n):
        dp[1][i][0] = -1
        q.put((1, i, 0))
        
        dp[0][i][i] = -1
        q.put((0, i, i))
        
    for i in range(1,n):
        dp[1][i][i] = 1
        q.put((1, i, i))

            
    while not q.empty():
        p, i, j = q.get()
        #print(p, i, j, dp[p][i][j])
        t = 1 - p
        if dp[p][i][j] == -1:
            for x in graph[j]:
                if dp[t][x][i] != 0:
                    continue
                dp[t][x][i] = 1
                q.put((t, x, i))
        else:
            for x in graph[j]:
                if dp[t][x][i] != 0:
                    continue
                c[t][x][i] -= 1
                if c[t][x][i] == 0:
                    dp[t][x][i] = -1
                    q.put((t,x,i))
class Solution:
    def catMouseGame(self, graph: List[List[int]]) -> int:
        init(graph)
        solve(graph)
        #for i in range(n):
        #    print(dpm[i])
            
        #print('')
        #for i in range(n):
        #    print(dpc[i])
        if dpm[1][2] == 0:
            return 0
        elif dpm[1][2] == -1:
            return 2
        else:
            return 1
