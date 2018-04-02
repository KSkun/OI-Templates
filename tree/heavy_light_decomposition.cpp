// Code by KSkun, 2018/4
#include <cstdio>

#include <algorithm>
#include <vector>

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

const int MAXN = 100005;

int n, m, r, p, dfn[MAXN], ptn[MAXN], w[MAXN];
std::vector<int> gra[MAXN];

// Segment Tree

#define lch o << 1
#define rch (o << 1) | 1
#define mid ((l + r) >> 1)

LL val[MAXN << 2], tag[MAXN << 2];

inline void pushdown(int o, int l, int r) {
	if(tag[o]) {
		tag[lch] = (tag[lch] + tag[o]) % p;
		tag[rch] = (tag[rch] + tag[o]) % p;
		val[lch] = (val[lch] + tag[o] * (mid - l + 1) % p) % p;
		val[rch] = (val[rch] + tag[o] * (r - mid) % p) % p;
		tag[o] = 0;
	}
}

inline void merge(int o) {
	val[o] = (val[lch] + val[rch]) % p;
}

inline void build(int o, int l, int r) {
	if(l == r) {
		val[o] = w[ptn[l]];
		return;
	}
	build(lch, l, mid);
	build(rch, mid + 1, r);
	merge(o);
}

inline void add(int o, int l, int r, int ll, int rr, LL v) {
	if(l >= ll && r <= rr) {
		val[o] = (val[o] + v * (r - l + 1) % p) % p;
		tag[o] = (tag[o] + v) % p;
		return;
	}
	pushdown(o, l, r);
	if(ll <= mid) add(lch, l, mid, ll, rr, v);
	if(rr > mid) add(rch, mid + 1, r, ll, rr, v);
	merge(o);
}

inline LL query(int o, int l, int r, int ll, int rr) {
	if(l >= ll && r <= rr) {
		return val[o];
	}
	pushdown(o, l, r);
	LL res = 0;
	if(ll <= mid) res = (res + query(lch, l, mid, ll, rr)) % p;
	if(rr > mid) res = (res + query(rch, mid + 1, r, ll, rr)) % p;
	return res;
}

int fa[MAXN], siz[MAXN], dep[MAXN], top[MAXN], son[MAXN], clk;

/*
 * Collect tree info.
 */
inline void dfs1(int u) {
	siz[u] = 1;
	for(int v : gra[u]) {
		if(v == fa[u]) continue;
		fa[v] = u;
		dep[v] = dep[u] + 1;
		dfs1(v);
		siz[u] += siz[v];
		if(siz[v] > siz[son[u]]) son[u] = v;
	}
}

/*
 * Give every node number.
 */
inline void dfs2(int u, int tp) {
	dfn[u] = ++clk;
	ptn[dfn[u]] = u;
	top[u] = tp;
	if(son[u]) {
		dfs2(son[u], tp);
	}
	for(int v : gra[u]) {
		if(v == fa[u] || v == son[u]) continue;
		dfs2(v, v);
	}
}

inline void add(int x, int y, LL z) {
	int tx = top[x], ty = top[y];
	while(tx != ty) {
		if(dep[tx] > dep[ty]) {
			std::swap(x, y);
			std::swap(tx, ty);
		}
		add(1, 1, n, dfn[ty], dfn[y], z);
		y = fa[ty];
		ty = top[y];
	}
	if(dep[x] > dep[y]) {
		std::swap(x, y);
	}
	add(1, 1, n, dfn[x], dfn[y], z);
}

// Path function

inline LL query(int x, int y) {
	int tx = top[x], ty = top[y];
	LL res = 0;
	while(tx != ty) {
		if(dep[tx] > dep[ty]) {
			std::swap(x, y);
			std::swap(tx, ty);
		}
		res = (res + query(1, 1, n, dfn[ty], dfn[y])) % p;
		y = fa[ty];
		ty = top[y];
	}
	if(dep[x] > dep[y]) {
		std::swap(x, y);
	}
	res = (res + query(1, 1, n, dfn[x], dfn[y])) % p;
	return res;
}

// Sub-tree function

inline void add(int x, LL z) {
	add(1, 1, n, dfn[x], dfn[x] + siz[x] - 1, z);
}

inline LL query(int x) {
	return query(1, 1, n, dfn[x], dfn[x] + siz[x] - 1);
}

// an example of HLD
// can pass luogu p3384

int op, x, y, z;

int main() {
	n = readint(); m = readint(); r = readint(); p = readint();
	for(int i = 1; i <= n; i++) w[i] = readint();
	for(int i = 1; i < n; i++) {
		x = readint(); y = readint();
		gra[x].push_back(y);
		gra[y].push_back(x);
	}
	dfs1(r);
	dfs2(r, r);
	build(1, 1, n);
	while(m--) {
		op = readint();
		x = readint();
		if(op <= 2) y = readint();
		if(op == 1 || op == 3) z = readint();
		switch(op) {
		case 1:
			add(x, y, z);
			break;
		case 2:
			printf("%lld\n", query(x, y));
			break;
		case 3:
			add(x, z);
			break;
		case 4:
			printf("%lld\n", query(x));
		}
	}
	return 0;
}
