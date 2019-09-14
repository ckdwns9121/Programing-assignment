#include <stdio.h>
#include <string.h>
#pragma warning(disable : 4996)

typedef struct Soccer {
	int get_gole = 0, rank = 0, away = 0, victory_Point = 0;
	//get_gole = ���� ,rank= ��ų away= ��������� victory_Point= ����
}Soccer;

Soccer LIS[41]; //����ü �迭

void scoreResult(int a_team, int h_team, int a_Score, int h_Score) {
	LIS[a_team].get_gole += a_Score - h_Score; //away���� ������ away���� - home����
	LIS[h_team].get_gole += h_Score - a_Score; //home���� ������ home���� - away����
	LIS[a_team].away += a_Score; //away ���� ��� �����ֱ�
	if (a_Score > h_Score) LIS[a_team].victory_Point += 3; //away ������ ������ away�� ���� +3
	else if (a_Score < h_Score) LIS[h_team].victory_Point += 3; //home ������ ������ home �� ����+3
	else { //���� ���� ������ ������ �Ѵ� 1����
		LIS[a_team].victory_Point += 1;
		LIS[h_team].victory_Point += 1;
	}
}
void rankResult(int n) {
	for (int i = 1; i <= n; i++) {
		for (int j = i + 1; j <= n; j++) {
			if (LIS[i].victory_Point == LIS[j].victory_Point) { //i���� j���� �� ex( 1���� 2�� )
				if (LIS[i].get_gole > LIS[j].get_gole) LIS[j].rank++; //i���� ������ �� ������ j���� ��ŷ ++
				else if (LIS[i].get_gole < LIS[j].get_gole) LIS[i].rank++; //j���� ������ �� ������ i���� ��ŷ++
				else if (LIS[i].get_gole == LIS[j].get_gole) { //������ away ������
					if (LIS[i].away > LIS[j].away) LIS[j].rank++; //i���� away������ �� ������ j�� rank ++
					else if (LIS[i].away < LIS[j].away) LIS[i].rank++; //j���� away������ �� ������ i�� rank++
				}
			}
			else if (LIS[i].victory_Point > LIS[j].victory_Point)LIS[j].rank++; //i���� ������ ������ j�� rank ++
			else LIS[i].rank++; //�ƴϸ� i�� ++
		}
	}
}
int main() {
	FILE* input_fp = fopen("soccer.inp", "rt");
	FILE* output_fp = fopen("soccer.out", "wt");
	int T, n, k, a_team, h_team, a_Score, h_Score;
	int count = 1;
	char ch;
	fscanf(input_fp, "%d", &T);
	fscanf(input_fp, "%c", &ch);
	while (T--) {
		fscanf(input_fp, "%d %d", &n, &k);
		for (int i = 0; i < (n - 1) * k * n; i++) {
			fscanf(input_fp, "%d %c %d %d %d", &a_team, &ch, &h_team, &a_Score, &h_Score);
			scoreResult(a_team, h_team, a_Score, h_Score);
		}
		rankResult(n);
		fprintf(output_fp, "Test Case #%d: ", count);
		for (int i = 1; i <= n; i++) fprintf(output_fp, "%d ", LIS[i].rank + 1);
		fprintf(output_fp, "\n");
		memset(LIS, 0, sizeof(LIS));
		count++;
	}
	return 0;
}

