#include <iostream>
#include <fstream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <utility>
#pragma warning(disable:4996)
using namespace std;

vector< pair< char, int> > Stone(101);
int jump(int N, int D) {
	int jmp1 = 0, jmp2 = 0, temp = 0, point = 0;
	for (int i = 0; i < N; i++) {
		if (Stone[i].first == 'B') {
			temp = Stone[i].second - point;
			point = Stone[i].second;
			if (jmp1 < temp) jmp1 = temp;
		}
		else if (Stone[i].first == 'S') {
			temp = Stone[i].second - point;
			point = Stone[i].second;
			Stone[i].first = NULL; Stone[i].second = 0;
			if (jmp1 < temp) jmp1 = temp;
			if (Stone[i + 1].first == NULL) break;
			if (Stone[i + 1].first == 'S')i++;
		}
	}
	if (jmp1 < D - point) jmp1 = D - point;
	point = D;
	for (int i = N - 1; i >= 0; i--) {
		if (Stone[i].first == 'B') {
			temp = point - Stone[i].second;
			point = Stone[i].second;
			if (jmp2 < temp) jmp2 = temp;
		}
		else if (Stone[i].first == 'S') {
			temp = point - Stone[i].second;
			point = Stone[i].second;
			Stone[i].first = NULL; Stone[i].second = 0;
			if (jmp2 < temp) jmp2 = temp;
			if (Stone[i - 1].first == 'S')i--;

		}
	}
	if (point > jmp2) jmp2 = point;
	return jmp1 > jmp2 ? jmp1 : jmp2;
}
int main() {
	ifstream input_fp("frog.inp");
	ofstream output_fp("frog.out");
	int testCase, N, D, M;
	int count = 1;
	char ch, bar, n;
	int d;
	input_fp >> testCase;
	while (testCase--) {
		input_fp >> N >> D;
		for (int i = 0; i < N; i++) {
			input_fp >> Stone[i].first >> bar >> Stone[i].second;
		}
		output_fp << "Case " << count << ": " << jump(N, D) << endl;
		count++;
		Stone.clear();
		Stone.resize(101);
	}
	input_fp.close();
	output_fp.close();
	return 0;
}