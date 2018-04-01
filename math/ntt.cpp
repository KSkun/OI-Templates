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

const int MAXN = 1 << 22, G = 3, MO = 998244353;

int n, m, len, rev[MAXN];
LL a[MAXN], b[MAXN], c[MAXN];

/*
 * Calculate the inverse of every number in binary.
 * For example: 0001's inverse is 1000
 */
inline void calrev() {
	for(int i = 0; i < n; i++) {
		rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << (len - 1));
	}
}

/*
 * Fast pow.
 */ 
inline LL fpow(LL n, LL k) {
	LL res = 1;
	while(k) {
		if(k & 1) res = res * n % MO;
		n = n * n % MO;
		k >>= 1;
	}
	return res;
}

/*
 * Apply NTT to a complex array.
 */
inline void ntt(LL *arr, int f) {
	for(int i = 0; i < n; i++) {
		if(i < rev[i]) std::swap(arr[i], arr[rev[i]]);
	}
	for(int i = 1; i < n; i <<= 1) {
		LL gn = fpow(G, (MO - 1) / (i << 1));
		if(f == -1) gn = fpow(gn, MO - 2);
		for(int j = 0; j < n; j += i << 1) {
			LL w = 1;
			for(int k = 0; k < i; k++) {
				LL x = arr[j + k], y = w * arr[j + k + i] % MO;
				arr[j + k] = (x + y) % MO;
				arr[j + k + i] = ((x - y) % MO + MO) % MO;
				w = w * gn % MO;
			}
		}
	}
}

// an example of NTT
// can pass luogu p3803

int main() {
	n = readint(); m = readint();
	for(int i = 0; i <= n; i++) {
		a[i] = readint();
	}
	for(int i = 0; i <= m; i++) {
		b[i] = readint();
	}
	m += n;
	for(n = 1; n <= m; n <<= 1) len++;
	calrev();
	ntt(a, 1); ntt(b, 1); // DFT
	for(int i = 0; i < n; i++) c[i] = a[i] * b[i];
	ntt(c, -1); // IDFT
	LL invn = fpow(n, MO - 2);
	for(int i = 0; i <= m; i++) {
		printf("%d ", c[i] * invn % MO);
	}
	return 0;
}
