#include <stdio.h>
#include <stdlib.h>
#pragma warning(disable:4996)
int LIS[1001][1001];
/*
int Left(int i, int j) {
	int result = 0;
	if (arr[i - 1][j - 1] == -1 && arr[i][j - 1] == -1) return 0;
	else {
		result = (arr[i - 1][j - 1] - arr[i][j - 1])%100;
		if (result < 0) result += 100;
		return result;
	}
}

int Right(int i, int j) {
	int result = 0;
	if (arr[i - 1][j] == -1 && arr[i][j + 1] == -1) return 0;
	else {
		result = (arr[i - 1][j] - arr[i][j + 1])%100;
		if (result < 0) result += 100;
		return result;
	}
}

int Down(int i, int j) {
	int result = 0;
	if (arr[i + 1][j] == -1 && arr[i + 1][j + 1] == -1) return 0;
	else {
		result = (arr[i + 1][j] + arr[i + 1][j + 1])%100;
		if (result < 0) result += 100;
		return result;
	}
}

void func(int num) {
	int Lresult = 0, Rresult = 0, Dresult = 0;
	for (int t = 0; t< num; t++) {
		for (int x = 0; x < num; x++) {
			for (int y = 0; y < x + 1; y++) {
				if (arr[x][y] == -1) {
					Lresult = Left(x, y);
					Rresult = Right(x, y);
					Dresult = Down(x, y);
					if (Lresult != 0) arr[x][y] = Lresult;
					if (Rresult != 0)arr[x][y] = Rresult;
					if (Dresult != 0)arr[x][y] = Dresult;
				}
			}
		}
	}
}
*/

void func2(int num) {
	for (int t = 0; t < num; t++) {
		for (int i = 0; i < num - 1; i++) {
			for (int j = 0; j < i + 1; j++) {
				if (LIS[i + 1][j] != -1 && LIS[i + 1][j + 1] != -1) { //¹Ø¿¡²¨±¸ÇÏ°í
					LIS[i][j] = (LIS[i + 1][j] + LIS[i + 1][j + 1]) % 100;
				}
				else if (LIS[i][j] != -1 && LIS[i + 1][j + 1] != -1) { // //¿À¸¥ÂÊ²¨±¸ÇÏ°í
					LIS[i + 1][j] = (LIS[i][j] - LIS[i + 1][j + 1]);
					if (LIS[i + 1][j] < 0) LIS[i + 1][j] += 100;
				}
				else if (LIS[i + 1][j] != -1 && LIS[i][j] != -1) {
					LIS[i + 1][j + 1] = (LIS[i][j] - LIS[i + 1][j]);
					if (LIS[i + 1][j + 1] < 0) LIS[i + 1][j + 1] += 100;
				}
			}
		}
	}
}
int main() {
	FILE* input_fp = fopen("block.inp", "rt");
	FILE* output_fp = fopen("block.out", "wt");
	int Tcase, n, value;
	char ch;
	fscanf(input_fp, "%d", &Tcase);
	fscanf(input_fp, "%c", &ch);
	while (Tcase--) {
		fscanf(input_fp, "%d", &n);
		fscanf(input_fp, "%c", &ch);
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < i + 1; j++) {
				fscanf(input_fp, "%d", &LIS[i][j]);
			}
		}
		func2(n);
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < i + 1; j++) {
				fprintf(output_fp, "%d ", LIS[i][j]);
			}
			fprintf(output_fp, "\n");
		}
	}
	fclose(input_fp);
	fclose(output_fp);
	return 0;
}