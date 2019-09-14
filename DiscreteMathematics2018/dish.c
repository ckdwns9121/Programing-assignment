#include <stdio.h>
#include <string.h>
#pragma warning(disable :4996)

void dish(char arr[], FILE* out) {
	int index = 0;
	int high = 0;
	for (int i = 0; i < 1000; i++) {
		if (arr[i] == '\0') break;
		else index++;
	}
	for (int i = 0; i < index; i++) {
		if (arr[i] == arr[i + 1]) high += 5;
		else  high += 10;
	}
	fprintf(out, "%d\n", high);
}
int main() {
	FILE* input_fp = fopen("dish.inp", "rt");
	FILE* output_fp = fopen("dish.out", "wt");
	int T = 0, i = 0, n = 0, count = 0;
	char ch;
	char arr[1000] = { '0' , };
	fscanf(input_fp, "%d", &T);
	fscanf(input_fp, "%c", &ch);
	while (1) {
		fscanf(input_fp, "%d", &n);
		fscanf(input_fp, "%c", &ch);
		for (int j = 0; j <= n; j++) {
			ch = fgetc(input_fp);
			if (ch == '\n') {
				dish(arr, output_fp);
				memset(arr, '\0', sizeof(arr));
				i = 0;
			}
			else {
				arr[i] = ch;
				i++;
			}
		}
		count++;
		if (count == T) break;
	}
	fclose(input_fp);
	fclose(output_fp);
	return 0;
}