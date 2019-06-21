#include <stdio.h>
#include <string.h>
#pragma warning(disable:4996)
int LIS[1000];
void func(int N, int M) {
	for (int i = 0; i < N; i++) {
		if (LIS[i] < M) {
			LIS[i] = M; return;
		}
	}
}
int index_size() {
	for (int arr_size = 0;; arr_size++)
		if (!LIS[arr_size])
			return arr_size;
}
int main() {
	FILE* input_fp = fopen("entrance.inp", "rt");
	FILE* output_fp = fopen("entrance.out", "wt");
	int t, N, M;
	fscanf(input_fp, "%d", &t);
	while (t--) {
		fscanf(input_fp, "%d", &N);
		for (int i = 0; i < N; i++) {
			fscanf(input_fp, "%d", &M);
			func(N, M);
		}
		fprintf(output_fp, "%d\n", index_size());
		memset(LIS, 0, sizeof(LIS));
	}
	fclose(input_fp);
	fclose(output_fp);
	return 0;
}