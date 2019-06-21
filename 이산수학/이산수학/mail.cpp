#include <stdio.h>
#include <string.h>
#pragma warning(disable:4996)

char arr[10001];
char A[6] = { '0','0','0','0','0','0' };
char B[6] = { '0','0','1','1','1','1' };
char C[6] = { '0','1','0','0','1','1' };
char dp_Array[6] = { '0','1','1','1','0','0' };
char E[6] = { '1','0','0','1','1','0' };
char F[6] = { '1','0','1','0','0','1' };
char G[6] = { '1','1','0','1','0','1' };
char H[6] = { '1','1','1','0','1','0' };


void a(FILE* out) {
	int Acount = 0;
	int Bcount = 0;
	int Ccount = 0;
	int Dcount = 0;
	int Ecount = 0;
	int Fcount = 0;
	int Gcount = 0;
	int Hcount = 0;
	int j = 0;
	int cnt = 0;
	int index = 0;
	for (int i = 0; i < 10001; i++) {
		if (arr[index] == '\0') break;
		else index++;
	}
	for (int i = 0; i < index; i++) {
		if (arr[i] == '\0')	break;
		if (j == 6) j = 0;
		if (A[j] == arr[i]) Acount++;
		if (B[j] == arr[i]) Bcount++;
		if (C[j] == arr[i]) Ccount++;
		if (dp_Array[j] == arr[i]) Dcount++;
		if (E[j] == arr[i]) Ecount++;
		if (F[j] == arr[i]) Fcount++;
		if (G[j] == arr[i]) Gcount++;
		if (H[j] == arr[i]) Hcount++;
		cnt++; j++;
		if (cnt == 6) {
			if (Acount >= 5) {
				fprintf(out, "A");
				Acount = Bcount = Ccount = Dcount = Ecount = Fcount = Gcount = Hcount = cnt = 0;
			}
			else if (Bcount >= 5) {
				fprintf(out, "B");
				Acount = Bcount = Ccount = Dcount = Ecount = Fcount = Gcount = Hcount = cnt = 0;
			}
			else if (Ccount >= 5) {
				fprintf(out, "C");
				Acount = Bcount = Ccount = Dcount = Ecount = Fcount = Gcount = Hcount = cnt = 0;
			}
			else if (Dcount >= 5) {
				fprintf(out, "D");
				Acount = Bcount = Ccount = Dcount = Ecount = Fcount = Gcount = Hcount = cnt = 0;
			}
			else if (Ecount >= 5) {
				fprintf(out, "E");
				Acount = Bcount = Ccount = Dcount = Ecount = Fcount = Gcount = Hcount = cnt = 0;
			}
			else if (Fcount >= 5) {
				fprintf(out, "F");
				Acount = Bcount = Ccount = Dcount = Ecount = Fcount = Gcount = Hcount = cnt = 0;
			}
			else if (Gcount >= 5) {
				fprintf(out, "G");
				Acount = Bcount = Ccount = Dcount = Ecount = Fcount = Gcount = Hcount = cnt = 0;
			}
			else if (Hcount >= 5) {
				fprintf(out, "H");
				Acount = Bcount = Ccount = Dcount = Ecount = Fcount = Gcount = Hcount = cnt = 0;
			}
			else {
				fprintf(out, "X");
				Acount = Bcount = Ccount = Dcount = Ecount = Fcount = Gcount = Hcount = cnt = 0;
			}
		}
	}
}
int main() {
	FILE* input_fp = fopen("mail.inp", "rt");
	FILE* output_fp = fopen("mail.out", "wt");
	int T, i, num;//검사하고자 하는총 경우의 수 T ,인덱스i ,숫자 nuM
	T = i = num = 0;
	char ch; // 개행확인.
	fscanf(input_fp, "%d", &T);
	fscanf(input_fp, "%c", &ch);
	while (T--) {
		fscanf(input_fp, "%d", &num);
		fscanf(input_fp, "%c", &ch);
		while (1) {
			ch = fgetc(input_fp);
			if (ch == '\n') break;
			else {
				arr[i] = ch;
				i++;
			}
		}
		a(output_fp);
		fprintf(output_fp, "\n");
		memset(arr, '\0', sizeof(arr));
		i = 0;
	}

	fclose(input_fp);
	fclose(output_fp);
	return 0;
}


