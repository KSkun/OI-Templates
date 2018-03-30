// Code by KSkun, 2018/3
#include <cstdio>
#include <cstring>

const int MAXN = 1000005;

int fail[MAXN];
char p[MAXN], t[MAXN];

inline void calfail() {
	int i = 0, j = -1;
	fail[0] = -1;
	for(; p[i]; i++, j++) {
		while(j >= 0 && p[j] != p[i]) j = fail[j];
		fail[i + 1] = p[j + 1] == p[i + 1] ? fail[j + 1] : j + 1; // optimize here
	}
}

inline int find(char *t) {
	int i = 0, j = 0, len = strlen(p);
	for(; t[i]; i++, j++) {
		while(j >= 0 && p[j] != t[i]) j = fail[j];
		if(j >= len - 1) return i - len + 2;
	}
	return -1;
}

inline void findall(char *t) {
	int i = 0, j = 0, len = strlen(p);
	for(; t[i]; i++, j++) {
		while(j >= 0 && p[j] != t[i]) j = fail[j];
		if(j >= len - 1) printf("%d\n", i - len + 2);
	}
}

// an example of using KMP alg to proccess string
// cannot pass luogu p3375 because of fail value

int main() {
#ifndef ONLINE_JUDGE
	scanf("%s", p);
	calfail();
	while(scanf("%s", t)) {
		printf("find at %d\n", find(t));
	}
#else
	scanf("%s%s", t, p);
	calfail();
	findall(t);
	int len = strlen(p);
	for(int i = 0; i < len; i++) {
		printf("%d ", fail[i]);
	}
#endif
	return 0;
}
