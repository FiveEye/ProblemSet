#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#define N 100100
int n, sa[N], rank[N], sa1[N], rank1[N], rank2[N], cnt[N], h[N];

void computeHeight(char * s) {
    int k;
    for(int i = 0; i < n; ++i) {
        rank[sa[i]] = i;
    }
    h[0] = 0;
    for(int i = 0; i < n; ++i) {
        if(rank[i] == 0) {
            continue;
        }
        if(i == 0 || h[rank[i-1]] <= 1) {
            k = 0;
        } else {
            k = h[rank[i-1]] - 1;
        }
        int j = sa[rank[i] - 1];
        while(i + k < n && j + k < n && s[i+k] == s[j+k]) {
            k++;
        }
        h[rank[i]] = k;
    }
}

void computeSA(char * s) {
    n = strlen(s);
    int m = n > 30 ? n : 30;
    memset(cnt, 0, sizeof(cnt[0]) * m);
    for(int i = 0; i < n; ++i) {
        cnt[s[i] - 'a']++;
    }
    for(int i = 1; i < m; ++i) {
        cnt[i] += cnt[i-1];
    }
    for(int i = 0; i < n; ++i) {
        rank[i] = cnt[s[i] - 'a'] - 1;
    }
    for(int l = 1; l < n; l <<= 1) {
        for(int i = 0; i < n; ++i) {
            rank1[i] = rank[i];
            rank2[i] = i + l < n ? rank[i+l] : 0;
        }
        memset(cnt, 0, sizeof(cnt[0]) * m);
        for(int i = 0; i < n; ++i) {
            cnt[rank2[i]]++;
        }
        for(int i = 1; i < m; ++i) {
            cnt[i] += cnt[i-1];
        }
        for(int i = n-1; i >= 0; --i) {
            sa1[--cnt[rank2[i]]] = i;
        }
        
        memset(cnt, 0, sizeof(cnt[0]) * m);
        for(int i = 0; i < n; ++i) {
            cnt[rank1[i]]++;
        }
        for(int i = 1; i < m; ++i) {
            cnt[i] += cnt[i-1];
        }
        for(int i = n-1; i >= 0; --i) {
            sa[--cnt[rank1[sa1[i]]]]= sa1[i];
        }
        int flag = 1;
        rank[sa[0]] = 1;
        for(int i = 1; i < n; ++i) {
            rank[sa[i]] = rank[sa[i-1]];
            if(rank1[sa[i]] == rank1[sa[i-1]] && rank2[sa[i]] == rank2[sa[i-1]]) {
                flag = 0;
            } else {
                rank[sa[i]]++;
            }
        }
        if(flag) break;
    }
    computeHeight(s);
}

char ans[N];
char * longestDupSubstring(char * S){
    computeSA(S);
    int maxi = 0;
    for(int i = 1; i < n; ++i) {
        if(h[i] > h[maxi]) maxi = i;
    }
    for(int i = 0; i < h[maxi]; ++i) {
        ans[i] = S[sa[maxi] + i];
    }
    ans[h[maxi]] = 0;
    return ans;
}
