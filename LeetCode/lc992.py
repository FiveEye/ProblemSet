def add(s, i, x):
    n = len(s)
    while i < n:
        s[i] += x
        i += (i&(-i))

def get(s, i):
    ret = 0
    while i != 0:
        ret += s[i]
        i -= (i&(-i))
    return ret

def find(s, k):
    n = len(s)
    beg = 0
    end = n
    tt = get(s, n-1)
    while beg < end:
        mid = (beg + end) // 2
        t = get(s, mid)
        if tt - t >= k:
            beg = mid + 1
        else:
            end = mid
    return end

def findR(s, k):
    n = len(s)
    tt = get(s, n-1)
    tk = tt - k
    if tk < 0:
        return 0
    i = 0
    w = 1
    while w * 2 < n:
        w *= 2
    while w > 0:
        while i+w >= n or s[i+w] > tk:
            w //= 2
            if w == 0:
                break
        if w == 0:
            break
        tk -= s[i+w]
        i += w
        w //= 2
    #print("findR tk:", tk, i+1)

    return i+1
        

class Solution:
    def subarraysWithKDistinct(self, A: List[int], K: int) -> int:
        n = len(A)
        #print(n)
        pre = [-1 for _ in range(n+10)]
        lst = [-1 for _ in range(n+10)]
        for i in range(n):
            pre[i] = lst[A[i]]
            lst[A[i]] = i
        
        s = [0 for _ in range(n+10)]
        for i in range(n+1):
            if lst[i] == -1:
                continue
            add(s, lst[i]+1, 1)
        
        ans = 0
        
        for i in range(n-1, -1, -1):
            #print("i:", i)
            #for j in range(n+1):
            #    print(j, get(s, j))
            #print("findR:", findR(s, K), findR(s, K+1))
            #print("find:", find(s, K), find(s, K+1))
            if get(s, len(s) - 1) < K:
                break
            ans += findR(s, K) - findR(s, K+1)
            add(s, i+1, -1)
            if pre[i] != -1:
                add(s, pre[i]+1, 1)
        return ans
