#include <vector>
#include <list>
#include <map>
#include <set>
#include <deque>
#include <stack>
#include <bitset>
#include <algorithm>
#include <functional>
#include <numeric>
#include <utility>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <cstdio>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <cstring>
#include <iterator>
#define FOR(i,a,n) for(int i = (a); i < (int)(n); ++i)
#define foreach(itr,c) for(decltype((c).begin()) itr=(c).begin(); itr != (c).end(); itr++)
#define mp(a,b) make_pair(a,b)

using namespace std;

//typedef __int64 ll;
//typedef unsigned __int64 ull;
typedef long long ll;
typedef unsigned long long ull;

const int N = 10000000;

int a[N], p[N], num = 0;

void Prime(int N, int *a, int *p, int &num) {
    int i, j;
    memset(a, 0, N * sizeof(a[0]));
    num = 0;
    for(i = 2; i < N; ++i) {
        if(!a[i]) a[i] = p[num++] = i;
        for(j = 0; j < num && i * p[j] < N; ++j) {
            a[i * p[j]] = p[j];
            if(!(i % p[j])) break;
        }
    }
}

ll f(ll n) {
  ll ret = 1;
  FOR(i, 0, num) {
    int tmp = 0;
    while(n % p[i] == 0) {
      tmp++;
      n /= p[i];
    }
    ret *= (tmp + 1);
    if(ret > 500) return ret;
  }
  return ret;
}

ll n = 0;

int main() {
  Prime(N, a, p, num);
  int i = 1;
  while(1) {
    n += i;
    i++;
    ll m = f(n);
    printf("n = %lld, f(n) = %lld\n", n, m);
    if(m > 500) {
      printf("ans = %d\n", n);
      break;
    }
  }
  return 0;
}
