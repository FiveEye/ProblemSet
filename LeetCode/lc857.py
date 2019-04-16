from queue import PriorityQueue
class Solution:
    def mincostToHireWorkers(self, quality, wage, K):
        """
        :type quality: List[int]
        :type wage: List[int]
        :type K: int
        :rtype: float
        """
        ratio = [(w / q, q) for q, w in zip(quality, wage)]
        ratio = sorted(ratio, key=lambda rq: rq[0])
        cur = 0
        sm = 0
        k = 0
        best = -1
        queue = PriorityQueue()
        for r,q in ratio:
            if k < K:
                sm += q
                cur = r
                k+=1
                queue.put(-q)
                continue
            if best == -1 or best > sm * cur:
                best = sm * cur
            
                
            m = -queue.get()
            
            if m > q:
                queue.put(-q)
                sm = sm - m + q
                cur = r
                if best == -1 or sm * cur < best:
                    best = sm * cur
            else:
                queue.put(-m)
        if best == -1 or best > sm * cur:
                best = sm * cur   
        return best
                
                
            
