#include <iostream>
#include <fstream>
#include <cstdio>
#include <string>
#pragma warning(disable:4996)
using namespace std;
int dice[6];
int x = 0, y = 0;

typedef struct Position {
	int left, right, front, back, top, bottom;
}Position;

Position dice_Position;

int Position_setting(int index) { //�ε��������� �����Ǽ���.
	if (index == 0) return dice[2];
	else if (index == 1) return dice[4];
	else if (index == 2) return dice[0];
	else if (index == 3) return dice[5];
	else if (index == 4) return dice[1];
	else if (index == 5) return dice[3];
}
void LR_Position(int top, int front) {
	//�̶� top�� index�� index����
	if (top == 0 && front == 1 || top == 1 && front == 2 || top == 2 && front == 4 || top == 4 && front == 0) {
		dice_Position.right = dice[3];
		dice_Position.left = Position_setting(3);
	}
	else if (top == 0 && front == 5 || top == 5 && front == 2 || top == 2 && front == 3 || top == 3 && front == 0) {
		dice_Position.right = dice[1];
		dice_Position.left = Position_setting(1);
	}
	else if (top == 0 && front == 3 || top == 3 && front == 2 || top == 2 && front == 5 || top == 5 && front == 0) {
		dice_Position.right = dice[4];
		dice_Position.left = Position_setting(4);
	}
	else if (top == 1 && front == 5 || top == 5 && front == 4 || top == 4 && front == 3 || top == 3 && front == 1) {
		dice_Position.right = dice[2];
		dice_Position.left = Position_setting(2);
	}
	else if (top == 1 && front == 3 || top == 3 && front == 4 || top == 4 && front == 5 || top == 5 && front == 1) {
		dice_Position.right = dice[0];
		dice_Position.left = Position_setting(0);
	}
	else {
		dice_Position.right = dice[5];
		dice_Position.left = Position_setting(5);
	}

}

void index_finding(int top, int front) { //index ������ ���� ������ ����.
	int top_index, front_index;
	for (int i = 0; i < 6; i++) { if (top == dice[i]) { top_index = i; break; } }
	for (int i = 0; i < 6; i++) { if (front == dice[i]) { front_index = i; break; } }
	dice_Position.top = top;
	dice_Position.front = front;
	dice_Position.bottom = Position_setting(top_index); //top �ε����� �̿��� botton ������
	dice_Position.back = Position_setting(front_index); //front �ε����� �̿��� back ������.
	LR_Position(top_index, front_index); // top�ε����� front �ε����� �̿��� ������� ���� left right ���ϱ�.
}

void function(char ch) { //��������
	int temp = 0;
	if (ch == 'E') {
		y++;
		temp = dice_Position.top;
		dice_Position.top = dice_Position.left;
		dice_Position.left = dice_Position.bottom;
		dice_Position.bottom = dice_Position.right;
		dice_Position.right = temp;
	}
	else if (ch == 'W') {
		y--;
		temp = dice_Position.top;
		dice_Position.top = dice_Position.right;
		dice_Position.right = dice_Position.bottom;
		dice_Position.bottom = dice_Position.left;
		dice_Position.left = temp;
	}
	else if (ch == 'S') {
		x--;
		temp = dice_Position.top;
		dice_Position.top = dice_Position.back;
		dice_Position.back = dice_Position.bottom;
		dice_Position.bottom = dice_Position.front;
		dice_Position.front = temp;
	}
	else {
		x++;
		temp = dice_Position.top;
		dice_Position.top = dice_Position.front;
		dice_Position.front = dice_Position.bottom;
		dice_Position.bottom = dice_Position.back;
		dice_Position.back = temp;
	}
}

void update_Postion(int n, string str) { //�Է¹��� ���ڿ� �ϳ��ϳ��� ������ �����ϴ��Լ�.
	for (int i = 0; i < n; i++)
		function(str[i]); // NWSE �ϳ��� ���������� ������ ����
}
int main() {
	ifstream input_fp("dice2.inp");
	ofstream output_fp("dice2.out");
	string str;
	int t, a, b, n;
	input_fp >> t;
	while (t--) {
		for (int i = 0; i < 6; i++)input_fp >> dice[i];
		input_fp >> a >> b;
		index_finding(a, b);
		input_fp >> n >> str;
		update_Postion(n, str);
		output_fp << y << " " << x << " " << dice_Position.top << " " << dice_Position.front << endl;
		x = 0, y = 0;
	}
	input_fp.close();
	output_fp.close();
	return 0;
}