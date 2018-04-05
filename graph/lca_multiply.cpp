// Code by KSkun, 2018/4
#include <cstdio>
#include <cstring>
#include <cmath>

#include <algorithm>

typedef long long LL;

inline char fgc() {
	static char buf[100000], *p1 = buf, *p2 = buf;
	return p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, 100000, stdin), p1 == p2) ? EOF : *p1++;
}

inline int readint() {
	register int res = 0, neg = 1;
	register char c = fgc();
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

const int MAXN = 500005, INF = 1e9;

int n, m;

struct Edge {
	int to, nxt;
} gra[MAXN << 1];
int head[MAXN], tot;

inline void addedge(int u, int v) {
	gra[tot] = Edge {v, head[u]}; head[u] = tot++;
	gra[tot] = Edge {u, head[v]}; head[v] = tot++;
}

int anc[MAXN][20], dep[MAXN], lgn;

// Get the info of every node
inline void dfs(int u) {
	for(int i = head[u]; ~i; i = gra[i].nxt) {
		int v = gra[i].to;
		if(v == anc[u][0]) continue;
		anc[v][0] = u;
		dep[v] = dep[u] + 1;
		dfs(v);
	}
}

// Calculate the ancestors of every node
inline void calanc() {
	for(int j = 1; (1 << j) <= n; j++) {
		for(int i = 1; i <= n; i++) {
			anc[i][j] = anc[anc[i][j - 1]][j - 1];
		}
	}
}

// Query the LCA of two nodes
inline int querylca(int u, int v) {
	if(dep[u] > dep[v]) std::swap(u, v);
	int del = dep[v] - dep[u];
	for(int i = 0; (1 << i) <= del; i++) {
		if((1 << i) & del) v = anc[v][i];
	}
	if(u == v) return u;
	for(int i = lgn; i >= 0; i--) {
		if(anc[u][i] != anc[v][i]) {
			u = anc[u][i];
			v = anc[v][i];
		}
	}
	return anc[u][0];
}

// an example of doubling LCA alg
// can pass luogu p3379

int s, x, y;

int main() {
	memset(head, -1, sizeof(head));
	n = readint(); m = readint(); s = readint();
	lgn = log(n) / log(2);
	for(int i = 1; i < n; i++) {
		x = readint(); y = readint();
		addedge(x, y);
	}
	dfs(s);
	calanc();
	while(m--) {
		x = readint(); y = readint();
		printf("%d\n", querylca(x, y));
	}
	return 0;
}
