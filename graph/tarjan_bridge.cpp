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

const int MAXN = 10005;

int n, m;
std::vector<int> gra[MAXN];

int dfn[MAXN], low[MAXN], clk, deg[MAXN];

void tarjan(int u, int fa) {
	dfn[u] = low[u] = ++clk;
	for(int i = 0; i < gra[u].size(); i++) {
		int v = gra[u][i];
		if(v == fa) continue;
		if(!dfn[v]) {
			tarjan(v, u);
			low[u] = std::min(low[u], low[v]);
		} else {
			low[u] = std::min(low[u], dfn[v]);
		}
	}
}

// an example of Tarjan algorithm of finding bridge edges
// can pass poj 3352

int main() {
	n = readint(); m = readint();
	for(int i = 1, u, v; i <= m; i++) {
		u = readint(); v = readint();
		gra[u].push_back(v);
		gra[v].push_back(u);
	}
	tarjan(1, 0);
	for(int u = 1; u <= n; u++) {
		for(int i = 0; i < gra[u].size(); i++) {
			int v = gra[u][i];
			if(low[u] != low[v]) {
				deg[low[u]]++;
			}
		}
	}
	int cnt = 0;
	for(int i = 1; i <= n; i++) {
		if(deg[i] == 1) cnt++;
	}
	printf("%d", (cnt + 1) / 2);
	return 0;
}