#include <stdio.h>
#include <string.h>
#include <algorithm>
using namespace std;

char s[100];

void reverse(char *s, int n) {
  for(int i = 0; i < n/2; ++i) {
    swap(s[i], s[n - 1 - i]);
  }
}

int solve() {
  int n = strlen(s);
  int i, j;
  for(i = n - 2; i >= 0; --i) {
    if(s[i] < s[i + 1]) break;
  }
  if(i == -1) return 0;
  for(j = n - 1; j > i; --j) {
    if(s[j] > s[i]) break; 
  }
  swap(s[i], s[j]);
  reverse(s + i + 1, n - i - 1);
  return 1;
}

int main() {
  while(scanf("%s", s) != EOF) {
    if(s[0] == '#') return 0;
    int ans = solve();
    if(!ans) puts("No Successor");
    else puts(s);
  }
  return 0;
}
