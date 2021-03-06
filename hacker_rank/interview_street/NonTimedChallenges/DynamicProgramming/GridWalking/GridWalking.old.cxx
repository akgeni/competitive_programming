// Grid Walking - problem description from interview street
// You are situated in an N dimensional grid at position(x_1,x2,...,x_N). The 
// dimensions of the grid are (D_1,D_2,...D_N). In one step, you can walk one 
// step ahead or behind in any one of the N dimensions. (So there are always 2N 
// possible different moves). In how many ways can you take M steps such that 
// you do not leave the grid at any point ? You leave the grid if you for any 
// x_i, either x_i <= 0 or x_i > D_i.
// 
// Input:
// The first line contains the number of test cases T. T test cases follow. For 
// each test case, the first line contains N and M, the second line contains 
// x_1,x_2...,x_N and the 3rd line contains D_1,D_2,...,D_N.
// 
// Output:
// Output T lines, one corresponding to each test case. Since the answer can be 
// really huge, output it modulo 1000000007.
// 
// Constraints: 1 <= T <= 10
// 1 <= N <= 10
// 1 <= M <= 300
// 1 <= D_i <= 100
// 1 <= x_i <= D_i
// 
// Sample Input #00:
// 10
// 1 287
// 44
// 78
// 1 236
// 25
// 87
// 1 122
// 41
// 63
// 1 260
// 7
// 64
// 1 127
// 3
// 73
// 1 69
// 6
// 68
// 1 231
// 14
// 63
// 1 236
// 13
// 30
// 1 259
// 38
// 70
// 1 257
// 11
// 12
// Sample output: 
// 38753340
// 587915072
// 644474045
// 423479916
// 320130104
// 792930663
// 846814121
// 385120933
// 60306396
// 306773532



// First simple solution that I can think of is to sum up all the paths 
// starting from the given point. Here's the reccursive formulation of this
// algorithm. If pos[cur] is the current position then let pos[next] be all 
// valid positions reachable from pos[cur]. So, for 2d, if pos[cur] = [Xi, Yj] 
// pos[next] is the set { (Xi-1, Yj), (Xi, Y-1), (Xi+1, Yj), (Xi, Yj+1) }
// GW(pos[cur], M) = { |{pos[next]}| if M = 1; }
// GW(pos[cur], M) = { sum(GW(post[next]), M-1) if M > 1; }
//
// We can see that we can apply dynamic programming. I need to figure out how 
// to do this without running out of memory. This problem allows 100x100...x100
// 10 dimensions; it'll be tricky.
//
// I think I've figured something out. If you look at the problem without any
// boundaries i.e. without anyone falling off, the problem is a polynomial
// function with N variables and degree M. So, to find the sum of all paths 
// that you can take in N-dims, we add up all polynomial coefficients for the 
// equation(x0 + x1 + ... + x2N)^M 
//
// Look up pascal's triangle/pyramid/.../M-simplex
//
// So the sum would be (2N)^M. Now we do have the constraint that you may fall 
// off if you're not within the dimensions of the grid. So we need to subtract
// right amount of values from the total.
// So, if the initial position is at the corner of a dimension, then one of 
// your simplex becomes 0 from the beginning. So subtract 2N^(M-1). The power is
// (m-1) because the size of this simplex is 1 less than the main simplex. 
// Eg: For a 2-simplex (pascal's triangle)
//        1
//      1   0 <- This is the dimension in which there is no movement
//    1   1   0 <- 2^2 - 2^(2-1) at M = 2
//  1   2   1   0 <- 2^3 - 2^(3-1) at M = 3 and so on
//
// Similarly, for every dimension that becomes the edge after 'k' positions, we 
// should subtract (2N)^(M-k-1) from (2N)^M
// This doesn't work out that easilyt either. I've thought of a new simpler
// solution which will be in a new file.
//


#include <iostream>

using namespace std;

#define MODULO_NUM 1000000007l

typedef long long  int vlong;

vlong modPow(vlong base, vlong power, vlong modulus = MODULO_NUM)
{
	vlong res = 1;
	for(vlong i = 0; i < power; i++)
		res = (res*base)%modulus;
	return res;
}

class NDimentionGrid
{
public:
	NDimentionGrid(int *dims, int size) 
		:N(size) {
		dimensions = new int[size];
		for(int index = 0; index < size; index++)
		{
			dimensions[index] = dims[index];
		}
	}

	vlong gridWalk(int *position, int M) {
		vlong subVal = 0;
		for(int i = 0; i < N; i++)
		{
			int diff1 = position[i] - 1; // from the 0th index
			int diff2 = dimensions[i] - position[i];
			cout << diff1 << " " << diff2 << " " << position[i] << " " << dimensions[i] << endl;
			if(M > diff1)
				subVal = (subVal + modPow(2*N, M-diff1-1))%MODULO_NUM;
			if(M > diff2)
				subVal = (subVal + modPow(2*N, M-diff2-1))%MODULO_NUM;
		}
		cout << modPow(2*N, M) << endl;
		cout << subVal << endl;
		cout << (-subVal)%MODULO_NUM << endl;
		cout <<  modPow(2*N, M) - subVal + MODULO_NUM << endl;
		return (modPow(2*N, M) + ((-subVal)%MODULO_NUM))%MODULO_NUM;
	}

/* Commented out since this is too slow
	bool isValidPosition(int *position) {
		for(int index = 0; index < N; index++)
			if(position[index] < 0 || position[index] > dimensions[index])
				return false;
		return true;
	}

	// position - current position
	// M - is the number of steps 
	// N - number of dimensions
	vlong gridWalkSlowMethod(int *position, int M) {
//		cout << M << endl;
		int idx = 0;
		vlong sizeOfPrev = 1;
		for(int index = N-1; index >= 0; index--)
		{
			idx = (position[index]-1) * sizeOfPrev;
			sizeOfPrev *= dimensions[index];
		}

		int totalPaths = 0;
		if(M == 1) // leaf
		{
			for(int index = 0; index < N; index++)
			{
				if(position[index]+1 <= dimensions[index]) 
					++totalPaths;
				if(position[index]-1 > 0)
					++totalPaths;
			}
		}
		else
		{
			for(int index = 0; index < N; index++)
			{
				if(position[index]+1 <= dimensions[index])
				{
					position[index] += 1;
					totalPaths += gridWalk(position, M-1);
					position[index] -= 1;
				}
				if(position[index]-1 > 0)
				{
					position[index] -= 1;
					totalPaths += gridWalk(position, M-1);
					position[index] += 1;
				}
			}
		}
		vals[idx] = (vals[idx] + totalPaths%MODULO_NUM)%MODULO_NUM;
		return vals[idx];
	}
	// supplmentts the above slow method
	int sum() {
		int s = 0;
		for(int i = 0; i < totalSize; i++)
			s = (s+vals[i])%MODULO_NUM;
		return s;
	}
*/


	void print() {
		cout << "Number of dimensions: " << N << endl;
		cout << "Dimensions: ";
		for(int d = 0; d < N; d++)
			cout << dimensions[d] << " ";
		cout << endl;
	}

	~NDimentionGrid() {
		delete dimensions;
	}

private:
	int *dimensions;
	int N;
//	int *vals;
//	vlong totalSize;
};

int main(int argc, char* argv[])
{
	int nTests;
	cin >> nTests;
	cout << "Number of tests: " << nTests << endl;
	for(int n = 0; n < nTests; n++)
	{
		int N, M;
		cin >> N ;
		cin >> M;

		cout << "N and M :" << N << " " << M << endl;

		int *dimensions, *position;
		position = new int[N];
		for(int i = 0; i < N; i++)
			cin >> position[i];
		cout << "positions: ";
		for(int i = 0; i < N; i++)
			cout << position[i] << " ";
		cout << endl;

		dimensions = new int[N];
		for(int d = 0; d < N; d++)
			cin >> dimensions[d];
		cout << "dimensions: ";
		for(int d = 0; d < N; d++)
			cout << dimensions[d] << " ";
		cout << endl;
		

		NDimentionGrid grid(dimensions, N);
		grid.print();
		cout << grid.gridWalk(position, M) << endl;

		delete dimensions;
		delete position;
	}
	return 0;
}

