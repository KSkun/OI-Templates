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
LL inv[MAXN];

// calculate modular multiplicative inverse with linear algorithm
// can pass luogu p3811

int main() {
	n = readint(); p = readint();
	inv[0] = inv[1] = 1;
	for(int i = 2; i <= n; i++) {
		inv[i] = -(p / i) * inv[p % i] % p;
		if(inv[i] < 0) inv[i] += p;
	}
	for(int i = 1; i <= n; i++) {
		printf("%lld\n", inv[i]);
	}
	return 0;
}
