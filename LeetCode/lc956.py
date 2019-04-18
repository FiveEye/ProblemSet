# class Solution(object):
    # def tallestBillboard(self, rods):
        # """
        # :type rods: List[int]
        # :rtype: int
        # """
        # rods = sorted(rods, reverse=True)
        # total = sum(rods)
        # ss = sum(rods)
        # n = len(rods)
        # s = sum(rods) // 2 + 1
        # #print("s", s)
        # dp = [set() for i in range(s)]
        # dp[0].add(0)
        # for x in rods:
            # for i in range(min(ss - total, s-1), -1, -1):
                # dpi = set()
                # for j in sorted(dp[i]):
                    # if i + total < j:
                        # break
                    # dpi.add(j)

                    # if i + x < s:
                        # if i + x <= j:
                            # dp[i+x].add(j)
                        # else:
                            # if i == j:
                                # dpi.add(i+x)
                            # else:
                                # dp[j].add(i+x)
                    # if j + x < s:
                        # if i <= j + x:
                            # dpi.add(j+x)
                        # else:
                            # print("err")
                            # dp[j+x].add(i)
                # dp[i] = dpi
                # #for j in range(s-1, -1, -1):
                # #    if dp[i][j] == 1:
                # #        if i+x < s:
                # #            dp[i+x][j] = 1
                # #        if j+x < s:
                # #            dp[i][j+x] = 1
            # total -= x
        # ans = 0
        # for i in range(0, s):
            # if i in dp[i]:
                # ans = i
        # return ans
        
def update(dp, i, x):
    if i not in dp or dp[i] < x:
        dp[i] = x
class Solution(object):
    def tallestBillboard(self, rods):
        """
        :type rods: List[int]
        :rtype: int
        """
        rods = sorted(rods, reverse=True)
        total = sum(rods)
        n = len(rods)
        s = sum(rods) // 2 + 1
        #print("s", s)
        dp = {}
        dp[0] = 0
        for x in rods:
            ndp = {}
            for k,v in dp.iteritems():
                update(ndp, k, v)
                update(ndp, k+x, v+x)
                update(ndp, abs(k-x), v+x)
            dp = ndp
        return dp[0] // 2
