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

const int MAXN = 10005, INF = 1e9;

struct Edge {
	int to, w;
};

int n, m, has[10000005], siz[MAXN], msz[MAXN], rt;
bool vis[MAXN];
std::vector<Edge> gra[MAXN];

/*
 * Find the center of gravity of a tree.
 */  
inline void findrt(int u, int f, int tot) {
	siz[u] = 1;
	for(Edge e : gra[u]) {
		int v = e.to;
		if(v == f || vis[v]) continue;
		findrt(v, u, tot);
		siz[u] += siz[v];
		msz[u] = std::max(msz[u], siz[v]);
	}
	msz[u] = std::max(msz[u], tot - siz[u]);
	if(msz[u] < msz[rt]) rt = u;
}

struct Data {
	int dis, subt;
};

std::vector<Data> diss;

inline void caldis(int u, int f, int d, int subt) {
	if(subt) diss.push_back(Data {d, subt});
	for(Edge e : gra[u]) {
		int v = e.to, w = e.w;
		if(v == f || vis[v]) continue;
		caldis(v, u, d + w, !f ? v : subt);
	}
}

inline void work(int u) {
	diss.clear();
	caldis(u, 0, 0, 0);
	for(int i = 0; i < diss.size(); i++) {
		has[diss[i].dis] = true;
		for(int j = i + 1; j < diss.size(); j++) {
			if(diss[i].subt != diss[j].subt) {
				has[diss[i].dis + diss[j].dis] = true;
			}
		}
	}
}

/*
 * Divide the problem into smaller trees.
 */
inline void divide(int u) {
	work(u);
	vis[u] = true;
	for(Edge e : gra[u]) {
		int v = e.to;
		if(vis[v]) continue;
		rt = 0;
		findrt(v, 0, siz[v]);
		divide(rt);
	}
}

// an example of tree DAC alg based on nodes.
// can pass luogu p3806

int a, b, c;

int main() {
	n = readint(); m = readint();
	for(int i = 1; i < n; i++) {
		a = readint(); b = readint(); c = readint();
		gra[a].push_back(Edge {b, c});
		gra[b].push_back(Edge {a, c});
	}
	rt = 0;
	msz[0] = INF;
	findrt(1, 0, n);
	divide(rt);
	while(m--) {
		a = readint();
		puts(has[a] ? "AYE" : "NAY");
	}
	return 0;
}
