#include <stdio.h>
#include <string.h>
#include <math.h>
#pragma warning(disable:4996)

char input[10000]; //�Է¹޴� �����Ͱ�

// ��� ���� �������ö� 
char number_a[100]; //���� ������ �迭
char alpa_a[100]; // ���ĺ� ������ �迭
int temp_mod[100]; //�߰��� ���� ���ĺ� �������� ������ �迭

// ��ǥ�� �������ö�
char number_b[100];
char alpa_b[100];


void func2(int result, FILE* out) { //���� ���ϴ��ִ��Լ�.
	int a = result / 26; //��
	int b = result % 26; //������
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

void func1(FILE * out) {  //���ĺ� �ڿ� ���� ������ �Լ� ex)42313
	int count = 0;
	int result = 0;
	for (int i = 0; input[i] != 'C'; i++) { //���� ���� ���ְ� R23C55 �̸� 23�� ��
		count++;
		number_a[i] = input[i + 1];
	}
	for (int i = count + 1; input[i] != NULL; i++) { //�ڿ� 55 ���ϴ� �Լ�
		if (input[i + 1] != NULL) {
			result *= 10;
			result += (input[i] - 48) * 10;
		}
		else result += (input[i] - 48);
	}
	func2(result, out); //���� �ٱ��ϸ� ���ĺ����� ��ȯ�Ϸ� func2 �Ѱ���

}

void fn1(FILE * out) {

	int result = 0;
	for (int i = 0;; i++) { //���� ������ ���ĺ� �ֱ� (���ĺ��� ���ڷ� ��ȯ�Ϸ���).
		if (input[i] < 58) break;
		else alpa_b[i] = input[i];
	}
	for (int i = 0, j = 0; input[i] != NULL; i++) { //���ĺ� �ڿ����� ���ڳֱ� (����Ҷ� ������).
		if (input[i] < 58) {
			number_b[j] = input[i];
			j++;
		}
	}
	int strSize = strlen(alpa_b); //���ĺ��� ����ִ� ���� ���ϱ�
	int temp = strSize; // ���� ����
	for (int i = 0; i < strSize; i++) {
		result += (alpa_b[i] - 64) * pow(26, temp - 1); //ex) BC-> 55 �� ��ȯ
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