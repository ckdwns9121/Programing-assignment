#include <stdio.h>
#include <stdlib.h>
#pragma warning(disable:4996)

int main() {

	FILE* input_fp = fopen("cross.inp", "rt");
	FILE* output_fp = fopen("cross.out", "wt");
	int T = 0, n;//테스트케이스
	int value;
	int count = 0;
	int Case = 1;
	char ch;

	fscanf(input_fp, "%d", &T);
	fscanf(input_fp, "%c", &ch);
	while (T--) {
		count = 0;
		fscanf(input_fp, "%d", &n);
		fscanf(input_fp, "%c", &ch);
		int* arr1 = (int*)malloc(sizeof(int) * n);
		int* arr2 = (int*)malloc(sizeof(int) * n);
		for (int i = 0; i < n; i++) {
			fscanf(input_fp, "%d", &value);
			arr1[value - 1] = i;
		}
		fscanf(input_fp, "%c", &ch);
		for (int i = 0; i < n; i++) {
			fscanf(input_fp, "%d", &value);
			arr2[value - 1] = i;
		}
		for (int i = 0; i < n; i++) {
			for (int j = i; j < n; j++) {
				if (arr1[i] < arr1[j] && arr2[i] > arr2[j]) count++;
				if (arr1[i] > arr1[j] && arr2[i] < arr2[j]) count++;
			}
		}
		fprintf(output_fp, "Case %d: %d\n", Case, count);
		Case++;
		free(arr1);
		free(arr2);
	}

	fclose(input_fp);
	fclose(output_fp);
	return 0;
}