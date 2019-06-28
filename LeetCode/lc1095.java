/**
 * // This is the MountainArray's API interface.
 * // You should not implement it, or speculate about its implementation
 * class MountainArray {
 *   public:
 *     int get(int index);
 *     int length();
 * };
 */

int n;
int s[11000];

int getTop(MountainArray &mountainArr) {
    int l = 0, r = n;
    while(l < r) {
        int m1 = l + (r-l)/3, m2 = l + (r-l)/3*2;
        int t1 = mountainArr.get(m1);
        int t2 = mountainArr.get(m2);
        if(t1 < t2) {
            l = m1 + 1;
        } else if(t1 > t2) {
            r = m2;
        } else {
            l = m1 + 1;
            r = m2;
        }
    }
    return l;
}

int solve(MountainArray &mountainArr, int x, int a, int b, int order) {
    int beg = a, end = b;
    while(beg < end) {
        int mid = beg + (end - beg) / 2;
        int t = mountainArr.get(mid);
        if(order) {
            if(t < x) {
                beg = mid + 1;
            } else {
                end = mid;
            }
        } else {
            if(t > x) {
                beg = mid + 1;
            } else {
                end = mid;
            }
        }
    }
    if(beg >= 0 && beg < n && mountainArr.get(beg) == x)
        return beg;
    return -1;
}

class Solution {
public:
    int findInMountainArray(int target, MountainArray &mountainArr) {
        n = mountainArr.length();
        int top = getTop(mountainArr);
        //cout << top << endl;
        int ans = solve(mountainArr, target, 0, top+1, 1);
        if(ans != -1) return ans;
        ans = solve(mountainArr, target, top, n, 0);
        return ans;
    }
};
