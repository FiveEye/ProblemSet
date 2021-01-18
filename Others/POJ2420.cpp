#include <stdio.h>
#include <math.h>

#define R 10000
#define eps 1e-3
const double pi=acos(-1.0);
const double delta = pi/4;

int n;
double s[10010][2];

double x, y;

double calc(double x, double y) {
    double ans = 0;
    for(int i = 0; i < n; ++i) {
        double xx = (s[i][0] - x) * (s[i][0] - x);
        double yy = (s[i][1] - y) * (s[i][1] - y);
        ans += sqrt(xx + yy);
    }
    return ans;
}


int solve() {
    double ans = calc(x, y);
    
    double rate = 0.6, step = rate * R;
    double cx, cy;
    while(step > eps) {
        for(double theta = 0; theta < 2*pi + eps; theta += delta) {
			cx = x + step*cos(theta);
			cy = y + step*sin(theta);
			double tmp = calc(cx, cy);
			if(tmp < ans) {
			    ans = tmp;
			    x = cx;
			    y = cy;
			}
		}
		step *= rate;
    }
    return ans + 0.5;
}



int main() {
    while(scanf("%d", &n) != EOF) {
        x = 0, y = 0;
        for(int i = 0; i < n; ++i) {
            scanf("%lf%lf", s[i], s[i] + 1);
            x += s[i][0];
            y += s[i][1];
        }
        x /= n;
        y /= n;
        printf("%d\n", solve());
    }
    return 0;
}
