// Code by KSkun, 2018/3
#include <cstdio>
#include <cstring>

const int MAXN = 1000005;

int fail[MAXN];
char p[MAXN], t[MAXN];

/*
 * Calculate fail values
 */
inline void calfail() {
	fail[1] = 0;
	int i = 2, j = 0;
	for(; p[i]; i++) {
		while(j && p[j + 1] != p[i]) j = fail[j];
		if(p[j + 1] == p[i]) j++;
		fail[i] = j;
	}
}

/*
 * Find the first position where p appears in t. If not found, returns -1
 * @return the first position where p appears in t
 */
inline int find(char *t) {
	int i = 1, j = 0, len = strlen(p + 1);
	for(; t[i]; i++) {
		while(j && p[j + 1] != t[i]) j = fail[j];
		if(p[j + 1] == t[i]) j++;
		if(j >= len) return i - len + 1;
	}
	return -1;
}

/*
 * Output all positions where p appears in t.
 */
inline void findall(char *t) {
	int i = 1, j = 0, len = strlen(p + 1);
	for(; t[i]; i++) {
		while(j && p[j + 1] != t[i]) j = fail[j];
		if(p[j + 1] == t[i]) j++;
		if(j >= len) printf("%d\n", i - len + 1);
	}
}

// an example of using KMP alg to proccess string
// can pass luogu p3375

int main() {
#ifndef ONLINE_JUDGE
	// input p at the first line
	scanf("%s", p + 1);
	calfail();
	// and input t at the lines below
	// output the first position of p
	while(scanf("%s", t + 1)) {
		printf("find at %d\n", find(t));
	}
#else // luogu p3375
	scanf("%s%s", t + 1, p + 1);
	calfail();
	findall(t);
	int len = strlen(p + 1);
	for(int i = 1; i <= len; i++) {
		printf("%d ", fail[i]);
	}
#endif
	return 0;
}
