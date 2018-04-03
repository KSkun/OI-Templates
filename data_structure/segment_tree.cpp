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

const int MAXN = 100005, INF = 1e9;

#define lch o << 1
#define rch (o << 1) | 1
#define mid ((l + r) >> 1)

// Segment tree

LL w[MAXN], val[MAXN << 2], tag[MAXN << 2];

// Merge the children's info into root
inline void merge(int o) {
	val[o] = val[lch] + val[rch];
}

// Push the tags down
inline void pushdown(int o, int l, int r) {
	if(tag[o]) {
		tag[lch] += tag[o];
		tag[rch] += tag[o];
		val[lch] += tag[o] * (mid - l + 1);
		val[rch] += tag[o] * (r - mid);
		tag[o] = 0;
	}
}

// Build the tree
inline void build(int o, int l, int r) {
	if(l == r) {
		val[o] = w[l];
		return;
	}
	build(lch, l, mid);
	build(rch, mid + 1, r);
	merge(o);
}

// Add v to elements in [l, r]
inline void add(int o, int l, int r, int ll, int rr, LL v) {
	if(l >= ll && r <= rr) {
		tag[o] += v;
		val[o] += v * (r - l + 1);
		return;
	}
	pushdown(o, l, r);
	if(ll <= mid) add(lch, l, mid, ll, rr, v);
	if(rr > mid) add(rch, mid + 1, r, ll, rr, v);
	merge(o);
}

// Query the sum of elements in [l, r]
inline LL query(int o, int l, int r, int ll, int rr) {
	if(l >= ll && r <= rr) {
		return val[o];
	}
	pushdown(o, l, r);
	LL res = 0;
	if(ll <= mid) res += query(lch, l, mid, ll, rr);
	if(rr > mid) res += query(rch, mid + 1, r, ll, rr);
	return res;
}

// an example of segment tree with lazy tags
// can pass luogu p3372

int n, m, op, x, y;
LL k;

int main() {
	n = readint(); m = readint();
	for(int i = 1; i <= n; i++) w[i] = readint();
	build(1, 1, n);
	while(m--) {
		op = readint(); x = readint(); y = readint();
		if(op == 1) {
			k = readint();
			add(1, 1, n, x, y, k);
		} else {
			printf("%lld\n", query(1, 1, n, x, y));
		}
	}
	return 0;
}
