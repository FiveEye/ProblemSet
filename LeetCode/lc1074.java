int n, m;
int s[310][310];
map<int, int> h;

inline int get_sum(int x, int y, int i) {
    return s[y][i] - s[x][i];
}
int solve(int x, int y, int t) {
    int ret = 0;
    h.clear();
    h[0] = 1;
    for(int i = 1; i <= m; ++i) {
        int tmp = get_sum(x, y, i);
        auto iter = h.find(tmp - t);
        if(iter != h.end()) {
            ret += iter->second;
        }
        h[tmp]++;
    }
    return ret;
    
}
class Solution {
public:
    int numSubmatrixSumTarget(vector<vector<int>>& matrix, int target) {
        n = matrix.size();
        m = matrix[0].size();
        
        for(int i = 0; i < n; ++i) {
            for(int j = 0; j < m; ++j) {
                s[i+1][j+1] = s[i+1][j] + s[i][j+1] - s[i][j] + matrix[i][j];
            }
        }
        int ans = 0;
        for(int i = 0; i < n; ++i) {
            for(int j = i+1; j <= n; ++j) {
                ans += solve(i, j, target);
            }
        }
        return ans;
    }
};
