// Code by KSkun, 2018/4
#include <cstdio>
#include <cstring>

#include <vector>
#include <queue>

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

const int MAXN = 50005, INF = 1e9;

struct Edge {
	int to, cap, cost, nxt;
} gra[MAXN << 1];
int head[MAXN], tot;

inline void addedge(int u, int v, int cap, int cost) {
	gra[tot] = Edge {v, cap, cost, head[u]}; head[u] = tot++;
	gra[tot] = Edge {u, 0, -cost, head[v]}; head[v] = tot++;
}

std::queue<int> que;

int flow, cost, f[MAXN], dis[MAXN], pre[MAXN], pree[MAXN];
bool inque[MAXN];

// Calculate the MCMF of the network 
inline void mcmf(int s, int t) {
	for(;;) {
		memset(f, 0, sizeof(f));
		memset(dis, 0x3f, sizeof(dis));
		dis[s] = 0; inque[s] = true; f[s] = INF; que.push(s);
		while(!que.empty()) {
			int u = que.front(); que.pop(); inque[u] = false;
			for(int i = head[u]; ~i; i = gra[i].nxt) {
				int v = gra[i].to;
				if(gra[i].cap > 0 && dis[v] > dis[u] + gra[i].cost) {
					pre[v] = u; pree[v] = i;
					f[v] = std::min(f[u], gra[i].cap);
					dis[v] = dis[u] + gra[i].cost;
					if(!inque[v]) {
						que.push(v); inque[v] = true;
					}
				}
			}
		}
		if(!f[t]) break;
		for(int i = t; i != s; i = pre[i]) {
			gra[pree[i]].cap -= f[t]; gra[pree[i] ^ 1].cap += f[t];
		}
		flow += f[t]; cost += f[t] * dis[t];
	}
}

// an example of MCMF SPFA Edmonds-Karp alg
// can pass luogu p3381

int n, m, s, t, u, v, w, c;

int main() {
	memset(head, -1, sizeof(head));
	n = readint(); m = readint(); s = readint(); t = readint();
	while(m--) {
		u = readint(); v = readint(); w = readint(); c = readint();
		addedge(u, v, w, c);
	}
	mcmf(s, t);
	printf("%d %d", flow, cost);
	return 0;
}
