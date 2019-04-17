import math

def createArray(dims) :
	if len(dims) == 1:
		return [-1 for _ in range(dims[0])]
	return [createArray(dims[1:]) for _ in range(dims[0])]
	
n = 0
g = []
ans = 0
mark = []

dp = []

count = {}

def encode():
    ret = 0
    w = 1
    for i in range(n):
        if mark[i]:
            ret += w
        w *= 2
    return ret

def dfs(x):
    y = encode()
    #print("dfs:", y, x)
    if dp[y][x] != -1:
        return dp[y][x]
    dp[y][x] = 0
    for i in range(n):
        if mark[i] == 1 or g[x][i] != 1:
            continue
        mark[i] = 1
        dp[y][x] += dfs(i)
        mark[i] = 0
    return dp[y][x]

def f():
    ret = 1
    for k,v in count.items():
        for i in range(2, v+1):
            ret *= i
    return ret
    

class Solution:
    def numSquarefulPerms(self, A: List[int]) -> int:
        global n, g, ans, mark, dp, count
        
        n = len(A)
        g = createArray([n,n])
        for i in range(n):
            for j in range(i+1, n):
                sum = A[i] + A[j]
                sq = int(math.sqrt(sum))
                if sq * sq == sum:
                    g[i][j] = g[j][i] = 1
                else:
                    g[i][j] = g[j][i] = 0
        #print(g)
        
        mark = [0 for _ in range(n)]
        
        dp = createArray([2**n, n])
        
        for i in range(n):
            dp[2**n-1][i] = 1
        
        ans = 0
        for i in range(n):
            mark[i] = 1
            ans += dfs(i)
            mark[i] = 0
        
        count = {}
        for x in A:
            if x not in count:
                count[x] = 1
            else:
                count[x] += 1
        
        
        print(dp, ans, f())
        return ans // f()
