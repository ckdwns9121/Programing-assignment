#include <stdio.h>
#include <string.h>
#include <math.h>
#pragma warning(disable:4996)

char input[10000]; //입력받는 데이터값

// 행과 열이 먼저나올때 
char number_a[100]; //숫자 저장할 배열
char alpa_a[100]; // 알파벳 저장할 배열
int temp_mod[100]; //중간에 오는 알파벳 나머지값 저장할 배열

// 좌표가 먼저나올때
char number_b[100];
char alpa_b[100];


void func2(int result, FILE* out) { //영어 구하는주는함수.
	int a = result / 26; //몫
	int b = result % 26; //나머지
	int temp_size = 0;
	int count = 0;
	memset(temp_mod, -1, sizeof(temp_mod));
	if (b == 0) { b = 26; a--; }
	if (result < 27) alpa_a[0] = b + 64;
	else {
		if (a > 26) {
			for (int i = 0; a > 26; i++) {
				temp_mod[i] = b;
				b = a % 26;
				a = a / 26;
				count++;
				if (b == 0) {
					a--; b = 26;
				}
			}
			temp_mod[count] = b;
			temp_mod[count + 1] = a;
		}
		else {
			temp_mod[count] = b;
			temp_mod[count + 1] = a;
		}
	}
	for (int i = 0; temp_mod[i] != -1; i++) temp_size++;
	for (int i = 0; temp_mod[i] != -1; i++, temp_size--) alpa_a[i] = temp_mod[temp_size - 1] + 64;
	for (int i = 0; alpa_a[i] != NULL; i++) fprintf(out, "%c", alpa_a[i]);
	for (int i = 0; number_a[i] != 'C'; i++) fprintf(out, "%c", number_a[i]);
	fprintf(out, "\n");
}

void func1(FILE * out) {  //알파벳 뒤에 숫자 빼오는 함수 ex)42313
	int count = 0;
	int result = 0;
	for (int i = 0; input[i] != 'C'; i++) { //숫자 먼저 빼주고 R23C55 이면 23을 뺌
		count++;
		number_a[i] = input[i + 1];
	}
	for (int i = count + 1; input[i] != NULL; i++) { //뒤에 55 구하는 함수
		if (input[i + 1] != NULL) {
			result *= 10;
			result += (input[i] - 48) * 10;
		}
		else result += (input[i] - 48);
	}
	func2(result, out); //숫자 다구하면 알파벳으로 변환하러 func2 넘겨줌

}

void fn1(FILE * out) {

	int result = 0;
	for (int i = 0;; i++) { //숫자 전까지 알파벳 넣기 (알파벳을 숫자로 전환하려고).
		if (input[i] < 58) break;
		else alpa_b[i] = input[i];
	}
	for (int i = 0, j = 0; input[i] != NULL; i++) { //알파벳 뒤에오는 숫자넣기 (출력할때 쓰려고).
		if (input[i] < 58) {
			number_b[j] = input[i];
			j++;
		}
	}
	int strSize = strlen(alpa_b); //알파벳이 들어있는 길이 구하기
	int temp = strSize; // 길이 저장
	for (int i = 0; i < strSize; i++) {
		result += (alpa_b[i] - 64) * pow(26, temp - 1); //ex) BC-> 55 로 변환
		temp--;
	}
	fprintf(out, "R%sC%d\n", number_b, result);
}
void judgment(FILE * out) {
	if (input[0] == 'R' && input[1] >= '0' && input[1] <= '9') func1(out);
	else fn1(out);
}
int main() {

	FILE* input_fp = fopen("spreadsheet.inp", "rt");
	FILE* output_fp = fopen("spreadsheet.out", "wt");

	int T;
	char ch;
	fscanf(input_fp, "%d", &T);
	fscanf(input_fp, "%c", &ch);
	while (T--) {
		fscanf(input_fp, "%s", &input);
		judgment(output_fp);
		memset(number_a, 0, sizeof(number_a));
		memset(number_b, 0, sizeof(number_b));
		memset(alpa_a, 0, sizeof(alpa_a));
		memset(alpa_b, 0, sizeof(alpa_b));
		memset(temp_mod, -1, sizeof(temp_mod));
	}
	fclose(input_fp);
	fclose(output_fp);
	return 0;
}