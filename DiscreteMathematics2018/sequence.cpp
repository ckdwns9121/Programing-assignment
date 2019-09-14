#include <stdio.h>
#pragma warning (disable : 4996)

void func(long long A, long long L, FILE* out) {

	int count = 0;

	while (1) {
		if (A == 1) break;
		if (A % 2 == 0) {
			A = A / 2;
			count++;
		}
		else {
			A = A * 3 + 1;
			if (A > L)break;
			else count++;
		}
	}
	fprintf(out, "number of terms = %d\n", count + 1);
}

int main() {
	FILE* input_fp = fopen("sequence.inp", "rt");
	FILE* output_fp = fopen("sequence.out", "wt");

	long long A, L;
	for (int i = 1;; i++) {
		fscanf(input_fp, "%lld%lld", &A, &L);
		if (A < 0 && L < 0) break;
		else {
			fprintf(output_fp, "Case %d: A = %lld, limit = %lld, ", i, A, L);
			func(A, L, output_fp);
		}

	}
	fclose(input_fp);
	fclose(output_fp);
	return 0;
}