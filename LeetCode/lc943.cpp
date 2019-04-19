
int n;
int d[16][16];
int dp[1 << 12][16];
int path[1 << 12][16];


int f(string a, string b){
	int n = a.length(), m = b.length();
	for(int i = 0; i < n; ++i) {
		int j = 0;
		while(j < m && i + j < n && a[i+j] == b[j]) {
			++j;
		}
		if(j == m) return 0;
		if(i+j == n) return m - j;
	}
	return m;
}
char ans[512];

class Solution {
public:
    string shortestSuperstring(vector<string>& A) {
		n = A.size();
		for(int i = 0; i < n; ++i) {
			for(int j = 0; j < n; ++j) {
				if(i != j) d[i][j] = f(A[i], A[j]);
			}
		}
		memset(dp, 0, sizeof(dp));
		for(int i = 0; i < n; ++i) {
			dp[1 << i][i] = A[i].length();
		}
		for(int i = 1; i < (1 << n); ++i) {
			for(int j = 0; j < n; ++j) {
				if(dp[i][j] == 0) continue;
				for(int l = 0; l < n; ++l) {
					if(i & (1 << l)) continue;
					int nxt = i | (1 << l);
					if(dp[nxt][l] == 0 || dp[nxt][l] > dp[i][j] + d[j][l]) {
						dp[nxt][l] = dp[i][j] + d[j][l];
						path[nxt][l] = j;
					}
				}
			}
		}
		int p = (1 << n) - 1;
		int q = 0;
		for(int i = 0; i < n; ++i) {
			if(dp[p][q] == 0 || dp[p][i] < dp[p][q]) {
				q = i;
			}
		}
		int len = dp[p][q];
		ans[len] = 0;
		while(p) {
			int pq = path[p][q];
			int pp = p ^ (1 << q);
			int plen = dp[pp][pq];
			int aql = A[q].length();
			//printf("%d %d\n", len, plen);
			for(int i = 0; i < len - plen; ++i) {
				ans[len - 1 - i] = A[q][aql - 1 - i];
			}
			p = pp;
			q = pq;
			len = plen;
		}
		//printf("%s\n", ans);
		return string(ans);
    }
};
