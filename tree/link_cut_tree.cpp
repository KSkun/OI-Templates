// Code by KSkun, 2018/4
#include <cstdio>

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

const int MAXN = 300005;

// Link-Cut Tree

struct Node {
	int ch[2], fa, val, xsum; // xsum: xor sum
	bool rev; // reverse tag
} tr[MAXN];

// Check if p is the left child of its father
inline bool isleft(int p) {
	return tr[tr[p].fa].ch[0] == p;
}

// Check if p is the root of the splay tree
inline bool isroot(int p) {
	return tr[tr[p].fa].ch[0] != p && tr[tr[p].fa].ch[1] != p;
}

// Update p info
inline void update(int p) {
	tr[p].xsum = tr[p].val ^ tr[tr[p].ch[0]].xsum ^ tr[tr[p].ch[1]].xsum;
}

// Apply reversal to p
inline void reverse(int p) {
	std::swap(tr[p].ch[0], tr[p].ch[1]);
	tr[p].rev ^= 1;
}

// Push tags down to children of p
inline void pushdown(int p) {
	if(tr[p].rev) {
		if(tr[p].ch[0]) reverse(tr[p].ch[0]);
		if(tr[p].ch[1]) reverse(tr[p].ch[1]);
		tr[p].rev ^= 1;
	}
}

int sta[MAXN], stop;

// Push tags down from root to p
inline void pushto(int p) {
	stop = 0;
	while(!isroot(p)) {
		sta[stop++] = p;
		p = tr[p].fa;
	}
	sta[stop++] = p;
	while(stop) {
		pushdown(sta[--stop]);
	}
}

// Rotate function of splay tree
inline void rotate(int p) {
	bool t = !isleft(p); int fa = tr[p].fa, ffa = tr[fa].fa;
	tr[p].fa = ffa; if(!isroot(fa)) tr[ffa].ch[!isleft(fa)] = p;
	tr[fa].ch[t] = tr[p].ch[!t]; tr[tr[fa].ch[t]].fa = fa;
	tr[p].ch[!t] = fa; tr[fa].fa = p;
	update(fa);
}

// Splay function of splay tree
inline void splay(int p) {
	pushto(p);
	for(int fa = tr[p].fa; !isroot(p); rotate(p), fa = tr[p].fa) {
		if(!isroot(fa)) rotate(isleft(fa) == isleft(p) ? fa : p);
	}
	update(p);
}

// Make the path from root to p a preferred path
inline void access(int p) {
	for(int q = 0; p; q = p, p = tr[p].fa) {
		splay(p);
		tr[p].ch[1] = q;
		update(p);
	}
}

// Make p as the root
inline void makert(int p) {
	access(p);
	splay(p);
	reverse(p);
}

// Find the root of the LCT
inline int findrt(int p) {
	access(p);
	splay(p);
	while(tr[p].ch[0]) p = tr[p].ch[0];
	return p;
}

// Split the path from u to v
inline void split(int u, int v) {
	makert(u);
	access(v);
	splay(v);
}

// Link u and v
inline void link(int u, int v) {
	split(u, v);
	tr[u].fa = v;
}

// Cut the link between u and v
inline void cut(int u, int v) {
	split(u, v);
	if(tr[v].ch[0] != u || tr[u].ch[1]) return;
	tr[u].fa = tr[v].ch[0] = 0;
}

// Modify the info of u
inline void modify(int u, int w) {
	access(u);
	splay(u);
	tr[u].val = w;
	update(u);
}

// an example of LCT
// can pass luogu p3690

int n, m, op, x, y;

int main() {
	n = readint(); m = readint();
	for(int i = 1; i <= n; i++) {
		tr[i].val = tr[i].xsum = readint();
	}
	while(m--) {
		op = readint(); x = readint(); y = readint();
		switch(op) {
		case 0:
			split(x, y);
			printf("%d\n", tr[y].xsum);
			break;
		case 1:
			link(x, y);
			break;
		case 2:
			cut(x, y);
			break;
		case 3:
			modify(x, y);
		}
	}
	return 0;
}
