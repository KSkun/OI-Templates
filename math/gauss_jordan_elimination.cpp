// Code by KSkun, 2018/3
#include <cstdio>
#include <cmath>

#include <algorithm>

const int MAXN = 105;
const double EPS = 1e-10;

int n;
double mat[MAXN][MAXN];

/*
 * Gauss-Jordan Elimination.
 */ 
inline bool gauss() {
	for(int i = 1; i <= n; i++) {
		int r = i;
		for(int j = i + 1; j <= n; j++) {
			if(std::fabs(mat[r][i]) < std::fabs(mat[j][i])) r = j;
		}
		if(r != i) {
			for(int j = 1; j <= n + 1; j++) std::swap(mat[i][j], mat[r][j]);
		}
		if(fabs(mat[i][i]) < EPS) return false;
		for(int j = 1; j <= n; j++) {
			if(j != i) {
				double t = mat[j][i] / mat[i][i];
				for(int k = i + 1; k <= n + 1; k++) mat[j][k] -= mat[i][k] * t;
			}
		}
	}
	for(int i = 1; i <= n; i++) mat[i][n + 1] /= mat[i][i];
	return true;
}

// an example of G-J Elimination
// can pass luogu p3389

int main() {
	scanf("%d", &n);
	for(int i = 1; i <= n; i++) {
		for(int j = 1; j <= n + 1; j++) {
			scanf("%lf", &mat[i][j]);
		}
	}
	if(gauss()) {
		for(int i = 1; i <= n; i++) {
			printf("%.2lf\n", mat[i][n + 1]);
		}
	} else {
		puts("No Solution");
	}
	return 0;
}
