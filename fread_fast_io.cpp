// Code by KSkun, 2018/3
#include <cstdio>

typedef long long LL;

/*
 * Using fread to accelerate input, the same as getchar()
 * @return single char from input
 */
inline char fgc() {
	static char buf[100000], *p1 = buf, *p2 = buf;
	return p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, 100000, stdin), p1 == p2) ? EOF : *p1++;
}


/*
 * Using fgc() read a single 64-bit integer
 * @return what we read
 */
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

// an example of using readint()
// you should input an EOF signal to end the proccess
// Ctrl+Z means EOF signal on Windows system

LL n;

int main() {
	n = readint();
	// output what we read
	printf("%lld", n);
	return 0;
}
