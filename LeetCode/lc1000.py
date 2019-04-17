# import heapq

# class Solution:
    # def mergeStones(self, stones: List[int], K: int) -> int:
        # heapq.heapify(stones)
        # ans = 0
        # while len(stones) >= K:
            # t = 0
            # for _ in range(K):
                # x = heapq.heappop(stones)
                # print(x)
                # t += x
            # ans += t
            # heapq.heappush(stones, t)
        # if len(stones) == 1:
            # return ans
        # return -1


# def find(stones, K):
    # ind = 0
    # ret = 0
    # tmp = 0
    # for i in stones[:K]:
        # ret += i
    # tmp = ret
    # for i in range(K, len(stones)):
        # tmp -= stones[i-K]
        # tmp += stones[i]
        # if tmp < ret:
            # ret = tmp
            # ind = i - K + 1
    # return ind, ret

# class Solution:
    # def mergeStones(self, stones: List[int], K: int) -> int:
        # n = len(stones)
        # if K > 2 and n % (K-1) != 1:
            # return -1
        # ans = 0
        # while True:
            # ind, ret = find(stones, K)
            # ans += ret
            # stones = stones[0:ind] + [ret] + stones[ind+K:]
            # if len(stones) == 1:
                # break
        # return ans

# [6, 4, 4, 6]

def createArray(dims) :
	if len(dims) == 1:
		return [-1 for _ in range(dims[0])]
	return [createArray(dims[1:]) for _ in range(dims[0])]
	

n = 0
sum = []
dp = []
class Solution:
    def mergeStones(self, stones: List[int], K: int) -> int:
        global n, sum, dp
        n = len(stones)
        if K > 2 and n % (K - 1) != 1:
            return -1
        sum = [0 for _ in range(n+1)]
        for i in range(1, n+1):
            sum[i] = sum[i-1]+stones[i-1]
        dp = createArray([n, n])
        for i in range(n):
            for j in range(K-1):
                if i+j >= n:
                    break
                dp[i][i+j] = 0
            if i + K - 1 < n:
                dp[i][i+K-1] = sum[i+K] - sum[i]
        for l in range(K,n):
            for i in range(0, n - l):
                j = i + l
                for k in range(i, j, K-1):
                    #print(i, j, k, dp[i][k], dp[k+1][j])
                    if dp[i][j] == -1 or dp[i][j] > dp[i][k] + dp[k+1][j]:
                        dp[i][j] = dp[i][k] + dp[k+1][j]
                if (j - i + 1) % (K - 1) == 1 or K == 2:
                    dp[i][j] += sum[j+1] - sum[i]
        return dp[0][n-1]
        
        
        
        
        
        
        
        
        
        
        
