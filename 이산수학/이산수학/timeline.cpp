#include <iostream>
#include <string>
#include <cstring>
#include <algorithm>
#include <fstream>
#pragma warning(disable:4996)
using namespace std;
#define A 200000
#define YEAR 372
#define MONTH 31
int row = 0;
int max_row = 0;

typedef struct timeline {
	int year, month, day; //년,월,일.
	bool primary_key;// 시작날과 종료날을 구분하기 위한 키값. true = 시작 false= 종료
	int sum; //어림잡아 계산한 총일수(?)
}timeline;

timeline date[A];

int func(int size) {
	for (int i = 0; i < size; i++) {
		if (date[i].primary_key) row += 1; //시작일을 만나면 행하나 증가
		else row -= 1; //종료일을 만나면 행 하나 감소
		if (max_row < row) max_row = row; //행을 제일 많이 쓴 값 저장.
	}
	return max_row;
}
bool compare(timeline a, timeline b) {
	if (a.sum == b.sum) return a.primary_key < b.primary_key; //시작일과 종료일이 같을때 end 먼저 정렬
	return a.sum < b.sum; //시작일 이던 종료일이던 상관없이 날짜순으로 정렬
}
int main() {
	ifstream input_fp("timeline.inp");
	ofstream output_fp("timeline.out");
	int t, n;
	char ch;
	input_fp >> t;
	while (t--) {
		input_fp >> n;
		for (int i = 0; i < n * 2; i++) {
			input_fp >> date[i].year >> ch >> date[i].month >> ch >> date[i].day;
			date[i].sum = (date[i].year * YEAR) + (date[i].month * MONTH) + (date[i].day);
			if (i % 2 == 0) date[i].primary_key = true; //왼쪽값이 시작일이니 키값 true
			else date[i].primary_key = false; //오른쪽값이 종료일이니 키값 false
		}
		sort(date, date + (n * 2), compare);
		output_fp << func(n * 2) << endl;
		max_row = 0, row = 0;
		memset(date, 0, sizeof(date));
	}

	return 0;
}