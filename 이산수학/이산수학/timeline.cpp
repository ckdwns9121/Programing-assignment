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
	int year, month, day; //��,��,��.
	bool primary_key;// ���۳��� ���ᳯ�� �����ϱ� ���� Ű��. true = ���� false= ����
	int sum; //���� ����� ���ϼ�(?)
}timeline;

timeline date[A];

int func(int size) {
	for (int i = 0; i < size; i++) {
		if (date[i].primary_key) row += 1; //�������� ������ ���ϳ� ����
		else row -= 1; //�������� ������ �� �ϳ� ����
		if (max_row < row) max_row = row; //���� ���� ���� �� �� ����.
	}
	return max_row;
}
bool compare(timeline a, timeline b) {
	if (a.sum == b.sum) return a.primary_key < b.primary_key; //�����ϰ� �������� ������ end ���� ����
	return a.sum < b.sum; //������ �̴� �������̴� ������� ��¥������ ����
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
			if (i % 2 == 0) date[i].primary_key = true; //���ʰ��� �������̴� Ű�� true
			else date[i].primary_key = false; //�����ʰ��� �������̴� Ű�� false
		}
		sort(date, date + (n * 2), compare);
		output_fp << func(n * 2) << endl;
		max_row = 0, row = 0;
		memset(date, 0, sizeof(date));
	}

	return 0;
}