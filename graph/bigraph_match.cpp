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

const int MAXN = 2005;

int n, m, e;

std::vector<int> gra[MAXN];

int match[MAXN], vis[MAXN], clk;

bool dfs(int u) {
	for(int i = 0; i < gra[u].size(); i++) {
		int v = gra[u][i];
		if(vis[v] != clk) {
			vis[v] = clk;
			if(!match[v] || dfs(match[v])) {
				match[v] = u; match[u] = v; return true;
			}
		}
	}
	return false;
}

inline int bmatch() {
	int res = 0;
	for(int i = 1; i <= n + m; i++) {
		if(!match[i]) {
			clk++; if(dfs(i)) res++;
		}
	}
	return res;
}

// an example of hungarian algorithm of bigraph match

int main() {
	n = readint(); m = readint(); e = readint();
	for(int i = 1, u, v; i <= e; i++) {
		u = readint(); v = readint();
		gra[u].push_back(v);
		gra[v].push_back(u);
	}
	printf("%d", bmatch());
	return 0;
}