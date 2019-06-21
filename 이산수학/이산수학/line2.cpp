#include <stdio.h>
#include <string.h>
#pragma warning(disable:4996)

typedef struct Line2 {
	int before = 0;
	int after = 0;
	int result = 0;
}Line2;

Line2 LIS[1001];

void swap(int n, int bf_index, int af_index) { //after 배열을 before 로 만들기 위한 swap 함수
	int temp = 0;
	for (int k = af_index; af_index < bf_index; af_index++) {
		temp = LIS[af_index].after;
		LIS[af_index].after = LIS[af_index + 1].after;
		LIS[af_index + 1].after = temp;
	}
}

void func(int n) {

	for (int i = n - 1; i >= 0; i--) {
		for (int j = 0; j < n; j++) {
			if (LIS[i].before == LIS[j].after) {
				LIS[LIS[i].before - 1].result = i - j;
				swap(n, i, j);
				break;
			}
		}
	}
}

int main() {
	FILE* input_fp = fopen("line2.inp", "rt");
	FILE* output_fp = fopen("line2.out", "wt");
	int T, n;
	fscanf(input_fp, "%d", &T);
	while (T--) {
		fscanf(input_fp, "%d", &n);
		for (int i = 0; i < n; i++) fscanf(input_fp, "%d", &LIS[i].before);
		for (int i = 0; i < n; i++) fscanf(input_fp, "%d", &LIS[i].after);
		func(n);
		for (int i = 0; i < n; i++) {
			fprintf(output_fp, "%d ", LIS[i].result);
		}
		fprintf(output_fp, "\n");
		memset(LIS, 0, sizeof(LIS));

	}
	fclose(input_fp);
	fclose(output_fp);
	return 0;
}