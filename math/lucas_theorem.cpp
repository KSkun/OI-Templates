// Code by KSkun, 2018/3
#include <cstdio>

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

inline LL fpow(LL n, LL k, LL p) {
	LL res = 1;
	while(k) {
		if(k & 1) res = res * n % p;
		n = n * n % p;
		k >>= 1;
	}
	return res;
}


const int MAXN = 100005;

LL T, n, m, p, mul[MAXN], inv[MAXN];

/*
 * Calculate C(n, m) that n, m < p
 */
inline LL C(LL n, LL m) {
	if(m > n) return 0;
	return mul[n] * inv[n - m] % p * inv[m] % p;
}

/*
 * Recurrently calculate C(n, m) based on Lucas's Theorem
 */
inline LL lucas(LL n, LL m) {
	if(!m) return 1;
	return C(n % p, m % p) * lucas(n / p, m / p) % p;
}

/*
 * Calculate factorial values and their inverses
 */
inline void cal() {
	mul[0] = mul[1] = inv[0] = inv[1] = 1;
	for(int i = 2; i < p; i++) {
		inv[i] = (-(p / i) * inv[p % i] % p + p) % p;
	}
	for(int i = 2; i < p; i++) {
		mul[i] = mul[i - 1] * i % p;
		inv[i] = inv[i - 1] * inv[i] % p;
	}
}

// an example of calculating C(n + m, m) based on Lucas's Theorem
// can pass luogu p3807

int main() {
	T = readint();
	while(T--) {
		n = readint(); m = readint(); p = readint();
		cal();
		// output C(n + m, m) % p
		printf("%lld\n", lucas(n + m, m));
	}
	return 0;
}
