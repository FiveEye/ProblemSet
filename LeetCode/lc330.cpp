#include <iostream>
#include <vector>

using namespace std;

class Solution {
private:
  long long now;
  int ret;
  void update(long long n) {
    while(now < n) {
      now += now + 1;
      ret++;
    }
    now += n + 1;
  }
    
public:
  int minPatches(vector<int>& nums, int n) {
    now = 0;
    ret = 0;
    int m = 0;
    while(m < nums.size() && nums[m] <= n) ++m;
    for(int i = 0; i < m; ++i) {
      update(nums[i] - 1);
    }
    update(n);
    return ret;  
  }
};

int main() {
  int n = 2147483647;
  vector<int> nums;
  nums.clear();
  nums.push_back(1);
  nums.push_back(2);
  nums.push_back(31);
  nums.push_back(33);
  Solution s;
  cout << s.minPatches(nums, n) << endl;
  return 0;
  
}
