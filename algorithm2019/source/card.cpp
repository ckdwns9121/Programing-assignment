/**
 * Assignment 14 : Card Game
 */
#include<fstream>
#include<algorithm>

using namespace std;
int sum[1001], n, t;
int main() {
	ifstream input("card.inp");
	ofstream output("card.out");
	input >> t;
	while (t--) {
		input >> n;
		int dp[1001] = {};
		for (int i = 1; i <= n; i++) {
			input >> sum[i];
			sum[i] += sum[i - 1];
		}
		for (int left = 1; left <= n; left++) {
			for (int right = n; right >= left; right--) {
				int section_sum = sum[right] - sum[right - left];
				int get_computer = min(dp[right - 1], dp[right]);
				dp[right] = section_sum - get_computer;
			}
		}
		output << dp[n] << "\n";
	}
	return 0;
}
