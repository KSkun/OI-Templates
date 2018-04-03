// Code by KSkun, 2018/4
#include <cstdio>
#include <cstring>

#include <algorithm>

typedef long long LL;

inline char fgc() {
	static char buf[100000], *p1 = buf, *p2 = buf;
	return p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, 100000, stdin), p1 == p2) ? EOF : *p1++;
}

inline LL readint() {
	register LL res = 0, neg = 1;
	char c = fgc();
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

const int MAXN = 100005;

// Splay tree

struct Node {
	int fa, ch[2], val, siz, cnt;
} tr[MAXN];

int tot = 0, sta[MAXN], stop = 0, rt = 0;

// Update the info of p
inline void update(int p) {
	int lch = tr[p].ch[0], rch = tr[p].ch[1];
	tr[p].siz = tr[lch].siz + tr[rch].siz + tr[p].cnt;
}

// Return a new node's number
inline int newnode() {
	int p;
	if(stop) p = sta[--stop];
	else p = ++tot;
	memset(tr + p, 0, sizeof(Node));
	return p;
}

// Recycle the memory of p
inline void delnode(int p) {
	sta[stop++] = p;
}

// If p is its father's left child
inline bool isleft(int p) {
	return tr[tr[p].fa].ch[0] == p;
}

// Apply a rotation to p
inline void rotate(int p) {
	bool t = !isleft(p); int fa = tr[p].fa, ffa = tr[fa].fa;
	tr[p].fa = ffa; if(ffa) tr[ffa].ch[!isleft(fa)] = p;
	tr[fa].ch[t] = tr[p].ch[!t]; tr[tr[fa].ch[t]].fa = fa;
	tr[p].ch[!t] = fa; tr[fa].fa = p;
	update(fa);
	if(!tr[p].fa) rt = p;
}

// Splay p until its father is tar
inline void splay(int p, int tar) {
	for(int fa = tr[p].fa; fa != tar; rotate(p), fa = tr[p].fa) {
		if(tr[fa].fa != tar) rotate(isleft(fa) == isleft(p) ? fa : p);
	}
	update(p);
}

// Insert a single node whose value is v
inline void insert(int v) {
	if(!rt) {
		rt = newnode();
		tr[rt].val = v;
		tr[rt].siz = tr[rt].cnt = 1;
		return;
	}
	int p = rt, fa = 0;
	for(;;) {
		if(v == tr[p].val) {
			tr[p].cnt++;
			update(p); update(fa);
			splay(p, 0);
			return;
		}
		fa = p;
		p = tr[p].ch[tr[p].val < v];
		if(!p) {
			p = newnode();
			tr[p].val = v; 
			tr[p].siz = tr[p].cnt = 1;
			tr[p].fa = fa;
			tr[fa].ch[tr[fa].val < v] = p;
			update(fa);
			splay(p, 0);
			return;
		}
	}
}

// Query the rank of v in the tree
inline int queryrk(int v) {
	int p = rt, res = 0;
	for(;;) {
		if(v < tr[p].val) {
			p = tr[p].ch[0];
		} else {
			res += tr[tr[p].ch[0]].siz;
			if(v == tr[p].val) {
				splay(p, 0);
				return res + 1;
			}
			res += tr[p].cnt;
			p = tr[p].ch[1];
		}
	}
}

// Query the k-th number in the tree
inline int queryn(int rk) {
	int p = rt;
	for(;;) {
		if(tr[p].ch[0] && rk <= tr[tr[p].ch[0]].siz) {
			p = tr[p].ch[0];
		} else {
			rk -= tr[tr[p].ch[0]].siz;
			if(rk <= tr[p].cnt) {
				return tr[p].val;
			}
			rk -= tr[p].cnt;
			p = tr[p].ch[1];
		}
	}
}

// Query the last number which is smaller than root
inline int querypre() {
	int p = tr[rt].ch[0];
	while(tr[p].ch[1]) p = tr[p].ch[1];
	return p;
}

// Query the first number which is larger than root
inline int querynxt() {
	int p = tr[rt].ch[1];
	while(tr[p].ch[0]) p = tr[p].ch[0];
	return p;
}

// Erase a single value v from the tree
inline void erase(int v) {
	queryrk(v);
	if(tr[rt].cnt > 1) {
		tr[rt].cnt--;
		update(rt);
		return;
	}
	if(!tr[rt].ch[0]) {
		delnode(rt);
		rt = tr[rt].ch[1];
		tr[rt].fa = 0;
		return;
	}
	if(!tr[rt].ch[1]) {
		delnode(rt);
		rt = tr[rt].ch[0];
		tr[rt].fa = 0;
		return;
	}
	int ort = rt, lmx = querypre();
	splay(lmx, 0);
	tr[rt].ch[1] = tr[ort].ch[1];
	tr[tr[rt].ch[1]].fa = rt;
	delnode(ort);
	update(rt);
}

// an example of splay tree used on counting functions
// can pass luogu p3369

int n, op, x;

int main() {
	n = readint();
	while(n--) {
		op = readint(); x = readint();
		switch(op) {
		case 1:
			insert(x); break;
		case 2:
			erase(x); break;
		case 3:
			printf("%d\n", queryrk(x)); break;
		case 4:
			printf("%d\n", queryn(x)); break;
		case 5:
			insert(x); printf("%d\n", tr[querypre()].val); erase(x); break;
		case 6:
			insert(x); printf("%d\n", tr[querynxt()].val); erase(x);
		}
	}
	return 0;
}
