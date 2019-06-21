#include <stdio.h>
#include <string.h>
#pragma warning(disable : 4996)

typedef struct Soccer {
	int get_gole = 0, rank = 0, away = 0, victory_Point = 0;
	//get_gole = ∞ÒµÊΩ« ,rank= ∑©≈≥ away= æÓø˛¿Ã¡°ºˆ victory_Point= Ω¬¡°
}Soccer;

Soccer LIS[41]; //±∏¡∂√º πËø≠

void scoreResult(int a_team, int h_team, int a_Score, int h_Score) {
	LIS[a_team].get_gole += a_Score - h_Score; //away∆¿¿« ∞ÒµÊΩ«¿∫ away¡°ºˆ - home¡°ºˆ
	LIS[h_team].get_gole += h_Score - a_Score; //home∆¿¿« ∞ÒµÊΩ«¿∫ home¡°ºˆ - away¡°ºˆ
	LIS[a_team].away += a_Score; //away ¡°ºˆ ∞Ëº” ¥ı«ÿ¡÷±‚
	if (a_Score > h_Score) LIS[a_team].victory_Point += 3; //away ¡°ºˆ∞° ≥Ù¿∏∏È away∆¿ Ω¬¡° +3
	else if (a_Score < h_Score) LIS[h_team].victory_Point += 3; //home ¡°ºˆ∞° ≥Ù¿∏∏È home ∆¿ Ω¬¡°+3
	else { //∏∏æ‡ µŒ∆¿ ¡°ºˆ∞° ∞∞¿∏∏È µ—¥Ÿ 1¡°æø
		LIS[a_team].victory_Point += 1;
		LIS[h_team].victory_Point += 1;
	}
}
void rankResult(int n) {
	for (int i = 1; i <= n; i++) {
		for (int j = i + 1; j <= n; j++) {
			if (LIS[i].victory_Point == LIS[j].victory_Point) { //i∆¿∞˙ j∆¿¿ª ∫Ò±≥ ex( 1∆¿∞˙ 2∆¿ )
				if (LIS[i].get_gole > LIS[j].get_gole) LIS[j].rank++; //i∆¿¿« ∞ÒµÊΩ«¿Ã ¥ı ≥Ù¿∏∏È j∆¿¿« ∑©≈∑ ++
				else if (LIS[i].get_gole < LIS[j].get_gole) LIS[i].rank++; //j∆¿¿« ∞ÒµÊΩ«¿Ã ¥ı ≥Ù¿∏∏È i∆¿¿« ∑©≈∑++
				else if (LIS[i].get_gole == LIS[j].get_gole) { //∞∞¿∏∏È away ¡°ºˆ∫Ò±≥
					if (LIS[i].away > LIS[j].away) LIS[j].rank++; //i∆¿¿« away¡°ºˆ∞° ¥ı ≥Ù¿∏∏È j∆¿ rank ++
					else if (LIS[i].away < LIS[j].away) LIS[i].rank++; //j∆¿¿« away¡°ºˆ∞° ¥ı ≥Ù¿∏∏È i∆¿ rank++
				}
			}
			else if (LIS[i].victory_Point > LIS[j].victory_Point)LIS[j].rank++; //i∆¿¿Ã ¡°ºˆ∞° ≥Ù¿∏∏È j∆¿ rank ++
			else LIS[i].rank++; //æ∆¥œ∏È i∆¿ ++
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

