#include <stdio.h>
#include <string.h>
#pragma warning(disable:4996)
int dp_Array[10001];
int result[10001];
int dp(int org, int arr, int strike, int ball) {
	int strCount = 0, ballCount = 0;
	int n1, n2, n3, n4, o1, o2, o3, o4;
	n1 = arr / 1000, n2 = (arr % 1000) / 100, n3 = (arr % 100) / 10, n4 = arr % 10;
	o1 = org / 1000, o2 = (org % 1000) / 100, o3 = (org % 100) / 10, o4 = org % 10;

	//같은숫자인지아닌지
	if (n1 == n2 || n1 == n3 || n1 == n4 || n2 == n3 || n2 == n4 || n3 == n4) return 1;
	if (o1 == o2 || o1 == o3 || o1 == o4 || o2 == o3 || o2 == o4 || o3 == o4) return 1;
	if (n1 == 0 || n2 == 0 || n3 == 0 || n4 == 0 || o1 == 0 || o2 == 0 || o3 == 0 || o4 == 0) return 1;
	//strCount
	if (n1 == o1) strCount++;
	if (n2 == o2) strCount++;
	if (n3 == o3) strCount++;
	if (n4 == o4) strCount++;
	//ballCount
	if (n1 == o2 || n1 == o3 || n1 == o4) ballCount++;
	if (n2 == o1 || n2 == o3 || n2 == o4) ballCount++;
	if (n3 == o1 || n3 == o2 || n3 == o4) ballCount++;
	if (n4 == o1 || n4 == o2 || n4 == o3) ballCount++;
	//조건에 만족하면 return 0
	if (strike == strCount && ball == ballCount) return 0;

	else return 1;
}

void print(int D[], FILE * output) {
	int count = 0;
	for (int i = 1234; i <= 9876; i++) {
		if (D[i] == 0) {
			result[count] = i;
			count++;
		}
	}
	if (count <= 6) { //6보다 작으면
		fprintf(output, "%d\n", count);
		for (int i = 0; i < sizeof(result) / sizeof(int); i++) {
			if (result[i] != 0)
				fprintf(output, "%d\n", result[i]);
			else break;
		}
	}
	else {
		fprintf(output, "%d\n", count);
		for (int i = 0; i < 3; i++) {
			if (result[i] != 0)
				fprintf(output, "%d\n", result[i]);
			else break;
		}
		for (int i = count - 3; i < count; i++) {
			if (result[i] != 0)
				fprintf(output, "%d\n", result[i]);
			else break;
		}
	}
	return;
}

int main() {
	FILE* input_fp = fopen("numgame.inp", "rt");
	FILE* output_fp = fopen("numgame.out", "wt");
	int testCase, N;
	int strike = 0, ball = 0, arr = 0;
	fscanf(input_fp, "%d", &testCase);
	while (testCase--) {
		fscanf(input_fp, "%d", &N);
		for (int j = 0; j < N; j++) {
			fscanf(input_fp, "%d %d %d", &arr, &strike, &ball);
			for (int x = 1234; x <= 9876; x++) {
				if (dp_Array[x] == 0) {
					dp_Array[x] = dp(x, arr, strike, ball);
				}
			}
		}
		print(dp_Array, output_fp);
		memset(dp_Array, 0, sizeof(dp_Array));
		memset(result, 0, sizeof(result));
	}
	fclose(input_fp);
	fclose(output_fp);
	return 0;
}