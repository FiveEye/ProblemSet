class Solution(object):
    def getMoneyAmount(self, n):
        """
        :type n: int
        :rtype: int
        """
        dp = [[0 for x in range(n+1)] for y in range(n+1)]
        for i in range(2,n+1):
            for x in range(n):
                if x + i > n:
                    break
                dp[x][x+i] = x+1 + dp[x+1][x+i]
                for j in range(x+1, x+i):
                    tmp = max(dp[x][j], dp[j+1][x+i]) + (j+1)
                    if tmp < dp[x][x+i]:
                        dp[x][x+i] = tmp
        print(dp[0])
        return dp[0][n]
