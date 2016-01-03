N = 15
s = []
dp = []
for i in range(N):
    s.append(list(map(int, input().split())))
    dp.append([0 for i in range(len(s[i]))])

dp[0][0] = s[0][0]

for i in range(1, N):
    dp[i][0] = dp[i-1][0] + s[i][0]
    dp[i][-1] = dp[i-1][-1] + s[i][-1]
    for j in range(1, len(s[i]) - 1):
        dp[i][j] = s[i][j] + max(dp[i-1][j-1], dp[i-1][j])

print(max(dp[-1]))
