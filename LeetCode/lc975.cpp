#include <map>
#include <string.h>
using namespace std;
int n, ans;
map<int, int> lst;
int dp[20010][2];
class Solution {
public:
    int oddEvenJumps(vector<int>& A) {
		n = A.size();
		ans = 1;
		lst.clear();
		memset(dp, 0, sizeof(dp));
		dp[n-1][0] = dp[n-1][1] = 1;
		lst[A[n-1]] = n-1;
		for(int i = n - 2; i > -1; --i) {
			int nxt;
			map<int, int>::iterator it = lst.lower_bound(A[i]);
			if(it != lst.end()) {
				nxt = (*it).second;
				dp[i][0] = dp[nxt][1];
			} else {
				dp[i][0] = 0;
			}
			
			if((*it).first != A[i] && it != lst.begin()) --it;
			if((*it).first <= A[i]) {
				nxt = (*it).second;
				dp[i][1] = dp[nxt][0];
			} else {
				dp[i][1] = 0;
			}
			ans += dp[i][0];
			lst[A[i]] = i;
		}
		return ans;
    }
};
