
/**
 * Assignment 15 : Coin Game
 */

#include <fstream>
#define MAX 101
using namespace std;

int bottle[MAX][MAX][MAX];


int dp(int A, int B, int C) {
	
	if (C == 1) {
		if (bottle[A][B][C - 1] == -1) return 1;
	}
	else if (C == 2) {
		if (bottle[A][B][C - 1] == -1) return 1;
		else if (bottle[A][B][C - 2] == -1) return 1;
	}
	else if (C >= 3) {
		if (bottle[A][B][C - 1] == -1) return 1;
		else if (bottle[A][B][C - 2] == -1) return 1;
		else if (bottle[A][B][C - 3] == -1) return 1;
	}
	if (B == 1) {
		if (bottle[A][B - 1][C] == -1) return 1;
	}
	else if (B == 2) {
		if (bottle[A][B - 1][C] == -1) return 1;
		else if (bottle[A][B - 2][C] == -1) return 1;
	}
	else if (B>=3){
		if (bottle[A][B - 1][C] == -1) return 1;
		else if (bottle[A][B - 2][C] == -1) return 1;
		else if (bottle[A][B - 3][C] == -1) return 1;
	}

	if (A == 1) {
		if (bottle[A - 1][B][C] == -1) return 1;
	}
	else if (A == 2) {
		if (bottle[A - 1][B][C] == -1) return 1;
		else if (bottle[A - 2][B][C] == -1) return 1;
	}
	else if (A >= 3) {
		if (bottle[A - 1][B][C] == -1) return 1;
		else if (bottle[A - 2][B][C] == -1) return 1;
		else if (bottle[A - 3][B][C] == -1) return 1;
	}
	

	if (!bottle[A][B][C]) return -1;

}


void setBottle() {
	bottle[0][0][1] = -1;
	bottle[0][1][0] = -1;
	bottle[1][0][0] = -1;
	bottle[1][1][1] = -1;

	for (int A = 0; A < 100; A++) {
		for (int B = 0; B < 100; B++) {
			for (int C = 0; C < 100; C++) {
				if (!A && !B && !C) continue;
				else if (bottle[A][B][C] != 0) continue;
				else bottle[A][B][C] = dp(A, B, C);
			}
		}
	}
}


int main() {
	ifstream input("coin.inp");
	ofstream output("coin.out");
	setBottle();
	int t,a, b, c;
	input >> t;
	while (t--) {
		input >> a >> b >> c;
		output << "(" << a << " " << b << " " << c << ")" << " : " << bottle[a][b][c] << "\n";
	}
	input.close();
	output.close();

	return 0;
}