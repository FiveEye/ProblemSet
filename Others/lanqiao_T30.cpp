//http://lx.lanqiao.org/problem.page?gpid=T30

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

    for(int i = N - 1; i >= 1; --i) {
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
