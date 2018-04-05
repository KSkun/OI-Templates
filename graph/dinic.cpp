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

std::queue<int> que;
int level[MAXN];
bool vis[MAXN];

// BFS proccess layered graph 
inline bool bfs(int s, int t) {
	memset(level, -1, sizeof(level));
	level[s] = 0;
	que.push(s);
	while(!que.empty()) {
		int u = que.front(); que.pop();
		for(int i = head[u]; ~i; i = gra[i].nxt) {
			int v = gra[i].to;
			if(level[v] == -1 && gra[i].cap > 0) {
				level[v] = level[u] + 1;
				que.push(v);
			}
		}
	}
	return level[t] != -1;
}

// DFS find augumenting paths
inline int dfs(int u, int t, int left) {
	if(u == t || left == 0) return left;
	int flow = 0;
	vis[u] = true;
	for(int i = head[u]; ~i; i = gra[i].nxt) {
		int v = gra[i].to;
		if(!vis[v] && gra[i].cap > 0 && level[v] == level[u] + 1) {
			int d = dfs(v, t, std::min(left, gra[i].cap));
			if(d > 0) {
				gra[i].cap -= d; gra[i ^ 1].cap += d;
				left -= d; flow += d;
				if(left == 0) {
					level[u] = -1;
					return flow;
				}
			}
		}
	}
	return flow;
}

// Keep augumenting until not path exists
inline int dinic(int s, int t) {
	int flow = 0;
	while(bfs(s, t)) {
		memset(vis, 0, sizeof(vis));
		int f;
		while(f = dfs(s, t, INF)) {
			flow += f;
		}
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
