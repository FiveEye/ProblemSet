class Solution:
    def countOrders(self, n: int) -> int:
        MOD = 1000000007
        dp = [[0 for _ in range(n+1)] for _ in range(n+1)]
        dp[0][0] = 1
        for i in range(n+1):
            for j in range(n+1):
                if dp[i][j] == 0:
                    continue
                if i < j:
                    continue
                if j < n:
                    dp[i][j+1] += dp[i][j] * (i - j)
                    dp[i][j+1] %= MOD
                if i < n:
                    dp[i+1][j] += dp[i][j]
                    dp[i+1][j] %= MOD
        ans = dp[n][n]
        #print(dp)
        for i in range(1,n+1):
            ans *= i
            ans %= MOD
        return ans
        
