// Code by KSkun, 2018/7
#include <cstdio>
#include <cctype>
#include <cstring>
#include <ctime>
#include <cstdlib>

#include <algorithm>
#include <vector>

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

LL gcd(LL a, LL b) {
	if(!b) return a;
	return gcd(b, a % b);
}

inline LL fpow(LL n, LL k, LL p) {
	LL res = 1;
	for(; k; k >>= 1) {
		if(k & 1) res = res * n % p;
		n = n * n % p;
	}
	return res;
}

inline LL randint(LL lim) {
	return (1ll * rand() * RAND_MAX + rand()) % lim + 1;
}

inline bool miller_rabin(LL x) {
	if(x == 2) return true;
	LL t = x - 1, cnt2 = 0;
	while(!(t & 1)) {
		t >>= 1; cnt2++;
	}
	for(int i = 1; i <= 5; i++) {
		LL now, lst;
		now = lst = fpow(rand() % (x - 1) + 1, t, x);
		for(int j = 1; j <= cnt2; j++) {
			now = lst * lst % x;
			if(now == 1 && lst != 1 && lst != x - 1) return false;
			lst = now;
		}
		if(now != 1) return false;
	}
	return true;
}

inline LL pollard_rho(LL x, LL k) {
	LL a = randint(x - 1), b = a, t1 = 1, t2 = 2;
	for(;;) {
		t1++; a = (a * a % x + k) % x; 
		LL g = gcd(abs(b - a), x);
		if(g > 1 && g < x) return g;
		if(a == b) break;
		if(t1 == t2) {
			b = a; t2 <<= 1;
		}
	}
	return x;
}

std::vector<LL> divi;

inline void calDiv(LL x) {
	if(x == 1) return;
	if(miller_rabin(x)) {
		divi.push_back(x); return;
	}
	LL p = x;
	while(p >= x) p = pollard_rho(x, randint(x - 1));
	calDiv(p);
	calDiv(x / p);
}

// an example of Pollard's Rho Alg
// can pass luogu p1075

LL n, m, t;

int main() {
	srand(time(NULL));
	n = readint();
	calDiv(n);
	printf("%lld\n", *std::max_element(divi.begin(), divi.end()));
	return 0;
}
