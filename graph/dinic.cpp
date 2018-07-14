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

const int MAXN = 100005, INF = 1e9;

struct Edge {
	int to, cap, nxt;
} gra[MAXN << 1];
int head[MAXN], tot;

inline void addedge(int u, int v, int cap) {
	gra[tot] = Edge {v, cap, head[u]}; head[u] = tot++;
	gra[tot] = Edge {u, 0, head[v]}; head[v] = tot++;
}

int level[MAXN];

inline bool bfs(int s, int t) {
	std::queue<int> que;
	memset(level, -1, sizeof(level));
	level[s] = 0; que.push(s);
	while(!que.empty()) {
		int u = que.front(); que.pop();
		for(int i = head[u]; ~i; i = gra[i].nxt) {
			int v = gra[i].to;
			if(level[v] == -1 && gra[i].cap) {
				level[v] = level[u] + 1;
				if(v == t) return true;
				que.push(v);
			}
		}
	}
	return level[t] != -1;
}

int cur[MAXN];

inline int dfs(int u, int t, int left) {
	if(u == t || !left) return left;
	int flow = 0;
	for(int &i = cur[u]; ~i; i = gra[i].nxt) {
		int v = gra[i].to;
		if(level[v] == level[u] + 1 && gra[i].cap) {
			int f = dfs(v, t, std::min(left, gra[i].cap));
			if(f) {
				flow += f; left -= f; gra[i].cap -= f; gra[i ^ 1].cap += f;
				if(!left) return flow;
			}
		}
	}
	return flow;
}

inline int dinic(int s, int t) {
	int flow = 0;
	while(bfs(s, t)) {
		memcpy(cur, head, sizeof(head));
		int f;
		while(f = dfs(s, t, INF)) flow += f;
	}
	return flow;
}

// an example of Dinic's alg
// can pass luogu p3376

int n, m, s, t, u, v, w;

int main() {
	memset(head, -1, sizeof(head));
	n = readint(); m = readint(); s = readint(); t = readint();
	while(m--) {
		u = readint(); v = readint(); w = readint();
		addedge(u, v, w);
	}
	printf("%d", dinic(s, t));
	return 0;
}
