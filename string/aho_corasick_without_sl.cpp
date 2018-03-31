// Code by KSkun, 2018/3
#include <cstdio>
#include <cstring>

#include <queue>
#include <algorithm>

const int MAXN = 20005;

// ch: trie, fail: fail pointer, last: suffix link, val: word id, cnt: node counter
int ch[MAXN][26], fail[MAXN], val[MAXN], cnt;

/*
 * Init the Aho-Corasick Automaton
 */
inline void initac() {
	memset(ch, 0, sizeof(ch));
	memset(fail, 0, sizeof(fail));
	memset(val, 0, sizeof(val));
	cnt = 0;
}

/*
 * Insert a single word into trie. Only lowercase letter.
 * @param id The id of the word. Used for counting.
 */
inline void insert(char *str, int id) {
	int p = 0;
	for(int i = 0; str[i]; i++) {
		int t = str[i] - 'a';
		if(!ch[p][t]) ch[p][t] = ++cnt;
		p = ch[p][t];
	}
	val[p] = id;
}

std::queue<int> que;

/*
 * Calculate the fail pointer of each node.
 */
inline void calfail() {
	for(int i = 0; i < 26; i++) {
		int u = ch[0][i];
		if(u) {
			fail[u] = 0;
			que.push(u);
		}
	}
	while(!que.empty()) {
		int u = que.front(); que.pop();
		for(int i = 0; i < 26; i++) {
			if(ch[u][i]) {
                fail[ch[u][i]] = ch[fail[u]][i];
                que.push(ch[u][i]);
            } else {
                ch[u][i] = ch[fail[u]][i];
            }
		}
	}
}

int pct[MAXN];

/*
 * Check if there are words in suffixes.
 */
inline int cal(int p) {
	int res = 0;
	for(; p; p = fail[p]) {
		// Count how many times each pattern is found.
		if(val[p]) pct[val[p]]++;
	}
	return res;
}

/*
 * Search patterns in text.
 */ 
inline void find(char *str) {
	int p = 0;
	for(int i = 0; str[i]; i++) {
		int t = str[i] - 'a';
		p = ch[p][t];
		cal(p);
	}
}

// an example of AC Automaton
// can pass luogu p3796

int n;
char pat[155][75], str[1000005];

int main() {
	// the number of patterns
	while(scanf("%d", &n) != EOF) {
		if(!n) break; // if n = 0, input ends
		initac();
		memset(pct, 0, sizeof(pct));
		// insert patterns
		for(int i = 1; i <= n; i++) {
			scanf("%s", pat[i]);
			insert(pat[i], i);
		}
		calfail();
		// find text
		scanf("%s", str);
		find(str);
		// get the maximum and output
		int mx = 0;
		for(int i = 1; i <= n; i++) {
			mx = std::max(mx, pct[i]);
		}
		printf("%d\n", mx);
		for(int i = 1; i <= n; i++) {
			if(pct[i] == mx) {
				printf("%s\n", pat[i]);
			}
		}
	}
	return 0;
}
