/**
 * Assignment 02 : Palindrome
 */

#include <fstream>
#include <string>
#include <algorithm>

using namespace std;

int LCS[1001][1001];

string Doreverse(string str) {
	string reverse_str = str;
	reverse(reverse_str.begin(), reverse_str.end());
	return reverse_str;
}

int Ispalindrome(string str, string reverse_str) {

	for (int i = 1; i <= str.size(); i++) {
		for (int j = 1; j <= str.size(); j++) {
			if (str[i - 1] == reverse_str[j - 1])
				LCS[i][j] = LCS[i - 1][j - 1] + 1;
			else
				LCS[i][j] = max(LCS[i][j - 1], LCS[i - 1][j]);
		}
	}

	int len = str.size();
	int result = len - LCS[len][len];
	if (result == 0) return 0;
	else if (result == 1) return 1;
	else if (result == 2) return 2;
	else return -1;

}

int main() {
	ifstream input("palindrome.inp");
	ofstream output("palindrome.out");

	string str;
	int testcase;
	input >> testcase;
	while (testcase--) {
		input >> str;
		output << Ispalindrome(str, Doreverse(str)) << endl;
	}
	input.clear();
	output.clear();
	return 0;
}