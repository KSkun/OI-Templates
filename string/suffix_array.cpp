// Code by KSkun, 2018/7
#include <cstdio>
#include <cctype>
#include <cstring>

#include <algorithm>

const int MAXN = 1000005;

struct SuffixArray {
	char s[MAXN];
	int n, m, sa[MAXN], t[MAXN], t1[MAXN], c[MAXN], rnk[MAXN], hei[MAXN];
	inline void calsa() {
		int *x = t, *y = t1;
		for(int i = 1; i <= m; i++) c[i] = 0;
		for(int i = 1; i <= n; i++) c[x[i] = s[i]]++;
		for(int i = 1; i <= m; i++) c[i] += c[i - 1];
		for(int i = n; i >= 1; i--) sa[c[x[i]]--] = i;
		for(int k = 1; k <= n; k <<= 1) {
			int p = 0;
			for(int i = n - k + 1; i <= n; i++) y[++p] = i;
			for(int i = 1; i <= n; i++) if(sa[i] > k) y[++p] = sa[i] - k;
			for(int i = 1; i <= m; i++) c[i] = 0;
			for(int i = 1; i <= n; i++) c[x[y[i]]]++;
			for(int i = 1; i <= m; i++) c[i] += c[i - 1];
			for(int i = n; i >= 1; i--) sa[c[x[y[i]]]--] = y[i];
			std::swap(x, y);
			p = x[sa[1]] = 1;
			for(int i = 2; i <= n; i++) {
				x[sa[i]] = (y[sa[i]] == y[sa[i - 1]] && y[sa[i] + k] == y[sa[i - 1] + k]) ? p : ++p;
			}
			if(p >= n) break;
			m = p;
		}
		memcpy(rnk, x, sizeof(rnk));
		int k = 0;
		for(int i = 1; i <= n; i++) {
			int j = sa[rnk[i] + 1];
			if(k) k--;
			if(!j) continue;
			while(s[i + k] == s[j + k]) k++;
			hei[rnk[i]] = k;
		}
	}
} sa;

// an example of suffix array algorithm 
// can pass luogu p3809

int main() {
	scanf("%s", sa.s + 1);
	sa.n = strlen(sa.s + 1); sa.m = 256;
	sa.calsa();
	for(int i = 1; i <= sa.n; i++) { 
		printf("%d ", sa.sa[i]);
	}
	return 0;
}