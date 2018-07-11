// Code by KSkun, 2018/7
#include <cstdio>
#include <cctype>
#include <cstring>

#include <algorithm>

typedef long long LL;

const int MAXN = 300005;

int n;
char s[MAXN];
LL ans;

struct PalindromicTree {
	int ch[MAXN][26], fail[MAXN], len[MAXN], siz[MAXN], lst, tot;
	PalindromicTree() {
		tot = 1; fail[0] = fail[1] = 1; len[1] = -1;
	}
	inline void extend(int c, int n) {
		int p = lst;
		while(s[n - len[p] - 1] != s[n]) p = fail[p];
		if(!ch[p][c]) {
			int now = ++tot, k = fail[p];
			len[now] = len[p] + 2;
			while(s[n - len[k] - 1] != s[n]) k = fail[k];
			fail[now] = ch[k][c]; ch[p][c] = now;
		}
		lst = ch[p][c]; siz[lst]++;
	}
	inline void solve() {
		for(int i = tot; i; i--) {
			siz[fail[i]] += siz[i];
			ans = std::max(ans, 1ll * siz[i] * len[i]);
		}
	}
} pam;

// an example of palindromic tree
// can pass APIO2014 Palindrome

int main() {
	scanf("%s", s + 1);
	n = strlen(s + 1);
	for(int i = 1; i <= n; i++) {
		pam.extend(s[i] - 'a', i);
	}
	pam.solve();
	printf("%lld", ans);
	return 0;
}