def createArray(dims) :
	if len(dims) == 1:
		return [0 for _ in range(dims[0])]
	return [createArray(dims[1:]) for _ in range(dims[0])]
	

def f(A, x, y):
    m = len(A)
    for i in range(m):
        if A[i][x] > A[i][y]:
            return 0
    return 1

class Solution(object):
    def minDeletionSize(self, A):
        """
        :type A: List[str]
        :rtype: int
        """
        n = len(A[0])
        g = createArray([n, n])
        for i in range(n):
            for j in range(i+1, n):
                g[i][j] = f(A, i, j)
        dp = createArray([n])
        for i in range(0, n):
            dp[i] = 1
            for j in range(0, i):
                if g[j][i] == 1:
                    if dp[i] < dp[j] + 1:
                        dp[i] = dp[j] + 1
        return n - max(dp)
            
