#include <stdio.h>
#include <string.h>
#pragma warning(disable:4996)
typedef struct calendar {
	int year = 0; //���
	int month = 0; //���
	int day = 0; //����
	int week = 0; //�����
}calendar;
char d_week[2]; //����
calendar LIS[2];
//16 �� 1���� 6���� ���� �־ 6�ַ� ����.
// 0�� 1�� 2ȭ 3�� 4�� 5�� 6��
//�޷� ����� ex)2017�� 5���� �޷�
//�޷��� ������� ���°�� �ش��ϴ� ������ ���Ҽ����� ���� 2��° �ݿ���
int date[6][7]; //�޷�
int Check_Day(int y, int m, int d) { //��¥�� �´����Ǻ� 
	int month[] = { 31,28,31,30,31,30,31,31,30,31,30,31 };
	if (!(y % 4) && y % 100 || !(y % 400)) month[1]++; //�����̸� 2�� 29��
	if (d > month[m - 1]) return 0; //�Է¹��� day �� ���� ���� ������ ������ 0����
	else return 1; //�ƴϸ� 1����
}
int subtract(int y, int m, int d) { //1��1��1�Ϻ��� y��m��d�� ������ ���ϼ�.
	int month[] = { 31,28,31,30,31,30,31,31,30,31,30,31 };
	int sum = 0;
	sum = (y - 1) * 365 + (y - 1) / 4 - (y - 1) / 100 + (y - 1) / 400;
	if (!(y % 4) && y % 100 || !(y % 400)) month[1]++; //�����̸� 2�� 29��
	for (int i = 0; i < m - 1; i++) sum += month[i];
	sum += d; //������ day�� ����
	return sum;
}

void Make_Calendar2(int result, int m, int c) {//���� �޷¸����
	int month[] = { 31,28,31,30,31,30,31,31,30,31,30,31 };
	if (c == 1) month[1]++; //������ ��� 2���� ++
	int check = 0; //ù° �ٺ��� �ְ� üũ��������.
	int count = 0; //1������ 31�ϱ��� �ִ� ����
	for (int i = 0; i < 6; i++) {
		if (check == 0) {
			for (int k = result; k < 7; k++) { //ù���� �ִ� ���ѿ��� ���� �־���� ex)�����Ͻ���
				date[0][k] = count + 1; //���� ���Ϻ��� �ְ�.
				count++;
			}
			check = 1; //ù��°�� �ٳ־����� ���̻� ù��°�� ������ �ȴ�� check=1
		}
		else {
			for (int j = 0; j < 7; j++) { //2°�� ���� �ٽ� ���ֱ�
				date[i][j] = count + 1;
				count++;
				if (count == month[m - 1])break; //�ٳ־�����
			}
		}
		if (count == month[m - 1])break; //�ٳ־����� break
	}
}

void Make_Calendar(int y, int m) { //�޷¸������ ���� ���� ���ϰ� �������� �Ǻ��ϱ�
	int month[] = { 31,28,31,30,31,30,31,31,30,31,30,31 };
	int sum = 0;
	int check = 0; //�����϶� 1 �ƴҶ� 0
	int result = 0;
	sum = (y - 1) * 365 + (y - 1) / 4 - (y - 1) / 100 + (y - 1) / 400; //1��1��1�Ϻ��� y��1��1�ϱ��� �ϼ�
	if (!(y % 4) && y % 100 || !(y % 400)) {
		month[1]++; //�����̸� 2���� �� ��¥�� 29�Ϸ� ����
		check = 1; //�����϶� check =1
	}
	for (int i = 0; i < m - 1; i++) sum += month[i]; //y��1��1�Ϻ��� y�� m������ �ϼ�
	result = (sum % 7) + 1; //Mod 7�ϸ� ������������ ����.
	if (result == 7) result = 0; //���ۿ��� ���ϱ�
	Make_Calendar2(result, m, check); //���ۿ��ϰ� �������� �ƴ��� �Ǻ��� ���� �޷¸��鶧 �����
}

int What_day() { // ������ ���� ���Ҷ�.
	// 0�Ͽ��� ~ 6�����
	int num;
	if (d_week[0] == 'M' && d_week[1] == 'o') num = 1;
	else if (d_week[0] == 'T' && d_week[1] == 'u')num = 2;
	else if (d_week[0] == 'W' && d_week[1] == 'e')num = 3;
	else if (d_week[0] == 'T' && d_week[1] == 'h')num = 4;
	else if (d_week[0] == 'F' && d_week[1] == 'r')num = 5;
	else if (d_week[0] == 'S' && d_week[1] == 'a')num = 6;
	else if (d_week[0] == 'S' && d_week[1] == 'u')num = 0;
	return num;
}

int main() {
	FILE* input_fp = fopen("calendar.inp", "rt");
	FILE* output_fp = fopen("calendar.out", "wt");
	int type, y, m, d;
	int t0_result = 0, t1_result = 0, t2_result = 0, t3_result = 0;
	int day_index; //���� ���Ҷ� �ε���
	char ch;
	int count = 1;
	int check1 = 0, check2 = 0; //type0 �ϰ�� ���� ��¥�� �����ʳ�¥�� �´��� �Ǻ��ϱ� ���� 2������.
	while (1) {
		fscanf(input_fp, "%d", &type);
		if (type == -1)break;
		if (type == 0) {
			//2018-2-28 2017-2-28
			for (int i = 0; i < 2; i++) {
				fscanf(input_fp, "%d%c%d%c%d", &LIS[i].year, &ch, &LIS[i].month, &ch, &LIS[i].day);
			}
			check1 = Check_Day(LIS[0].year, LIS[0].month, LIS[0].day); //���ʳ�¥ �Ǻ�
			check2 = Check_Day(LIS[1].year, LIS[1].month, LIS[1].day); //������ ��¥ �Ǻ�
			if (check1 == 0 || check2 == 0) fprintf(output_fp, "-1\n"); //���� �ϳ��� Ʋ���� -1���
			else { //�´� ��¥�̸�
				t0_result = subtract(LIS[1].year, LIS[1].month, LIS[1].day) - subtract(LIS[0].year, LIS[0].month, LIS[0].day);
				if (t0_result < 0) t0_result *= -1;
				fprintf(output_fp, "%d\n", t0_result);
			}
			memset(LIS, 0, sizeof(LIS));
		}
		else if (type == 1) {
			//2017-5-13 2017-5-2-Sat
			for (int i = 0; i < 2; i++) {
				if (i == 0)fscanf(input_fp, "%d%c%d%c%d", &LIS[i].year, &ch, &LIS[i].month, &ch, &LIS[i].day);
				else fscanf(input_fp, "%d%c%d%c%d%c%s", &LIS[i].year, &ch, &LIS[i].month, &ch, &LIS[i].week, &ch, &d_week);
			}
			Make_Calendar(LIS[1].year, LIS[1].month);
			day_index = What_day(); //���� �������� ���ϴ� ����
			for (int j = 0; j < 6; j++) { //�� ���ϸ� ���η� ���� for�� 
				if (date[j][day_index] == 0)continue;
				else {
					if (count == LIS[1].week) {
						LIS[1].day = date[j][day_index];
						break;
					}
					else {
						count++;
					}
				}
			}
			check1 = Check_Day(LIS[0].year, LIS[0].month, LIS[0].day); //���� �Է³�¥�� �´��� �Ǵ�
			if (LIS[1].day == 0 || check1 == 0) fprintf(output_fp, "-1\n"); //0�̵���ִ� �Ҹ��� �� �ڸ��� ��¥�� ���°���
			else {
				t1_result = subtract(LIS[1].year, LIS[1].month, LIS[1].day) - subtract(LIS[0].year, LIS[0].month, LIS[0].day);
				if (t1_result < 0)t1_result *= -1;
				fprintf(output_fp, "%d\n", t1_result);
			}
			memset(LIS, 0, sizeof(LIS));
			memset(date, 0, sizeof(date));
			count = 1;
		}
		else if (type == 2) { //type 1�̶� ������ �ٸ�
			//1999-12-5-Sat 1000-11-5
			for (int i = 0; i < 2; i++) {
				if (i == 0) fscanf(input_fp, "%d%c%d%c%d%c%s", &LIS[i].year, &ch, &LIS[i].month, &ch, &LIS[i].week, &ch, &d_week);
				else fscanf(input_fp, "%d%c%d%c%d", &LIS[i].year, &ch, &LIS[i].month, &ch, &LIS[i].day);
			}
			Make_Calendar(LIS[0].year, LIS[0].month); //����������� �޷��� �������.
			day_index = What_day();
			for (int j = 0; j < 6; j++) {
				if (date[j][day_index] == 0)continue;
				else if (date[j][day_index] != 0) {
					if (count == LIS[0].week) {
						LIS[0].day = date[j][day_index];
						break;
					}
					else {
						count++;
					}
				}
			}
			check1 = Check_Day(LIS[1].year, LIS[1].month, LIS[1].day);
			if (LIS[0].day == 0 || check1 == 0) fprintf(output_fp, "-1\n");
			else {
				t2_result = subtract(LIS[1].year, LIS[1].month, LIS[1].day) - subtract(LIS[0].year, LIS[0].month, LIS[0].day);
				if (t2_result < 0)t2_result *= -1;
				fprintf(output_fp, "%d\n", t2_result);
			}
			memset(LIS, 0, sizeof(LIS));
			memset(date, 0, sizeof(date));
			count = 1;
		}
		else if (type == 3) {
			//3 2017 - 9 - 1 - Thu 2017 - 9 - 2 - Fri
			for (int i = 0; i < 2; i++) {
				fscanf(input_fp, "%d%c%d%c%d%c%s", &LIS[i].year, &ch, &LIS[i].month, &ch, &LIS[i].week, &ch, &d_week);
				Make_Calendar(LIS[i].year, LIS[i].month);
				day_index = What_day();
				for (int j = 0; j < 6; j++) {
					if (date[j][day_index] == 0)continue;
					else {
						if (count == LIS[i].week) {
							LIS[i].day = date[j][day_index];
							break;
						}
						else {
							count++;
						}
					}
				}
				memset(date, 0, sizeof(date));
				count = 1;
			}
			//���� �ϳ��� 0�̸� �´� ��¥�� �ƴϱ� ������ -1���
			if (LIS[0].day == 0 || LIS[1].day == 0) fprintf(output_fp, "-1\n");
			else {
				t3_result = subtract(LIS[1].year, LIS[1].month, LIS[1].day) - subtract(LIS[0].year, LIS[0].month, LIS[0].day);
				if (t3_result < 0) t3_result *= -1;
				fprintf(output_fp, "%d\n", t3_result);
			}
			memset(LIS, 0, sizeof(LIS));
			memset(date, 0, sizeof(date));
		}
	}
	fclose(input_fp);
	fclose(output_fp);
	return 0;
}

