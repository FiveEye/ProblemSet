class Solution:
    def subarraysWithKDistinct(self, A: List[int], K: int) -> int:
        n = len(A)
        #print(n)
        pre = [-1 for _ in range(n+10)]
        lst = [-1 for _ in range(n+10)]
        for i in range(n):
            pre[i] = lst[A[i]]
            lst[A[i]] = i
        
        s = [0 for _ in range(n)]
        for i in range(n+1):
            if lst[i] == -1:
                continue
            s[lst[i]] = 1
            
        
        ans = 0        
        p = n
        k = K
        while p >= 0 and k > 0:
            p -= 1
            k -= s[p]
        q = p - 1
        while q >= 0 and s[q] == 0:
            q -= 1
        for i in range(n-1, -1, -1):
            if p < 0:
                break
            #print(s)
            #print(i, p, q)
            ans += p - q
            j = pre[i]
            s[i] = 0
            s[j] = 1
            if p < j:
                continue
            elif q < j and j < p:
                p = j
                continue
            else:
                p = q
                q = p - 1
                while q >= 0 and s[q] == 0:
                    q -= 1
        
        return ans
