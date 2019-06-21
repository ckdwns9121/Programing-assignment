#include <stdio.h>
#include <math.h>
#pragma warning(disable:4996)

int min_result = 0;
int max_result = 99999;
int k = 0;
int func(int num, int line) {
	double min_num = 1, max_num = 1;
	double min, max;
	if (line == 1) {
		min_num = 1;
		max_num = 0;
	}
	else {
		for (int i = 1; i < line - 1; i++)  min_num = min_num + i;
		for (int i = 1; i < line - 1; i++) max_num = max_num + (i + 1);
	}
	min = (num - max_num) / line;
	max = (num - min_num) / (line - 1);
	min = ceil(min);
	max = floor(max);
	if (min_result < min) min_result = min;
	if (max_result > max) max_result = max;
	if (max_result == min_result) {
		k = max_result;
		return k;
	}
	else if (max_result != min_result) {
		return -1;
	}
}

int main() {
	FILE* input_fp = fopen("line.inp", "rt");
	FILE* output_fp = fopen("line.out", "wt");
	int count = 1;
	int T, M, num, line, result;
	fscanf(input_fp, "%d", &T);
	while (T--) {
		fscanf(input_fp, "%d", &M);
		for (int i = 0; i < M; i++) {
			fscanf(input_fp, "%d %d", &num, &line);
			result = func(num, line);
			if (result == -1) count++;
		}
		if (result == -1)fprintf(output_fp, "-1\n");
		else fprintf(output_fp, "%d %d\n", count, result);
		result = 0, count = 1;
		max_result = 99999;
		min_result = 0;

	}
	fclose(input_fp);
	fclose(output_fp);
	return 0;
}
