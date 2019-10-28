/**
 * Assignment 08 : BitMap
 */

#include <fstream>
#include <string>
#pragma warning(disable:4996)

using namespace std;


int CASES[24][6] = {
	{ 0,1,2,3,4,5 },{ 0,2,4,1,3,5 },{ 0,3,1,4,2,5 },{ 0,4,3,2,1,5 },
	{ 5,4,2,3,1,0 },{ 5,3,4,1,2,0 },{ 5,1,3,2,4,0 },{ 5,2,1,4,3,0 },
	{ 1,0,3,2,5,4 },{ 1,2,0,5,3,4 },{ 1,5,2,3,0,4 },{ 1,3,5,0,2,4 },
	{ 4,5,3,2,0,1 },{ 4,2,5,0,3,1 },{ 4,0,2,3,5,1 },{ 4,3,0,5,2,1 },
	{ 2,0,1,4,5,3 },{ 2,4,0,5,1,3 },{ 2,5,4,1,0,3 },{ 2,1,5,0,4,3 },
	{ 3,5,1,4,0,2 },{ 3,4,5,0,1,2 },{ 3,0,4,1,5,2 },{ 3,1,0,5,4,2 }
};

char cube1[6], cube2[6], temp[6];

bool finish() {
	int count = 0;
	char ch = cube1[0];
	for (int i = 0; i < 6; i++) {
		if (ch == cube1[i]) count++;
		if (ch == cube2[i]) count++;
	}
	if (count == 12) return false;
	else return true;
}
bool func() {
	bool check = false;
	for (int i = 0; i < 24; i++) {
		for (int j = 0; j < 6; j++) {
			int index = CASES[i][j];
			temp[j] = cube2[index];
		}
		if ((temp[0] == cube1[0]) && (temp[1] == cube1[1]) && (temp[2] == cube1[2]) && (temp[3] == cube1[3]) && (temp[4] == cube1[4]) && (temp[5] == cube1[5])) {
			return true;
		}
		else check = false;
	}
	return check;
}

int main() {
	ifstream input("cube.inp");
	ofstream output("cube.out");
	while (true) {
		for (int i = 0; i < 6; i++)
			input >> cube1[i];
		for (int i = 0; i < 6; i++)
			input >> cube2[i];
		if (!finish()) {
			output << "TRUE\n";
			return 0;
		}
		if (func()) output << "TRUE\n";
		else output << "FALSE\n";

	}
	input.close();
	output.close();
	return 0;
}