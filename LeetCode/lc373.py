from heapq import heappush, heappop

class Solution:
    def kSmallestPairs(self, nums1: List[int], nums2: List[int], k: int) -> List[List[int]]:
        if len(nums1) == 0 or len(nums2) == 0:
            return []
        nums1 = sorted(nums1)
        nums2 = sorted(nums2)
        heap = []
        for i, x in enumerate(nums1):
            heappush(heap, (x + nums2[0], i, 0))
        
        ans = []
        for i in range(k):
            if len(heap) == 0:
                break
            s, i, j = heappop(heap)
            ans.append([nums1[i],nums2[j]])
            if j+1 < len(nums2):
                heappush(heap, (nums1[i] + nums2[j+1], i, j+1))
        return ans
