// Code by KSkun, 2018/7
#include <cstdio>
#include <cctype>
#include <cstring>

#include <algorithm>

typedef long long LL;

const int MAXN = 1000005;

struct SuffixAutomaton {
	int lst, tot, ch[MAXN << 1][26], nxt[MAXN << 1], len[MAXN << 1], siz[MAXN << 1];
	SuffixAutomaton() {
		lst = tot = 1;
	}
	inline void extend(int c) {
		int u = ++tot, v = lst;
		len[u] = len[v] + 1;
		for(; v && !ch[v][c]; v = nxt[v]) ch[v][c] = u;
		if(!v) {
			nxt[u] = 1;
		} else if(len[ch[v][c]] == len[v] + 1) {
			nxt[u] = ch[v][c];
		} else {
			int n = ++tot, o = ch[v][c];
			len[n] = len[v] + 1;
			memcpy(ch[n], ch[o], sizeof(ch[o]));
			nxt[n] = nxt[o]; nxt[o] = nxt[u] = n;
			for(; v && ch[v][c] == o; v = nxt[v]) ch[v][c] = n;
		}
		lst = u; siz[u] = 1;
	}
} sam;

char s[MAXN];
int a[MAXN << 1], c[MAXN << 1];

// an example of suffix automaton
// can pass luogu p3804

int main() {
	scanf("%s", s + 1);
	for(int i = 1; s[i]; i++) {
		sam.extend(s[i] - 'a');
	}
	LL ans = 0;
	for(int i = 1; i <= sam.tot; i++) c[sam.len[i]]++;
	for(int i = 1; i <= sam.tot; i++) c[i] += c[i - 1];
	for(int i = 1; i <= sam.tot; i++) a[c[sam.len[i]]--] = i;
	for(int i = sam.tot; i; i--) {
		int p = a[i];
		sam.siz[sam.nxt[p]] += sam.siz[p];
		if(sam.siz[p] > 1) ans = std::max(ans, 1ll * sam.siz[p] * sam.len[p]);
	}
	printf("%lld", ans);
	return 0;
}