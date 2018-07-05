// Code by KSkun, 2018/7
#include <cstdio>
#include <cctype>

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

int n;
LL mat[55];

// add an element into "linear basis" set
inline void insert(LL x) {
	for(int i = 50; i >= 0; i--) {
		if(x & (1ll << i)) {
			if(!mat[i]) {
				mat[i] = x; break;
			} else {
				x ^= mat[i];
			}
		}
	}
}

// an example of "linear basis" algorithm
// can pass luogu p3812

int main() {
	n = readint();
	for(int i = 1; i <= n; i++) {
		LL t = readint();
		insert(t);
	}
	LL res = 0;
	for(int i = 50; i >= 0; i--) {
		res = std::max(res, res ^ mat[i]);
	}
	printf("%lld", res);
	return 0;
}