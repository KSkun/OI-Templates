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

inline LL fpow(LL n, LL k, LL p) {
	LL res = 1; n %= p;
	for(; k; k >>= 1) {
		if(k & 1) res = res * n % p;
		n = n * n % p;
	}
	return res;
}

const int MAXN = 15;

int n, a[MAXN], p[MAXN];

inline LL crt() {
	LL pprod = 1, res = 0;
	for(int i = 1; i <= n; i++) {
		pprod = pprod * p[i];
	}
	for(int i = 1; i <= n; i++) {
		LL pi = pprod / p[i];
		res += 1ll * a[i] * pi % pprod * fpow(pi, p[i] - 2, p[i]) % pprod;
		res %= pprod;
	}
	return res;
}

// an example of Chinese Remainder Theorem

int main() {
	n = readint();
	for(int i = 1; i <= n; i++) {
		p[i] = readint(); a[i] = readint();
	}
	printf("%lld", crt());
	return 0;
}