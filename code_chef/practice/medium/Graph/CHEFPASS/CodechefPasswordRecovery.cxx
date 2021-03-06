// http://www.codechef.com/problems/CHEFPASS/

#include <cstdio>
#include <cstring>

#define REP(i, n) for(int i = 0; i < (n); ++i)
#define SET(arr, val) memset(arr, val, sizeof(arr))

// Find Union set
int parent[52];
int init() { REP(i, 52) parent[i] = i; }
int find(int x) { return parent[x] = (parent[x] == x) ? x : find(parent[x]); }
void join(int x, int y) { parent[find(x)] = find(y); }

// encoding 'A' -> 'Z' and 'a' -> 'z' to be within 0->52
int E(char c) { return c >= 'a' ? 26 + c - 'a' : c-'A'; }

// Solution: find set of eulerian circuits that include all chars in A and some
// in B.
int main(int argc, char *argv[])
{
	int T; scanf("%d", &T);
	int N, M;
	char inp[3];
	int deg[52], oddVertices[52];
	while(T--) {
		// count the degrees of every vertex in A. We want to ensure if any
		// vertex's degree is odd it provides a complete circuit through B.
		scanf("%d", &N);
		SET(deg, 0);
		while(N--) scanf("%s", inp), deg[E(inp[0])]++, deg[E(inp[1])]++;

		// Prepare a find union set based on B. This essentially merges 
		// connected vertices. 
		scanf("%d", &M); init();
		while(M--) scanf("%s", inp), join(E(inp[0]), E(inp[1]));

		SET(oddVertices, 0);
		REP(i, 52) if(deg[i]%2) oddVertices[find(i)]++;
		int odd = 0;
		REP(i, 52) if(oddVertices[i]%2) { odd = 1; break; }
		printf("%s\n", odd?"NO":"YES");
	}

	return 0;
}



