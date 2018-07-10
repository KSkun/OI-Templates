// Code by KSkun, 2018/7
#include <cstdio>
#include <cctype>
#include <cstring>

#include <algorithm>
#include <vector>

typedef long long LL;

inline char fgc() {
	static char buf[100000], *p1 = buf, *p2 = buf;
	return p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, 100000, stdin), p1 == p2)
		? EOF : *p1++;
}

inline LL readint() {
	register LL res = 0, neg = 1; register char c = fgc();
	for(; !isdigit(c); c = fgc()) if(c == '-') neg = -1;
	for(; isdigit(c); c = fgc()) res = (res << 1) + (res << 3) + c - '0';
	return res * neg;
}

const int MAXN = 100005;

int n, m;
std::vector<int> gra[MAXN];

int dfn[MAXN], low[MAXN], clk;
bool cut[MAXN];

inline void tarjan(int u, int rt) {
	dfn[u] = low[u] = ++clk;
	int subt = 0;
	for(auto v : gra[u]) {
		if(!dfn[v]) {
			tarjan(v, rt);
			low[u] = std::min(low[u], low[v]);
			if(low[v] >= dfn[u] && u != rt) cut[u] = true;
			subt++;
		} else {
			low[u] = std::min(low[u], dfn[v]);
		}
	}
	if(u == rt && subt >= 2) cut[u] = true;
}

// an example of Tarjan algorithm of finding cut vertices
// can pass luogu p3388

int main() {
	n = readint(); m = readint();
	for(int i = 1, u, v; i <= m; i++) {
		u = readint(); v = readint();
		gra[u].push_back(v); gra[v].push_back(u);
	}
	for(int i = 1; i <= n; i++) {
		if(!dfn[i]) tarjan(i, i);
	}
	int cnt = 0;
	for(int i = 1; i <= n; i++) {
		if(cut[i]) cnt++;
	}
	printf("%d\n", cnt);
	for(int i = 1; i <= n; i++) {
		if(cut[i]) printf("%d ", i);
	}
	return 0;
}