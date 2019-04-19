#include <stdio.h>
#include <string.h>
#include <vector>
int n, m, dp[1010][1010];


class Solution {
public:
    vector<int> movesToStamp(string stamp, string target) {
		vector<int> ret;
        n = stamp.length();
		m = target.length();
		vector<int> front, back;
		ret.clear();
		front.clear();
		back.clear();
		memset(dp, 0, sizeof(dp));
		if(stamp[0] == target[0]) {
			dp[0][0] = 1;
		} else {
			return ret;
		}
		for(int i = 0; i < m - 1; ++i) {
			int flag = 0;
			for(int j = 0; j < n; ++j) {
				if(dp[i][j] != 0) {
					flag = j+1;
                } else if(dp[i][n-1] != 0) {
					flag = n;
                } else {
					continue;
				}
                if(j == n - 1) continue;
				if(target[i+1] == stamp[j+1]) {
					if(dp[i][j] != 0) {
						dp[i+1][j+1] = j+2;
					} else {
						dp[i+1][j+1] = -j-2;
					}
				}
			}
			if(flag == 0) {
                printf("flag0 %d\n", i);
				return ret;
			}
			if(target[i+1] == stamp[0]) {
				dp[i+1][0] = flag;
			}
		}
        /*
		for(int i = 0; i < m; ++i) {
			for(int j = 0; j < n; ++j) {
				printf("%2d ", dp[i][j]);
			}
			printf("\n");
		}
        */
        if(dp[m-1][n-1] == 0) {
            return ret;
        }
		int j = n - 1;
		for(int i = m - 1; i >= 0; --i) {
            //printf("ij %d %d\n", i, j);
			if(j == 0 && dp[i][j] > 0) {
				back.push_back(i);
				j = dp[i][j] - 1;
				continue;
			}
			if(dp[i][j] > 0) {
				--j;
			} else {
				front.push_back(i + dp[i][j] + 1);
				j = n - 1;
			}
		}
		for(int i = 0; i < front.size(); ++i) {
			ret.push_back(front[i]);
		}
		for(int i = 0; i < back.size(); ++i) {
			ret.push_back(back[back.size() - 1 - i]);
		}
		return ret;
    }
};

