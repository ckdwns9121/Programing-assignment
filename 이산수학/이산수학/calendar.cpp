#include <stdio.h>
#include <string.h>
#pragma warning(disable:4996)
typedef struct calendar {
	int year = 0; //몇년
	int month = 0; //몇월
	int day = 0; //몇일
	int week = 0; //몇번쨰
}calendar;
char d_week[2]; //요일
calendar LIS[2];
//16 년 1월이 6주차 까지 있어서 6주로 만듦.
// 0일 1월 2화 3수 4목 5금 6토
//달력 만들기 ex)2017년 5월달 달력
//달력을 만들고나면 몇번째에 해당하는 요일을 구할수있음 예로 2번째 금요일
int date[6][7]; //달력
int Check_Day(int y, int m, int d) { //날짜가 맞는지판별 
	int month[] = { 31,28,31,30,31,30,31,31,30,31,30,31 };
	if (!(y % 4) && y % 100 || !(y % 400)) month[1]++; //윤달이면 2월 29일
	if (d > month[m - 1]) return 0; //입력받은 day 가 현재 달의 날보다 많으면 0리턴
	else return 1; //아니면 1리턴
}
int subtract(int y, int m, int d) { //1년1월1일부터 y년m월d일 까지의 총일수.
	int month[] = { 31,28,31,30,31,30,31,31,30,31,30,31 };
	int sum = 0;
	sum = (y - 1) * 365 + (y - 1) / 4 - (y - 1) / 100 + (y - 1) / 400;
	if (!(y % 4) && y % 100 || !(y % 400)) month[1]++; //윤달이면 2월 29일
	for (int i = 0; i < m - 1; i++) sum += month[i];
	sum += d; //나머지 day를 더함
	return sum;
}

void Make_Calendar2(int result, int m, int c) {//실제 달력만들기
	int month[] = { 31,28,31,30,31,30,31,31,30,31,30,31 };
	if (c == 1) month[1]++; //윤달일 경우 2월달 ++
	int check = 0; //첫째 줄부터 넣게 체크변수선언.
	int count = 0; //1월부터 31일까지 넣는 변수
	for (int i = 0; i < 6; i++) {
		if (check == 0) {
			for (int k = result; k < 7; k++) { //첫번쨰 주는 구한요일 부터 넣어야함 ex)수요일시작
				date[0][k] = count + 1; //구한 요일부터 넣고.
				count++;
			}
			check = 1; //첫번째꺼 다넣었으면 더이상 첫번째에 넣으면 안대니 check=1
		}
		else {
			for (int j = 0; j < 7; j++) { //2째주 부터 다시 값넣기
				date[i][j] = count + 1;
				count++;
				if (count == month[m - 1])break; //다넣었으면
			}
		}
		if (count == month[m - 1])break; //다넣었으면 break
	}
}

void Make_Calendar(int y, int m) { //달력만들기전 시작 요일 구하고 윤달인지 판별하기
	int month[] = { 31,28,31,30,31,30,31,31,30,31,30,31 };
	int sum = 0;
	int check = 0; //윤달일때 1 아닐때 0
	int result = 0;
	sum = (y - 1) * 365 + (y - 1) / 4 - (y - 1) / 100 + (y - 1) / 400; //1년1월1일부터 y년1월1일까지 일수
	if (!(y % 4) && y % 100 || !(y % 400)) {
		month[1]++; //윤달이면 2월달 총 날짜를 29일로 만듦
		check = 1; //윤달일때 check =1
	}
	for (int i = 0; i < m - 1; i++) sum += month[i]; //y년1월1일부터 y년 m월까지 일수
	result = (sum % 7) + 1; //Mod 7하면 무슨요일인지 나옴.
	if (result == 7) result = 0; //시작요일 구하기
	Make_Calendar2(result, m, check); //시작요일과 윤달인지 아닌지 판별한 값을 달력만들때 념겨줌
}

int What_day() { // 요일의 값을 구할때.
	// 0일요일 ~ 6토요일
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
	int day_index; //요일 구할때 인덱스
	char ch;
	int count = 1;
	int check1 = 0, check2 = 0; //type0 일경우 왼쪽 날짜와 오른쪽날짜가 맞는지 판별하기 위해 2개선언.
	while (1) {
		fscanf(input_fp, "%d", &type);
		if (type == -1)break;
		if (type == 0) {
			//2018-2-28 2017-2-28
			for (int i = 0; i < 2; i++) {
				fscanf(input_fp, "%d%c%d%c%d", &LIS[i].year, &ch, &LIS[i].month, &ch, &LIS[i].day);
			}
			check1 = Check_Day(LIS[0].year, LIS[0].month, LIS[0].day); //왼쪽날짜 판별
			check2 = Check_Day(LIS[1].year, LIS[1].month, LIS[1].day); //오른쪽 날짜 판별
			if (check1 == 0 || check2 == 0) fprintf(output_fp, "-1\n"); //둘중 하나라도 틀리면 -1출력
			else { //맞는 날짜이면
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
			day_index = What_day(); //무슨 요일인지 구하는 변수
			for (int j = 0; j < 6; j++) { //그 요일만 세로로 도는 for문 
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
			check1 = Check_Day(LIS[0].year, LIS[0].month, LIS[0].day); //왼쪽 입력날짜가 맞는지 판단
			if (LIS[1].day == 0 || check1 == 0) fprintf(output_fp, "-1\n"); //0이들어있단 소리는 그 자리에 날짜가 없는거임
			else {
				t1_result = subtract(LIS[1].year, LIS[1].month, LIS[1].day) - subtract(LIS[0].year, LIS[0].month, LIS[0].day);
				if (t1_result < 0)t1_result *= -1;
				fprintf(output_fp, "%d\n", t1_result);
			}
			memset(LIS, 0, sizeof(LIS));
			memset(date, 0, sizeof(date));
			count = 1;
		}
		else if (type == 2) { //type 1이랑 순서만 다름
			//1999-12-5-Sat 1000-11-5
			for (int i = 0; i < 2; i++) {
				if (i == 0) fscanf(input_fp, "%d%c%d%c%d%c%s", &LIS[i].year, &ch, &LIS[i].month, &ch, &LIS[i].week, &ch, &d_week);
				else fscanf(input_fp, "%d%c%d%c%d", &LIS[i].year, &ch, &LIS[i].month, &ch, &LIS[i].day);
			}
			Make_Calendar(LIS[0].year, LIS[0].month); //여기까지오면 달력이 만들어짐.
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
			//둘중 하나라도 0이면 맞는 날짜가 아니기 떄문에 -1출력
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

