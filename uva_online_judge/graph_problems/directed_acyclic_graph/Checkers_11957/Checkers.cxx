/*
  Problem: Checkers
  Link: http://uva.onlinejudge.org/external/119/11957.html
  Author: Deepak Antony - "deebee" "drunkbeast" "dAbeAst"
  Solution: Prepare a dag from the position of white till the top of the board.
  Then find the number paths to the top of the board by using DP.
*/

#include <cstdio>
#include <cstring>
#include <cassert>
#include <ctime>
#include <vector>
#include <algorithm>
#include <utility>
#include <limits>

using namespace std;

typedef unsigned long long UL;
typedef long long LL;
typedef pair<int,int> PII;

typedef vector<int> VI;
typedef vector<VI> VVI;
typedef vector<LL> VL;
typedef vector<VL> VVL;
typedef vector<PII> VPII;
typedef vector<VPII> VVPII;

#define REP(i, n) for(int i = 0; i < (n); ++i)
#define FOR(i, st, nd) for(int i = (st); i < (nd); ++i)
#define SET(a, val) memset(a, val, sizeof(a))
#define mp make_pair

#define INF numeric_limits<int>::max()
#define MOD 1000007

VVI G;
char board[110][110];
int N;
VL memo;

LL pathsToTop(int row, int col) {
	LL &res = memo[row*N+col];
	if(res == -1) {
		res = 0;
		if(row == 0) res = 1;
		else if(row > 0) {
			if(col > 0) {
				if(board[row-1][col-1] == '.') 
					res = (res+pathsToTop(row-1, col-1))%MOD;
				else if(board[row-1][col-1] == 'B' && col > 1 && row > 1 &&
						board[row-2][col-2] == '.')
					res = (res+pathsToTop(row-2, col-2))%MOD;
			}
			if(col < N-1) {
				if(board[row-1][col+1] == '.')
					res = (res+pathsToTop(row-1, col+1))%MOD;
				else if(board[row-1][col+1] == 'B' && col < N-2 && row > 1 &&
						board[row-2][col+2] == '.')
					res = (res+pathsToTop(row-2, col+2))%MOD;
			}
		}
	}
	return res;
}

void solveCheckers() {
	int T; scanf("%d", &T);
	int rowW, colW;

	REP(test, T) {
		scanf("%d", &N);

		REP(row, N) {
			scanf("%s", board[row]);
			// find 'W' if it exist
			REP(col, N) if(board[row][col] == 'W') rowW = row, colW = col;
		}

		// construct graph G 
		//G.assign(N*N, VI());
		//addEdgesToLocation(rowW, colW);

		memo.assign(N*N, -1);
		printf("Case %d: %d\n", test+1, pathsToTop(rowW,colW));
	}
}

int main(int argc, char *argv[]) {
#ifndef ONLINE_JUDGE
	clock_t start = clock();
#endif 
	// solve something here
	solveCheckers();

#ifndef ONLINE_JUDGE
	fprintf(stderr, "Time taken : %.5f seconds.\n",
			((float)clock()-start)/CLOCKS_PER_SEC);
#endif
	return 0;
}
