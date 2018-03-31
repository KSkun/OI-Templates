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
};

const int MAXN = 1 << 22;
const double PI = std::acos(-1);

int n, m, len, rev[MAXN];
Complex a[MAXN], b[MAXN], c[MAXN];

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
 * Apply FFT to a complex array.
 */
inline void fft(Complex *arr, int f) {
	for(int i = 0; i < n; i++) {
		if(i < rev[i]) std::swap(arr[i], arr[rev[i]]);
	}
	for(int i = 1; i < n; i <<= 1) {
		Complex wn(std::cos(PI / i), f * std::sin(PI / i));
		for(int j = 0; j < n; j += i << 1) {
			Complex w(1, 0);
			for(int k = 0; k < i; k++) {
				Complex x = arr[j + k], y = w * arr[j + k + i];
				arr[j + k] = x + y;
				arr[j + k + i] = x - y;
				w *= wn;
			}
		}
	} 
}

// an example of FFT
// can pass luogu p3803

int main() {
	n = readint(); m = readint();
	for(int i = 0; i <= n; i++) {
		a[i].real = readint();
	}
	for(int i = 0; i <= m; i++) {
		b[i].real = readint();
	}
	m += n;
	for(n = 1; n <= m; n <<= 1) len++;
	calrev();
	fft(a, 1); fft(b, 1); // DFT
	for(int i = 0; i <= n; i++) c[i] = a[i] * b[i];
	fft(c, -1); // IDFT
	for(int i = 0; i <= m; i++) {
		printf("%d ", int(c[i].real / n + 0.5));
	}
	return 0;
}
