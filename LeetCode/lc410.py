def solve(nums, x, m):
    j = 0
    n = len(nums)
    for i in range(m):
        s = 0
        while j < n and s + nums[j] <= x:
            s = s + nums[j]
            j += 1
        if i == m - 1:
            if j == n:
                return True
            else:
                return False
        



class Solution(object):
    def splitArray(self, nums, m):
        """
        :type nums: List[int]
        :type m: int
        :rtype: int
        """
        end = sum(nums)
        beg = end // m - 1
        while beg < end:
            mid = (beg + end) // 2
            if not solve(nums, mid, m):
                beg = mid + 1
            else:
                end = mid
        return end
