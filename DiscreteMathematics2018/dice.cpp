#include <stdio.h>
#pragma warning(disable:4996)

int dice[10001][7];

int func(int n) {
	int sum = 0; //���� �� ���� ��
	int result = 0; //��� ����� ���� �������� sum �� �ִ�.
	int bottom, top; //��,�Ʒ�
	int bot_index; //�ظ��� �ε�����.
	int max = 0; //������ �ִ�.
	for (int Bottom = 1; Bottom <= 6; Bottom++) { //1���� ���� 6���� ����� ���� ������ 6�� ����.
		bottom = Bottom; //1���� �ٴ��� ���Ƿ� ����.
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < 6; j++) {
				if (dice[i][j] == bottom) bot_index = j; //top ���� ���ϱ� ���� �ٴ��� �ε������� ���س���.
			}
			if (bot_index == 0) top = dice[i][5];
			else if (bot_index == 1) top = dice[i][3];
			else if (bot_index == 2) top = dice[i][4];
			else if (bot_index == 3) top = dice[i][1];
			else if (bot_index == 4) top = dice[i][2];
			else if (bot_index == 5) top = dice[i][0];
			for (int k = 0; k < 6; k++) {
				if (dice[i][k] != top && dice[i][k] != bottom) { //bottom �� floor �� �ƴ� ���� ���.
					if (dice[i][k] > max) max = dice[i][k]; //������ �ִ��̸� ����.
				}
			}
			sum += max; //sum �� �ִ� max �� ����ؼ� ������
			bottom = top; //top�� �״��� �ٴ��� ��.
			max = 0; //�ִ� �ʱ�ȭ.
		}
		if (result < sum) result = sum; //���̽��� 6�� ������ �� ���̽����� �ִ��� �ٸ��� result �� ����.
		sum = 0;
	}
	return result;
}
int main() {
	FILE* input_fp = fopen("dice.inp", "rt");
	FILE* output_fp = fopen("dice.out", "wt");
	int n;
	fscanf(input_fp, "%d", &n);
	for (int i = 0; i < n; i++) {
		fscanf(input_fp, "%d %d %d %d %d %d", &dice[i][0], &dice[i][1], &dice[i][2], &dice[i][3], &dice[i][4], &dice[i][5], &dice[i][6]);
	}
	fprintf(output_fp, "%d", func(n));
	fclose(input_fp);
	fclose(output_fp);
	return 0;
}
