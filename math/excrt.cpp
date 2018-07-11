// Code by KSkun, 2018/7
#include <cstdio>
#include <cctype>
#include <cstring>
#include <cmath>

#include <algorithm>

typedef long long LL;

inline char fgc() {
	static char buf[100000], *p1 = buf, *p2 = buf;
	return p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, 100000, stdin), p1 == p2)
		? EOF : *p1++;
}

inline LL readint() {
	register LL res = 0, neg = 1; register char c = fgc();
	for(; !isdigit(c); c = fgc()) if(c == '-') neg = -1;
	for(; isdigit(c); c = fgc()) res = (res << 1) + (res << 3) + c - '0';
	return res * neg;
}

inline LL exgcd(LL a, LL b, LL &x, LL &y) {
	if(!b) {
		x = 1; y = 0; return a;
	}
	LL res = exgcd(b, a % b, x, y);
	LL t = x; x = y; y = t - a / b * y;
	return res;
}

const int MAXN = 100005;

LL n, a[MAXN], p[MAXN];

inline LL excrt() {
	LL A = a[1], P = p[1], x, y;
	for(int i = 2; i <= n; i++) {
		LL g = exgcd(P, p[i], x, y);
		if((a[i] - A) % g) return -1;
		x = (a[i] - A) / g * x; 
		LL m = p[i] / g; x = (x % m + m) % m;
		A = P * x + A; P = P / g * p[i]; A %= P;
	}
	return A;
}

// an example of exCRT

int main() {
	while(scanf("%lld", &n) != EOF) {
		for(int i = 1; i <= n; i++) {
			scanf("%lld%lld", &p[i], &a[i]);
		}
		printf("%lld\n", excrt());
	}
	return 0;
}