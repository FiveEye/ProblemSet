def createArray(dims) :
	if len(dims) == 1:
		return [0 for _ in range(dims[0])]
	return [createArray(dims[1:]) for _ in range(dims[0])]


	
class Solution:
    def countTriplets(self, A: List[int]) -> int:
        n = len(A)
        A = sorted(A)
        dp = createArray([2**16, 4])
        #for i in range(n):
        #    for j in range(2**16):
        #        for k in range(2, 0, -1):
        #            if dp[j][k] == 0:
        #                continue
        #            dp[j&A[i]][k+1] += dp[j][k]
        #    dp[A[i]][1] += 1
        #print(dp[0][1], dp[0][2], dp[0][3])
        mm = 1
        for i in range(n):
            j = 0
            while j < mm:
                t = j & A[i]
                if t == 0:
                    if dp[j][2] != 0:
                        dp[j&A[i]][3] += dp[j][2]
                    j += 1
                else:
                    j += (t&(-t))
            for j in range(0, i):
                dp[A[i]&A[j]][2] += 1
            dp[A[i]][1] += 1
            if A[i] >= mm:
                mm = A[i] + 1
        #print(dp)
        #print(dp[0][1], dp[0][2], dp[0][3])
        return dp[0][1] + dp[0][2] * 6 + dp[0][3] * 6
        
