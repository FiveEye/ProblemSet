class Solution:
    def countOrders(self, n: int) -> int:
        MOD = 10**9+7
        if n == 1:
            return 1
        return self.countOrders(n-1) * n * (2 * n-1) % MOD
        
