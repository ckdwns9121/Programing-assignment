#include <stdio.h>
#pragma warning(disable:4996)

int dice[10001][7];

int func(int n) {
	int sum = 0; //댓값을 다 더한 값
	int result = 0; //모든 경우의 수를 돌고나서의 sum 의 최댓값.
	int bottom, top; //밑,아래
	int bot_index; //밑면의 인덱스값.
	int max = 0; //옆면의 최댓값.
	for (int Bottom = 1; Bottom <= 6; Bottom++) { //1부터 시작 6가지 경우의 수가 있으니 6번 돌림.
		bottom = Bottom; //1부터 바닥을 임의로 설정.
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < 6; j++) {
				if (dice[i][j] == bottom) bot_index = j; //top 값을 구하기 위해 바닥의 인덱스값을 구해놓음.
			}
			if (bot_index == 0) top = dice[i][5];
			else if (bot_index == 1) top = dice[i][3];
			else if (bot_index == 2) top = dice[i][4];
			else if (bot_index == 3) top = dice[i][1];
			else if (bot_index == 4) top = dice[i][2];
			else if (bot_index == 5) top = dice[i][0];
			for (int k = 0; k < 6; k++) {
				if (dice[i][k] != top && dice[i][k] != bottom) { //bottom 과 floor 가 아닌 옆면 계산.
					if (dice[i][k] > max) max = dice[i][k]; //옆면이 최댓값이면 저장.
				}
			}
			sum += max; //sum 에 최댓값 max 를 계속해서 더해줌
			bottom = top; //top이 그다음 바닥이 됨.
			max = 0; //최댓값 초기화.
		}
		if (result < sum) result = sum; //케이스가 6번 있으니 각 케이스마다 최댓값이 다르니 result 에 저장.
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
