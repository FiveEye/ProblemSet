//http://lx.lanqiao.org/problem.page?gpid=T30
//Wrong code! But AC!
//we should use a disjoint set instead of a queue

#include <stdio.h>
#include <string.h>
#define N 60000
int n, in[N], ind[N];
int stk[N], top;
int LH[N], RH[N];
int LL[N], RL[N], MX[N];
int q[2 * N], beg, end, np;

void print_q() {
  printf("qu ");
  for(int i = beg; i < end; ++i) printf("%d ", q[i]); puts("");
}

void push_front(int x) {
  q[--beg] = x;
}

int count(int x) {
  if(np == -1) np = beg;
  while(np < end && q[np] <= x) ++np;
  return np - beg;
}

void clear(int x) {
  while(beg < end && q[beg] <= x) ++beg;
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

    for(int i = N - 1; i >= 1; --i) {
      int j = i + 1;
      while(LL[i] <= ind[j] && ind[j] <= RL[i]) {
        j = MX[j] + 1;
        if(j > n) break;
      }
      MX[i] = j - 1;
    }
    //for(int i = 1; i <= n; ++i) printf("%d %d\n", i, MX[i]);
  
    beg = end = n;
    np = -1;
  
    int ans = 1;
    push_front(n);
  
    for(int i = n - 1; i >= 1; --i) {
      int tmp = (ind[i + 1] < ind[i] ? LH[i] : RH[i]) - 1;
      clear(tmp);
      push_front(i);
      //printf("%d %d %d %d\n", i, MX[i], ans, tmp);
      //print_q();
      if(MX[i] == i) {
        ans += 1;
      } else {
        ans += count(MX[i]);
      }
    }
    printf("%d\n", ans);
  }
  return 0;
}
