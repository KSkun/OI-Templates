// Code by KSkun, 2018/3
#include <cstdio>

#include <algorithm>

typedef long long LL;

inline char fgc() {
	static char buf[100000], *p1 = buf, *p2 = buf;
	return p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, 100000, stdin), p1 == p2) ? EOF : *p1++;
}

inline LL readint() {
	register LL res = 0, neg = 1;
	char c = fgc();
	while(c < '0' || c > '9') {
		if(c == '-') neg = -1;
		c = fgc();
	}
	while(c >= '0' && c <= '9') {
		res = res * 10 + c - '0';
		c = fgc();
	}
	return res * neg;
}

const int MAXN = 3000005;

int n, p;

inline LL exgcd(LL a, LL b, LL &x, LL &y) {
	if(!b) {
		x = 1; y = 0;
		return a;
	}
	LL res = exgcd(b, a % b, x, y);
	LL t = x; x = y; y = (t - a / b * y) % p;
	return res;
}

// calculate modular multiplicative inverse with extended euclidean alg
// cannot pass luogu p3811 because of O(n log n)

int main() {
	n = readint(); p = readint();
	for(int i = 1; i <= n; i++) {
		LL x, y;
		exgcd(i, p, x, y);
		x = (x % p + p) % p;
		printf("%lld\n", x);
	}
	return 0;
}
