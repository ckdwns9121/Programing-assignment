#include <stdio.h>
#include <string.h>
#pragma warning(disable:4996)

int row[50][50];
int column[50][50];

void func(int N, int M, FILE* out) {

	int result = 0;
	for (int i = 0; i < N - 1; i++) {
		for (int j = 0; j < M - 1; j++) {
			result = column[i][j] + column[i + 1][j] + row[i][j] + row[i][j + 1];
			if (result != 1 && result != 3) break;
		}
		if (result != 1 && result != 3) break;
	}
	if (result == 1 || result == 3) fprintf(out, "1 ");
	else fprintf(out, "0 ");

}

int main() {

	FILE* input_fp = fopen("paper.inp", "rt");
	FILE* output_fp = fopen("paper.out", "wt");

	int T, N, M;
	char ch;
	fscanf(input_fp, "%d", &T);
	fscanf(input_fp, "%c", &ch);
	while (T--) {
		fscanf(input_fp, "%d %d", &N, &M);
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < M - 1; j++) {
				fscanf(input_fp, "%d", &column[i][j]);
			}
		}
		for (int i = 0; i < N - 1; i++) {
			for (int j = 0; j < M; j++) {
				fscanf(input_fp, "%d", &row[i][j]);
			}
		}
		func(N, M, output_fp);
		memset(column, 0, sizeof(column));
		memset(row, 0, sizeof(row));
	}
	return 0;
}