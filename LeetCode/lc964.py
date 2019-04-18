mem = {}
x = 0
def bound(n):
    w = 0
    t = x
    while t < n:
        t *= x
        w += 1
    return w

def chkmin(x, y):
    if x == -1 or x > y:
        return y
    return x
def dfs(n):
    #print("dfs:", n)
    if n in mem:
        #print("in mem", mem[n])
        if mem[n] != -2:
            return mem[n]
    mem[n] = -2
    addc = n // x + dfs(n % x)
    w = 0
    t = x
    while t * x <= n:
        t *= x
        w += 1
    timec = w + 1 + dfs(n - t)
    ret = min(addc, timec)
    t *= x
    w += 1
    #print(n, ret, w + 1 + bound(t - n))
    if w + 1 + bound(t - n) < ret:
        #if t - n in mem :
        #    print("t-n in mem", t - n, mem[t - n])
        if t - n not in mem or mem[t - n] != -2:
            ret = min(ret, w + 1 + dfs(t - n))
    mem[n] = ret
    return mem[n]


class Solution(object):
    def leastOpsExpressTarget(self, X, target):
        """
        :type x: int
        :type target: int
        :rtype: int
        """
        global mem, x
        x = X
        mem = {}
        mem[0] = -1
        mem[1] = 1
        for i in range(2, x):
            mem[i] = min(i + i - 1, (x - i) * 2)
        mem[x] = 0
        return dfs(target)
