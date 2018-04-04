// Code by KSkun, 2018/4
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

const int MAXN = 500005;

int n, m;
LL bit[MAXN];

// Return the last 1 in x (binary)
inline int lowbit(int x) {
	return x & -x;
}

// Add k to element x
inline void add(int x, int k) {
	for(int i = x; i <= n; i += lowbit(i)) {
		bit[i] += k;
	}
}

// Query the sum from 1 to x
inline LL query(int x) {
	LL res = 0;
	for(int i = x; i > 0; i -= lowbit(i)) {
		res += bit[i];
	}
	return res;
}

// an example of binary index tree
// can pass luogu p3374

int op, x, y;

int main() {
	n = readint(); m = readint();
	for(int i = 1; i <= n; i++) {
		x = readint();
		add(i, x);
	}
	while(m--) {
		op = readint(); x = readint(); y = readint();
		if(op == 1) add(x, y);
		else printf("%lld\n", query(y) - query(x - 1));
	}
	return 0;
}
