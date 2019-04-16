# class Solution:
    # def numDupDigitsAtMostN(self, N: int) -> int:
        # N += 1
        # if N <= 10:
            # return 0
        # d = [0 for _ in range(15)]
        # d[0] = 9
        # for i in range(1, 12):
            # d[i] = d[i-1] * 9
        # n = N
        # t = []
        # d[-1] = 1
        # while n != 0:
            # t.append(n % 10)
            # n //= 10
        # m = len(t)
        # print(d[0:m], t, m)
        # ans = 0
        # for i in range(m - 1, -1, -1):
            # if i == m - 1:
                # ans += d[i-1] // 9 * 10
                # ans += (t[i] - 1) * d[i-1]
            # else:
                # #if t[i] > 0 and t[i+1] != 0:
                # #    ans += d[i-1] / 10 * 9
                # print(i, t[i], t[i+1], d[i-1])
                # if t[i] <= t[i+1]:
                    # ans += t[i] * d[i-1]
                # else :
                    # ans += (t[i] - 1) * d[i-1]
                # if t[i] == t[i+1]:
                    # break
            # print(i, N, ans)
        # return N - ans

def A(n, m):
    if m > n:
        return 0
    ret = 1
    for i in range(m):
        ret *= (n - i)
    return ret

class Solution:
    def numDupDigitsAtMostN(self, N: int) -> int:
        N += 1
        if N <= 10:
            return 0
        n = N
        t = []
        while n != 0:
            t.append(n % 10)
            n //= 10
        m = len(t)
        ans = 0
        #print(t, m)
        mark = [0 for _ in range(10)]
        x = 10
        for i in range(m - 1, -1, -1):
            if i == m-1:
                for j in range(1, m):
                    ans += A(10, j) - A(9, j - 1)
                ans += (t[i] - 1) * A(9, i)
                mark[t[i]] = 1
                x -= 1
            else:
                #print("mark:", i, mark)
                for j in range(t[i]):
                    if mark[j] == 1:
                        continue
                    ans += A(x - 1, i)
                if mark[t[i]] == 1:
                    break
                mark[t[i]] = 1
                x -= 1
            print(i, ans)
        return N - ans - 1
