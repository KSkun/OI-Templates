// Code by KSkun, 2018/3
#include <cstdio>
#include <cmath>

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

struct Complex {
	double real, imag;
	Complex(double real = 0, double imag = 0): real(real), imag(imag) {}
	inline Complex operator+(const Complex &rhs) const {
		return Complex(real + rhs.real, imag + rhs.imag);
	}
	inline Complex operator-(const Complex &rhs) const {
		return Complex(real - rhs.real, imag - rhs.imag);
	}
	inline Complex operator*(const Complex &rhs) const {
		return Complex(real * rhs.real - imag * rhs.imag, real * rhs.imag + imag * rhs.real);
	}
	inline Complex& operator*=(const Complex &x) {
		return *this = *this * x;
	}
	inline Complex operator/(const double &rhs) const {
		return Complex(real / rhs, imag / rhs);
	}
	inline Complex& operator/=(const double &x) {
		return *this = *this / x;
	}
};

const int MAXN = 1 << 20;
const double PI = std::acos(-1);

int n, m, MO, len, rev[MAXN];
LL x[MAXN], y[MAXN], z[MAXN];
Complex a[MAXN], b[MAXN], c[MAXN], d[MAXN], e[MAXN], f[MAXN], g[MAXN], h[MAXN], wn[MAXN];

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
 * Calculate the root of unity.
 */
inline void calwn() {
	for(int i = 1; i < n; i <<= 1) {
		for(int j = 0; j < i; j++) {
			wn[n / i * j] = Complex(std::cos(PI / i * j), std::sin(PI / i * j));
		}
	}
}

/*
 * Apply FFT to a complex array.
 */
inline void fft(Complex *arr, int f) {
	for(int i = 0; i < n; i++) {
		rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << (len - 1));
	}
	for(int i = 0; i < n; i++) {
		if(i < rev[i]) std::swap(arr[i], arr[rev[i]]);
	}
	for(int i = 1; i < n; i <<= 1) {
		for(int j = 0; j < n; j += i << 1) {
			for(int k = 0; k < i; k++) {
				Complex w = Complex(wn[n / i * k].real, f * wn[n / i * k].imag), 
					x = arr[j + k], y = w * arr[j + k + i];
				arr[j + k] = x + y;
				arr[j + k + i] = x - y;
			}
		}
	} 
	if(f == -1) {
		for(int i = 0; i < n; i++) arr[i] /= n;
	}
}

// an example of FFT on any modulo numbers
// can pass luogu p4245

int main() {
	n = readint(); m = readint(); MO = readint();
	for(int i = 0; i <= n; i++) {
		x[i] = readint() % MO;
	}
	for(int i = 0; i <= m; i++) {
		y[i] = readint() % MO;
	}
	m += n;
	for(n = 1; n <= m; n <<= 1) len++;
	calrev(); calwn();
	// split a number into x * 32768 + y
	for(int i = 0; i < n; i++) {
		a[i].real = x[i] >> 15; b[i].real = x[i] & 0x7fff;
		c[i].real = y[i] >> 15; d[i].real = y[i] & 0x7fff;
	}
	fft(a, 1); fft(b, 1); fft(c, 1); fft(d, 1); // DFT
	for(int i = 0; i < n; i++) {
		e[i] = a[i] * c[i]; f[i] = b[i] * c[i];
		g[i] = a[i] * d[i]; h[i] = b[i] * d[i];
	}
	fft(e, -1); fft(f, -1); fft(g, -1); fft(h, -1); // IDFT
	for(int i = 0; i < n; i++) {
		z[i] = (((((LL(llroundl(e[i].real)) % MO) << 30) % MO + ((LL(llroundl(f[i].real)) % MO) << 15) % MO) % MO +
			((LL(llroundl(g[i].real)) % MO) << 15) % MO) + LL(llroundl(h[i].real)) % MO) % MO;
	}
	for(int i = 0; i <= m; i++) {
		printf("%lld ", z[i]);
	}
	return 0;
}
