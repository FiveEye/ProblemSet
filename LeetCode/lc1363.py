class Solution:
    def largestMultipleOfThree(self, digits: List[int]) -> str:
        digits = sorted(digits, reverse = True)
        ans = [0, -1, -1]
        flag = [0, 0, 0]
        for x in digits:
            nans = ans.copy()
            for i in range(3):
                if ans[i] == -1:
                    continue
                tmp = ans[i] * 10 + x
                if nans[(x + i) % 3] <= tmp:
                    nans[(x + i) % 3] = tmp
                    flag[(x + i) % 3] = 1
            ans = nans
        if flag[0] == 1:
            return str(ans[0])
        else:
            return ""
