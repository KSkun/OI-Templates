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

const int MAXN = 200005;

int n, m;

#define mid ((l + r) >> 1)

struct Node {
	int lch, rch, siz;
} sgt[MAXN * 30];
int rt[MAXN], tot;

// Insert a single number into the tree
inline void insert(int &o, int l, int r, int x) {
	sgt[++tot] = sgt[o]; o = tot; sgt[o].siz++;
	if(l == r) return;
	if(x <= mid) insert(sgt[o].lch, l, mid, x);
	else insert(sgt[o].rch, mid + 1, r, x);
}

// Query the k-th number in an interval
inline int query(int o1, int o2, int l, int r, int rk) {
	if(l == r) return l;
	int siz = sgt[sgt[o2].lch].siz - sgt[sgt[o1].lch].siz;
	if(rk <= siz) return query(sgt[o1].lch, sgt[o2].lch, l, mid, rk);
	else return query(sgt[o1].rch, sgt[o2].rch, mid + 1, r, rk - siz);
}

// an example of hjt persistant segment tree (store history versions)
// can pass luogu p3834

int a[MAXN], l, r, k;
std::vector<int> vec;

int main() {
	n = readint(); m = readint();
	for(int i = 1; i <= n; i++) {
		vec.push_back(a[i] = readint());
	}
	vec.push_back(-2e9);
	std::sort(vec.begin(), vec.end());
	vec.erase(std::unique(vec.begin(), vec.end()), vec.end());
	for(int i = 1; i <= n; i++) {
		insert(rt[i] = rt[i - 1], 1, vec.size() - 1, std::lower_bound(vec.begin(), vec.end(), a[i]) - vec.begin());
	}
	while(m--) {
		l = readint(); r = readint(); k = readint();
		printf("%d\n", vec[query(rt[l - 1], rt[r], 1, vec.size() - 1, k)]);
	}
	return 0;
}
