#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#pragma warning(disable:4996)
int N, M;

int Visted(int type, int s, int k, FILE* out) {
	int a = 0, b = 0;
	int result = 0; // 출발점

	if (type == 1) {
		a = (k - 1) / M;
		b = (k - 1) % M;
		if (s == 1) {
			if (a % 2 == 0) {
				result = (a * M) + (b + 1);
				return result;
			}
			else {
				result = (a * M) + (M - b);
				return result;
			}
		}
		else if (s == 2) {
			if (a % 2 == 0) {
				result = (a * M) + (M - b);
				return result;
			}
			else {
				result = (a * M) + (b + 1);
				return result;
			}
		}
		else if (s == 3) {

			if (a % 2 == 0) {
				result = (N * M) - (a * M) - b;
				return result;
			}
			else {
				result = (N * M) - (a * M) - (M - b - 1);
				return result;
			}
		}
		else {
			if (a % 2 == 0) {
				result = ((N * M) - (M - 1)) - (a * M) + b;
				return result;
			}
			else {
				result = ((N * M) - (M - 1)) - (a * M) + (M - (b + 1));
				return result;
			}
		}
	}
	else if (type == 2) {
		a = (k - 1) / N;
		b = (k - 1) % N;
		if (s == 1) {
			result = 1;
			if (a % 2 == 0) {
				result += a + (((k - 1) % N) * M);
				return result;
			}
			else {
				result += a + ((N - 1) * M) - (((k - 1) % N) * M);
				return result;
			}
		}
		else if (s == 2) {
			result = M;
			if (a % 2 == 0) {
				result += -a + (((k - 1) % N) * M);
				return result;
			}
			else {
				result += -a + ((N - 1) * M) - (((k - 1) % N) * M);
				return result;
			}
		}
		else if (s == 3) {
			result = (N * M);
			if (a % 2 == 0) {
				result += -a - (((k - 1) % N) * M);
				return result;
			}
			else {
				result += -a - ((N - 1) * M) + (((k - 1) % N) * M);
				return result;
			}
		}
		else {
			result = ((N - 1) * M + 1);
			if (a % 2 == 0) {
				result += a - (((k - 1) % N) * M);
				return result;
			}
			else {
				result += a - ((N - 1) * M) + (((k - 1) % N) * M);
				return result;
			}
		}
	}
}
int main() {

	FILE* input_fp = fopen("grid1.inp", "rt");
	FILE* output_fp = fopen("grid1.out", "wt");
	int T = 0; //테스트케이스
	int value = 1;
	int t, s, k;
	int count = 0, result = 0;
	N = M = t = s = k = 0;
	//N행M열,t출발타입,s출발점 k이동거리
	char ch; //개행읽을변수

	fscanf(input_fp, "%d", &T);
	fscanf(input_fp, "%c", &ch);
	while (T) {
		fscanf(input_fp, "%d", &N);
		fscanf(input_fp, "%c", &ch);
		fscanf(input_fp, "%d", &M);
		fscanf(input_fp, "%c", &ch);
		fscanf(input_fp, "%d", &t);
		fscanf(input_fp, "%c", &ch);
		fscanf(input_fp, "%d", &s);
		fscanf(input_fp, "%c", &ch);
		fscanf(input_fp, "%d", &k);
		fscanf(input_fp, "%c", &ch);
		if (ch == '\n') {
			fprintf(output_fp, "%d\n", Visted(t, s, k, output_fp));
			count++;
		}
		if (count == T)break;
	}
	fclose(input_fp);
	fclose(output_fp);
	return 0;

}