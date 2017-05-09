//http://lx.lanqiao.org/problem.page?gpid=T30
/*
连号区间数

问题描述
小明这些天一直在思考这样一个奇怪而有趣的问题：

在1~N的某个全排列中有多少个连号区间呢？这里所说的连号区间的定义是：

如果区间[L, R] 里的所有元素（即此排列的第L个到第R个元素）递增排序后能得到一个长度为R-L+1的“连续”数列，则称这个区间连号区间。

当N很小的时候，小明可以很快地算出答案，但是当N变大的时候，问题就不是那么简单了，现在小明需要你的帮助。

输入格式
第一行是一个正整数N (1 <= N <= 50000), 表示全排列的规模。

第二行是N个不同的数字Pi(1 <= Pi <= N)， 表示这N个数字的某一全排列。

输出格式
输出一个整数，表示不同连号区间的数目。

样例输入1
4
3 2 4 1
样例输出1
7
样例输入2
5
3 4 2 5 1
样例输出2
9
*/

//Because the last part use a disjoint set, it is near linear time.


#include <stdio.h>
#include <string.h>
#define N 60000
int n, in[N], ind[N];
int stk[N], top;
int LH[N], RH[N];
int LL[N], RL[N], MX[N];

int print_arr(int s[], int n) {
  for(int i = 0; i < n; ++i) printf("%d ", s[i]); puts("");
}

int getfat(int bc[], int x) {
  if(bc[x] == -1) return x;
  return bc[x] = getfat(bc, bc[x]);
}

void uni(int bc[], int x, int y) {
  x = getfat(bc, x);
  y = getfat(bc, y);
  if(x == y) return;
  bc[x] = y;
}

void push(int x) {
  LL[x] = top;
  stk[top++] = x;
}

int count(int x) {
  int y = getfat(RL, x + 1);
  return top - LL[y] - 1;
}

void clear(int x) {
  while(top > 0 && stk[top - 1] <= x) {
    uni(RL, stk[top - 1], stk[top - 2]);
    --top;
  }
}

int main() {
  while(scanf("%d", &n) != EOF) {
    for(int i = 1; i <= n; ++i) {
      scanf("%d", in + i);
      ind[in[i]] = i;
      MX[i] = i;
    }

    top = 0;    
    for(int i = 1; i <= n; ++i) {
      while(top > 0 && stk[top - 1] > in[i]) {
        int j = stk[top - 1];
        RL[j] = i - 1;
        --top;
      }
      if(top == 0) LL[in[i]] = 1;
      else LL[in[i]] = ind[stk[top - 1]] + 1;
      stk[top++] = in[i];
    }
    while(top > 0) {
      int j = stk[top - 1];
      RL[j] = n;
      --top;
    }
    
    top = 0;    
    for(int i = 1; i <= n; ++i) {
      while(top > 0 && stk[top - 1] < in[i]) {
        int j = stk[top - 1];
        RH[j] = in[i];
        --top;
      }
      if(top == 0) LH[in[i]] = n + 1;
      else LH[in[i]] = stk[top - 1];
      stk[top++] = in[i];
    }
    while(top > 0) {
      int j = stk[top - 1];
      RH[j] = n + 1;
      --top;
    }
    
    //for(int i = 1; i <= n; ++i) printf("%d %d %d %d %d\n", i, LL[i], RL[i], LH[i], RH[i]);

    for(int i = n - 1; i >= 1; --i) {
      int j = i + 1;
      while(LL[i] <= ind[j] && ind[j] <= RL[i]) {
        j = MX[j] + 1;
        if(j > n) break;
      }
      MX[i] = j - 1;
    }
    
    //for(int i = 1; i <= n; ++i) printf("%d %d\n", i, MX[i]);
    
    memset(RL, -1, sizeof(RL[0]) * (n + 10));
    
    top = 0;
    
    int ans = 1;
    push(n + 1);
    push(n);
    
    for(int i = n - 1; i >= 1; --i) {
      int tmp = (ind[i + 1] < ind[i] ? LH[i] : RH[i]) - 1;
      clear(tmp);
      push(i);
      //print_arr(stk, top);
      //printf("i %d %d %d %d\n", i, tmp, count(MX[i]), ans);
      ans += count(MX[i]);
    }
    printf("%d\n", ans);
  }
  return 0;
}
