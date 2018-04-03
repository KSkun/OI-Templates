// Code by KSkun, 2018/4
#include <cstdio>
#include <cstring>

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

const int MAXN = 100005, INF = 1e9;

// Splay tree

struct Node {
	int fa, ch[2], val, siz, cnt;
	bool rev;
} tr[MAXN];

int tot = 0, sta[MAXN], stop = 0, rt = 0;

// Update the info of p
inline void update(int p) {
	int lch = tr[p].ch[0], rch = tr[p].ch[1];
	tr[p].siz = tr[lch].siz + tr[rch].siz + tr[p].cnt;
}

// Apply reversal to p
inline void reverse(int p) {
	std::swap(tr[p].ch[0], tr[p].ch[1]);
	tr[p].rev ^= 1;
}

// Push the tag info down to children
inline void pushdown(int p) {
	if(tr[p].rev) {
		if(tr[p].ch[0]) reverse(tr[p].ch[0]);
		if(tr[p].ch[1]) reverse(tr[p].ch[1]);
		tr[p].rev ^= 1;
	}
}

// Return a new node's number
inline int newnode() {
	int p;
	if(stop) p = sta[--stop];
	else p = ++tot;
	memset(tr + p, 0, sizeof(Node));
	return p;
}

// Recycle the memory of p
inline void delnode(int p) {
	sta[stop++] = p;
}

// If p is its father's left child
inline bool isleft(int p) {
	return tr[tr[p].fa].ch[0] == p;
}

// Apply a rotation to p
inline void rotate(int p) {
	bool t = !isleft(p); int fa = tr[p].fa, ffa = tr[fa].fa;
	tr[p].fa = ffa; if(ffa) tr[ffa].ch[!isleft(fa)] = p;
	tr[fa].ch[t] = tr[p].ch[!t]; tr[tr[fa].ch[t]].fa = fa;
	tr[p].ch[!t] = fa; tr[fa].fa = p;
	update(fa);
	if(!tr[p].fa) rt = p;
}

// Splay p until its father is tar
inline void splay(int p, int tar) {
	for(int fa = tr[p].fa; fa != tar; rotate(p), fa = tr[p].fa) {
		if(tr[fa].fa != tar) rotate(isleft(fa) == isleft(p) ? fa : p);
	}
	update(p);
}

// Query the k-th number in the tree
inline int queryn(int rk) {
	int p = rt;
	for(;;) {
		pushdown(p);
		if(tr[p].ch[0] && rk <= tr[tr[p].ch[0]].siz) {
			p = tr[p].ch[0];
		} else {
			rk -= tr[tr[p].ch[0]].siz;
			if(rk <= tr[p].cnt) {
				return p;
			}
			rk -= tr[p].cnt;
			p = tr[p].ch[1];
		}
	}
}

int w[MAXN];

// Build the splay tree
inline int build(int fa, int l, int r) {
	if(l > r) return 0;
	int mid = (l + r) >> 1, p = newnode();
	tr[p].val = w[mid];
	tr[p].fa = fa;
	tr[p].ch[0] = build(p, l, mid - 1);
	tr[p].ch[1] = build(p, mid + 1, r);
	tr[p].cnt = 1;
	update(p);
	return p;
}

inline void dfs(int p) {
	pushdown(p);
	if(tr[p].ch[0]) dfs(tr[p].ch[0]);
	if(tr[p].val != -INF && tr[p].val != INF) {
		printf("%d ", tr[p].val);
	}
	if(tr[p].ch[1]) dfs(tr[p].ch[1]);
}

// an example of splay tree with reverse tag
// can pass luogu p3391

int n, m, l, r;

int main() {
	n = readint(); m = readint();
	for(int i = 2; i <= n + 1; i++) {
		w[i] = i - 1;
	}
	w[1] = -INF; w[n + 2] = INF;
	rt = build(0, 1, n + 2);
	while(m--) {
		l = queryn(readint()); r = queryn(readint() + 2);
		splay(l, 0);
		splay(r, l);
		reverse(tr[tr[rt].ch[1]].ch[0]);
	}
	dfs(rt);
	return 0;
}
