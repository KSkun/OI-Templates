// Code by KSkun, 2018/4
#include <cstdio>
#include <cstring>

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

const int MAXN = 100005, INF = 1e9;

struct Edge {
	int to, w, nxt;
} gra[MAXN << 1], grao[MAXN << 1];
int head[MAXN], heado[MAXN], tot, toto;

inline void addedge(int u, int v, int w) {
	gra[tot] = Edge {v, w, head[u]}; head[u] = tot++;
	gra[tot] = Edge {u, w, head[v]}; head[v] = tot++;
}

inline void addedgeo(int u, int v, int w) {
	grao[toto] = Edge {v, w, heado[u]}; heado[u] = toto++;
	grao[toto] = Edge {u, w, heado[v]}; heado[v] = toto++;
}

int n, m, has[10000005], siz[MAXN], ct, ctsiz;
bool del[MAXN];

/*
 * Rebuild the tree into a binary tree
 */
inline void rebuild(int u, int f) {
	int ff = 0;
	for(int i = heado[u]; ~i; i = grao[i].nxt) {
		int v = grao[i].to, w = grao[i].w;
		if(v == f) continue;
		if(!ff) {
			addedge(u, v, w);
			ff = u;
		} else {
			int k = ++n;
			addedge(ff, k, 0);
			addedge(k, v, w);
			ff = k;
		}
		rebuild(v, u);
	}
}

inline void calsiz(int u, int f) {
	siz[u] = 1;
	for(int i = head[u]; ~i; i = gra[i].nxt) {
		int v = gra[i].to;
		if(v == f || del[i >> 1]) continue;
		calsiz(v, u);
		siz[u] += siz[v];
	}
}

/*
 * Find the center edge of a tree.
 */ 
inline void findct(int u, int f, int tot) {
	for(int i = head[u]; ~i; i = gra[i].nxt) {
		int v = gra[i].to;
		if(v == f || del[i >> 1]) continue;
		findct(v, u, tot);
		int vsiz = std::max(siz[v], tot - siz[v]);
		if(vsiz < ctsiz) {
			ct = i;
			ctsiz = vsiz;
		}
	}
}

std::vector<int> diss[2];

inline void caldis(int u, int f, int d, int side) {
	diss[side].push_back(d);
	for(int i = head[u]; ~i; i = gra[i].nxt) {
		int v = gra[i].to, w = gra[i].w;
		if(v == f || del[i >> 1]) continue;
		caldis(v, u, d + w, side);
	}
}

inline void work(int e) {
	int u = gra[e].to, v = gra[e ^ 1].to;
	diss[0].clear(); diss[1].clear();
	caldis(u, 0, 0, 0); caldis(v, 0, 0, 1);
	for(int i : diss[0]) {
		for(int j : diss[1]) {
			has[i] = has[j] = has[i + gra[e].w + j] = true;
		}
	}
}

/*
 * Divide the problem into smaller trees.
 */
inline void divide(int u) {
	calsiz(u, 0);
	ct = -1; ctsiz = INF; findct(u, 0, siz[u]);
	if(ct == -1) return;
	del[ct >> 1] = true;
	int x = gra[ct].to, y = gra[ct ^ 1].to;
	work(ct);
	divide(x); divide(y);
}

// an example of tree DAC alg based on edges.
// can pass luogu p3806

int a, b, c;

int main() {
	memset(head, -1, sizeof(head));
	memset(heado, -1, sizeof(heado));
	n = readint(); m = readint();
	for(int i = 1; i < n; i++) {
		a = readint(); b = readint(); c = readint();
		addedgeo(a, b, c);
	}
	rebuild(1, 0);
	divide(1);
	while(m--) {
		a = readint();
		puts(has[a] ? "AYE" : "NAY");
	}
	return 0;
}
