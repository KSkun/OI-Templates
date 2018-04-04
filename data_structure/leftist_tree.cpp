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

const int MAXN = 100005;

struct Node {
	int fa, val, dis, ch[2];
} tr[MAXN];

// Find the root of the heap which contains p
inline int findrt(int p) {
	while(tr[p].fa) p = tr[p].fa;
	return p;
}

// Merge two heaps
inline int merge(int u, int v) {
	if(!u || !v) return u + v;
	if(tr[u].val > tr[v].val) std::swap(u, v);
#ifdef ONLINE_JUDGE
	if(tr[u].val == tr[v].val && u > v) std::swap(u, v); // not necessary
#endif
	tr[u].ch[1] = merge(tr[u].ch[1], v);
	tr[tr[u].ch[1]].fa = u;
	if(tr[tr[u].ch[0]].dis < tr[tr[u].ch[1]].dis) std::swap(tr[u].ch[0], tr[u].ch[1]);
	tr[u].dis = tr[tr[u].ch[1]].dis + 1;
	return u;
}

inline bool isleft(int p) {
	return tr[tr[p].fa].ch[0] == p;
}

// Erase a node from the heap
inline void erase(int p) {
	int q = merge(tr[p].ch[0], tr[p].ch[1]);
	tr[q].fa = tr[p].fa; if(tr[p].fa) tr[tr[p].fa].ch[!isleft(p)] = q;
	memset(tr + p, 0, sizeof(Node));
	tr[p].val = -1;
	for(int i = tr[q].fa; i; i = tr[i].fa) {
		if(tr[tr[i].ch[0]].dis < tr[tr[i].ch[1]].dis) std::swap(tr[i].ch[0], tr[i].ch[1]);
		if(tr[i].dis == tr[tr[i].ch[1]].dis + 1) break;
		tr[i].dis = tr[tr[i].ch[1]].dis + 1;
	}
}

// an example of leftist tree
// can pass luogu p3377

int n, m, op, x, y;

int main() {
	tr[0].dis = -1;
	n = readint(); m = readint();
	for(int i = 1; i <= n; i++) tr[i].val = readint();
	while(m--) {
		op = readint(); x = findrt(readint());
		if(op == 1) {
			y = findrt(readint());
			if(tr[x].val == -1 || tr[y].val == -1 || x == y) continue;
			merge(x, y);
		} else {
			printf("%d\n", tr[x].val);
			erase(x);
		}
	}
	return 0;
}
