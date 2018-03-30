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

/*
 * Fast pow with modulo, calculate n^k mod p. O(n log n)
 * @return n^k mod p
 */
inline LL fpow(LL n, LL k, LL p) {
	LL res = 1;
	while(k) {
		if(k & 1) res = res * n % p;
		n = n * n % p;
		k >>= 1;
	}
	return res;
}

// an example of calculationg n^k mod p

LL n, k, p;

int main() {
	n = readint(); k = readint(); p = readint();
	printf("%lld", fpow(n, k, p));
	return 0;
}
