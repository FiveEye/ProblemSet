#include<string.h>
int dp[1 << 20][20];
int n, m, s, t, tss;

int dx[4] = {1, -1, 0, 0};
int dy[4] = {0, 0, 1, -1};

class Solution {
public:
    int uniquePathsIII(vector<vector<int>>& grid) {
        n = grid.size();
		m = grid[0].size();
		tss = 0;
		memset(dp, 0, sizeof(dp));
		for(int i = 0; i < n; ++i) {
			for(int j = 0; j < m; ++j) {
				if(grid[i][j] != -1) {
					tss |= (1 << (i * m + j));
				}
				if(grid[i][j] == 1) {
					s = i * m + j;
				} else if(grid[i][j] == 2) {
					t = i * m + j;
				}
			}
		}
		dp[1 << s][s] = 1;
		int ss = 1 << (n * m);
		int nm = n * m;
		for(int i = 0; i < ss; ++i) {
			for(int j = 0; j < nm; ++j) {
				if(dp[i][j] == 0) continue;
				int x = j / m, y = j % m;
				for(int k = 0; k < 4; ++k) {
					int nx = x + dx[k];
					int ny = y + dy[k];
					if(nx < 0 || nx >=n || ny < 0 || ny >= m) continue;
					if(grid[nx][ny] == -1) continue;
					int ni = nx * m + ny;
					if(i & (1 << ni)) continue;
					dp[i | (1 << ni)][ni] += dp[i][j];
				}
			}				
		}
		return dp[tss][t];
    }
};
