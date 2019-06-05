#ifndef leetCode673_hpp
#define leetCode673_hpp

#include <stdio.h>

#endif /* leetCode673_hpp */

vector<int> s[2100];
vector<int> ss[2100];
int n, c[2100], l[2100];


vector<int> longest;

int bs(vector<int> &t, int x, bool check(int, int)) {
    int n = t.size();
    int beg = 0, end = n, mid;
    while(beg < end) {
        mid = (beg + end) / 2;
        if(check(t[mid], x)) {
            beg = mid + 1;
        } else {
            end = mid;
        }
    }
    return end;
}

void print(vector<int> &t) {
    for(int i = 0; i < t.size(); ++i) {
        cout << t[i] << ' ';
    }
    cout << endl;
}

class Solution {
public:
    int findNumberOfLIS(vector<int>& nums) {
        n = nums.size();
        longest.clear();
        for(int i = 0; i <= n; ++i) {
            s[i].clear();
            ss[i].clear();
            ss[i].push_back(0);
        }
        for(int i = 0; i < n; ++i) {
            int tmp = bs(longest, nums[i], [](int x, int y) { return x < y; });
            if(tmp >= longest.size()) {
                longest.push_back(nums[i]);
            } else {
                if(longest[tmp] > nums[i]) {
                    longest[tmp] = nums[i];
                }
            }
            l[i] = tmp;
            
            
            if(tmp == 0) {
                c[i] = 1;
            } else {
                //print(s[tmp-1]);
                //cout << "bs2 " << nums[i] << " " << s[tmp-1].size() - bs2(s[tmp-1], nums[i]) << endl;
                int ssr = bs(s[tmp-1], nums[i], [](int x, int y) { return x >= y; });
                c[i] = ss[tmp-1][s[tmp-1].size()] - ss[tmp-1][ssr];
            }
            
            s[tmp].push_back(nums[i]);
            ss[tmp].push_back(ss[tmp][ss[tmp].size()-1] + c[i]);
            
        }
        //print(longest);
        int m = longest.size() - 1;
        int ans = 0;
        for(int i = 0; i < n; ++i) {
            //cout << '(' << l[i] << ',' << c[i] << ')';
            if(l[i] == m) {
                ans += c[i];
            }
        }
        return ans;
    }
};
