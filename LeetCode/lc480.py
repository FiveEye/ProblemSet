def clean_heap(h, i):
    while len(h) > 0 and h[0][1] < i:
        #print("clean", i, h[0][1])
        heapq.heappop(h)
        
        
n = 0
c = [0, 0]
h = [[],[]]
m = []
s = [0, 0]

def init_heap(nums, k):
    global n, c, h, m, s
    n = len(nums)
    c = [k // 2, k - k // 2]
    h = [[],[]]
    m = [-1 for _ in range(n)]
    s = [0, 0]
    
def my_pop(i):
    #print('pop', i, m[i])
    t = m[i]
    #m[i] = -1
    s[t] -= 1
    clean_heap(h[t], i+1)
    if t == 0:
        (x, j) = heapq.heappop(h[1])
        heapq.heappush(h[0], (-x, j))
        m[j] = 0
        s[0] += 1
        s[1] -=1
        clean_heap(h[1], i+1)
    
    
def my_push(i, x):
    global n, c, h, m, s
    if s[0] < c[0]:
        heapq.heappush(h[0], (-x, i))
        m[i] = 0
        s[0] += 1
        return
    if s[0] > 0 and x < -h[0][0][0]:
        heapq.heappush(h[0], (-x, i))
        m[i] = 0
        x, i = heapq.heappop(h[0])
        x = -x
        m[i] = -1
    if s[1] < c[1]:
        heapq.heappush(h[1], (x, i))
        m[i] = 1
        s[1] += 1
        return
    if x < h[1][0]:
        heapq.heappush(h[1], (x, i))
        heapq.heappop(h[1])
        
        
def get_med(i):
    global n, c, h, m, s
    clean_heap(h[0], i)
    clean_heap(h[1], i)
    if c[0] == c[1]:
        return (h[1][0][0] - h[0][0][0]) / 2
    else:
        return h[1][0][0] * 1.0
    
class Solution:
    def medianSlidingWindow(self, nums: List[int], k: int) -> List[float]:
        global n, c, h, m, s
        init_heap(nums, k)
        
        for i in range(k):
            my_push(i, nums[i])
            #print(i, h)
        ans = [get_med(0)]    
        for i in range(k, n):
            my_pop(i - k)
            my_push(i, nums[i])
            #print(i, h, s)
            ans.append(get_med(i-k))
        return ans
            
