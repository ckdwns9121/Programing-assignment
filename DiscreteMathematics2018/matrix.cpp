#include <stdio.h>
#pragma warning(disable:4996)

int LIS[300][300];

int main() {
	FILE* input_fp = fopen("matrix.inp", "rt");
	FILE* output_fp = fopen("matrix.out", "wt");
	int T = 0, n;//테스트케이스
	char ch;
	int result = 0;
	int check = 0, temp;
	fscanf(input_fp, "%d", &T);
	fscanf(input_fp, "%c", &ch);
	while (T--) {
		temp = 0;
		fscanf(input_fp, "%d", &n);
		fscanf(input_fp, "%c", &ch);
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				fscanf(input_fp, "%d ", &LIS[i][j]);
			}
		}
		for (int x = 0; x < n; x++) {
			for (int y = 0; y < n; y++) {
				check = 0;
				if (LIS[x][y] != 1) {
					for (int i = 0; i < n; i++) {
						for (int j = 0; j < n; j++) {
							result = LIS[x][i] + LIS[j][y];
							if (LIS[x][y] == result) {
								check = 1;
								break;
							}
						}
						if (check == 1) break;
					}
					if (check == 0) {
						temp = 1;
						break;
					}
				}
			}
		}
		if (temp == 0) {
			fprintf(output_fp, "1\n");
		}
		else if (temp == 1) {
			fprintf(output_fp, "0\n");
		}

	}
	fclose(input_fp);
	fclose(output_fp);

	return 0;

}