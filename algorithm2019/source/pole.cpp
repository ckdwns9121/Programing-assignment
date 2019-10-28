/**
 * Assignment 11 : Pole Arrangement
 */
#include <fstream>
#include <algorithm>
#include <vector>

using namespace std;
int n, l, r;
unsigned long long dp[21][21][21];

void solution() {
	for (int i = 1; i <21; i++) {
		dp[i][i][1] = dp[i][1][i] = 1;
	}
	for (int i = 2; i <21; i++) {
		for (int j = 1; j <=i; j++) {
			for (int k = 1; k <=i; k++) {
				dp[i][j][k] = dp[i - 1][j][k] * (i - 2) +
						      dp[i - 1][j][k - 1] +
							  dp[i - 1][j - 1][k];
			}

		}
	}

}

int main() {
	ifstream input("pole.inp");
	ofstream output("pole.out");
	int t;
	input >> t;
	solution();
	while (t--) {
		input >> n >> l >> r;
		output << dp[n][l][r] << "\n";
	}
	return 0;
}