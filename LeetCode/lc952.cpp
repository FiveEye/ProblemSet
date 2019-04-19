#include<string.h>

int a[100010], p[100010], num;

int Prime(int N, int *a, int *p, int &num) {
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
    return num;
}

int _num = Prime(100010, a, p, num);


int bc[20010], h[100010];

int get(int x) {
	if(bc[x] == -1) return x;
	return bc[x] = get(bc[x]);
}

void uni(int x, int y) {
	x = get(x);
	y = get(y);
	if(x == y) return;
	bc[y] = x;
}


class Solution {
public:
    int largestComponentSize(vector<int>& A) {
        int n = A.size();
		memset(bc, -1, sizeof(bc[0]) * n);
		memset(h, -1, sizeof(h));
		for(int i = 0; i < n; ++i) {
			int x = A[i];
			while(x != 1) {
				if(h[a[x]] == -1) {
					h[a[x]] = i;
				} else {
					uni(h[a[x]], i);
				}
				x /= a[x];
			}
		}
		memset(h, 0, sizeof(h[0]) * n);
		int ans = 1;
		for(int i = 0; i < n; ++i) {
			int tmp = ++h[get(i)];
			if(tmp > ans) ans = tmp;
		}
		return ans;
    }
};
