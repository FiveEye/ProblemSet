#include <string.h>
#define MOD 1000000007
unsigned int dp[2010][27];
int n, s[2010];

int distinctSubseqII(char* S) {
    memset(dp, 0, sizeof(dp));
	n = strlen(S);
	for(int i = 0; i < n; ++i) {
		s[i+1] = S[i] - 'a';
	}
	dp[0][26] = 1;
	for(int i = 1; i < n+1; ++i) {
		for(int j = 0; j < 27; ++j) {
			if(s[i] != j) {
				dp[i][j] = dp[i-1][j];
			}
			dp[i][s[i]] += dp[i-1][j];
			dp[i][s[i]] %= MOD;
		}
	}
	unsigned int ans = 0;
	for(int i = 0; i < 26; ++i) {
		ans = (ans + dp[n][i]) % MOD;
	}
	return (int)ans;
}
