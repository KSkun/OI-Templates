// Code by KSkun, 2018/7
#include <cstdio>
#include <cctype>
#include <cstring>

#include <algorithm>

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

int T, n, m;

struct Edge {
	int to, w, nxt;
} gra[MAXN << 3];
int head[MAXN], tot;

inline void addedge(int u, int v, int w) {
	gra[tot] = Edge {v, w, head[u]}; head[u] = tot++;
}

int dis[MAXN], cnt[MAXN];
int que[MAXN], ql, qr;
bool inque[MAXN];

inline bool spfa() {
	ql = qr = 0;
	for(int i = 1; i <= n; i++) {
		que[qr++] = i; inque[i] = true; dis[i] = 0; cnt[i] = 0;
	}
	while(ql != qr) {
		int u = que[ql++]; inque[u] = false;
		if(ql == MAXN) ql = 0;
		for(int i = head[u]; ~i; i = gra[i].nxt) {
			int v = gra[i].to;
			if(dis[v] > dis[u] + gra[i].w) {
				cnt[v] = cnt[u] + 1;
				if(cnt[v] >= n) return true;
				dis[v] = dis[u] + gra[i].w;
				if(!inque[v]) {
					inque[v] = true;
					que[qr++] = v;
					if(qr == MAXN) qr = 0;
				}
			}
		}
	}
	return false;
}

// an example of finding negative circle with SPFA
// can pass luogu p3385

int main() {
	T = readint();
	while(T--) {
		memset(head, -1, sizeof(head)); tot = 0;
		n = readint(); m = readint();
		for(int i = 1, u, v, w; i <= m; i++) {
			u = readint(); v = readint(); w = readint();
			addedge(u, v, w);
			if(w >= 0) addedge(v, u, w);
		}
		puts(spfa() ? "YE5" : "N0");
	}
	return 0;
}