#include <stdio.h>
#pragma warning(disable:4996)

int N, M;

int Visted(int type, int s, int k) {
	int a = 0, b = 0;
	int count = 0, result = 0, vector;
	//result = 현재위치 , vector = 방향.
	if (type == 3) {
		if (s == 1) {
			int x = M, y = N - 1, vector = 0;
			while (1) {
				if (vector == 0) {
					if (k - x > 0) {
						result += x;
						k = k - x;
						vector = 1;
						x--;
					}
					else {
						result += k;
						break;
					}
				}
				else if (vector == 1) {
					if (k - y > 0) {
						result += M * y;
						k = k - y;
						vector = 2;
						y--;
					}
					else {
						result += k * M;
						break;
					}
				}
				else if (vector == 2) {
					if (k - x > 0) {
						result -= x;
						k = k - x;
						vector = 3;
						x--;
					}
					else {
						result -= k;
						break;
					}
				}
				else if (vector == 3) {
					if (k - y > 0) {
						result -= M * y;
						k = k - y;
						vector = 0;
						y--;

					}
					else {
						result -= M * k;
						break;
					}
				}
			}
			return result;
		}
		else if (s == 2) {
			int x = M - 1, y = N, vector = 1;
			while (1) {
				if (vector == 1) {
					if (k - y > 0) {
						result += M * y;
						k = k - y;
						vector = 2;
						y--;
					}
					else {
						result += k * M;
						break;
					}
				}
				else if (vector == 2) {
					if (k - x > 0) {
						result -= x;
						k = k - x;
						vector = 3;
						x--;
					}
					else {
						result -= k;
						break;
					}
				}
				else if (vector == 3) {
					if (k - y > 0) {
						result -= M * y;
						k = k - y;
						vector = 0;
						y--;
					}
					else {
						result -= M * k;
						break;
					}
				}
				else if (vector == 0) {
					if (k - x > 0) {
						result += x;
						k = k - x;
						vector = 1;
						x--;
					}
					else {
						result += k;
						break;
					}
				}
			}
			return result;
		}
		else if (s == 3) {
			int x = M, y = N - 1, vector = 2, result = (N * M) + 1;
			while (1) {
				if (vector == 1) {
					if (k - y > 0) {
						result += M * y;
						k = k - y;
						vector = 2;
						y--;
					}
					else {
						result += k * M;
						break;
					}
				}
				else if (vector == 2) {
					if (k - x > 0) {
						result -= x;
						k = k - x;
						vector = 3;
						x--;
					}
					else {
						result -= k;
						break;
					}
				}
				else if (vector == 3) {
					if (k - y > 0) {
						result -= M * y;
						k = k - y;
						vector = 0;
						y--;
					}
					else {
						result -= M * k;
						break;
					}
				}
				else if (vector == 0) {
					if (k - x > 0) {
						result += x;
						k = k - x;
						vector = 1;
						x--;
					}
					else {
						result += k;
						break;
					}
				}
			}
			return result;
		}
		else if (s == 4) {
			int x = M - 1, y = N, vector = 3, result = (N * M) + 1;
			while (1) {
				if (vector == 1) {
					if (k - y > 0) {
						result += M * y;
						k = k - y;
						vector = 2;
						y--;
					}
					else {
						result += k * M;
						break;
					}
				}
				else if (vector == 2) {
					if (k - x > 0) {
						result -= x;
						k = k - x;
						vector = 3;
						x--;
					}
					else {
						result -= k;
						break;
					}
				}
				else if (vector == 3) {
					if (k - y > 0) {
						result -= M * y;
						k = k - y;
						vector = 0;
						y--;
					}
					else {
						result -= M * k;
						break;
					}
				}
				else if (vector == 0) {
					if (k - x > 0) {
						result += x;
						k = k - x;
						vector = 1;
						x--;
					}
					else {
						result += k;
						break;
					}
				}
			}
			return result;
		}
	}
	else {
		if (s == 1) {
			int x = M - 1, y = N, vector = 1, result = -(M - 1);
			while (1) {
				if (vector == 0) {
					if (k - x > 0) {
						result += x;
						k = k - x;
						vector = 3;
						x--;
					}
					else {
						result += k;
						break;
					}
				}
				else if (vector == 1) {
					if (k - y > 0) {
						result += M * y;
						k = k - y;
						vector = 0;
						y--;
					}
					else {
						result += k * M;
						break;
					}
				}
				else if (vector == 2) {
					if (k - x > 0) {
						result -= x;
						k = k - x;
						vector = 1;
						x--;
					}
					else {
						result -= k;
						break;
					}
				}
				else if (vector == 3) {
					if (k - y > 0) {
						result -= M * y;
						k = k - y;
						vector = 2;
						y--;

					}
					else {
						result -= M * k;
						break;
					}
				}
			}
			return result;
		}
		else if (s == 2) {
			int x = M, y = N - 1, vector = 2, result = M + 1;
			while (1) {
				if (vector == 0) {
					if (k - x > 0) {
						result += x;
						k = k - x;
						vector = 3;
						x--;
					}
					else {
						result += k;
						break;
					}
				}
				else if (vector == 1) {
					if (k - y > 0) {
						result += M * y;
						k = k - y;
						vector = 0;
						y--;
					}
					else {
						result += k * M;
						break;
					}
				}
				else if (vector == 2) {
					if (k - x > 0) {
						result -= x;
						k = k - x;
						vector = 1;
						x--;
					}
					else {
						result -= k;
						break;
					}
				}
				else if (vector == 3) {
					if (k - y > 0) {
						result -= M * y;
						k = k - y;
						vector = 2;
						y--;

					}
					else {
						result -= M * k;
						break;
					}
				}
			}
			return result;
		}
		else if (s == 3) {
			int x = M - 1, y = N, vector = 3, result = (N + 1) * M;
			while (1) {
				if (vector == 0) {
					if (k - x > 0) {
						result += x;
						k = k - x;
						vector = 3;
						x--;
					}
					else {
						result += k;
						break;
					}
				}
				else if (vector == 1) {
					if (k - y > 0) {
						result += M * y;
						k = k - y;
						vector = 0;
						y--;
					}
					else {
						result += k * M;
						break;
					}
				}
				else if (vector == 2) {
					if (k - x > 0) {
						result -= x;
						k = k - x;
						vector = 1;
						x--;
					}
					else {
						result -= k;
						break;
					}
				}
				else if (vector == 3) {
					if (k - y > 0) {
						result -= M * y;
						k = k - y;
						vector = 2;
						y--;

					}
					else {
						result -= M * k;
						break;
					}
				}
			}
			return result;
		}
		else if (s == 4) {
			int x = M, y = N - 1, vector = 0, result = (N - 1) * M;
			while (1) {
				if (vector == 0) {
					if (k - x > 0) {
						result += x;
						k = k - x;
						vector = 3;
						x--;
					}
					else {
						result += k;
						break;
					}
				}
				else if (vector == 1) {
					if (k - y > 0) {
						result += M * y;
						k = k - y;
						vector = 0;
						y--;
					}
					else {
						result += k * M;
						break;
					}
				}
				else if (vector == 2) {
					if (k - x > 0) {
						result -= x;
						k = k - x;
						vector = 1;
						x--;
					}
					else {
						result -= k;
						break;
					}
				}
				else if (vector == 3) {
					if (k - y > 0) {
						result -= M * y;
						k = k - y;
						vector = 2;
						y--;
					}
					else {
						result -= M * k;
						break;
					}
				}
			}
			return result;
		}
	}
}

int main() {

	FILE* input_fp = fopen("grid2.inp", "rt");
	FILE* output_fp = fopen("grid2.out", "wt");
	int T = 0; //테스트케이스
	int t, s, k;
	int count = 0;
	N = M = t = s = k = 0;
	//N행M열,t출발타입,s출발점 k이동거리
	char ch; //개행읽을변수

	fscanf(input_fp, "%d", &T);
	fscanf(input_fp, "%c", &ch);
	while (T--) {
		fscanf(input_fp, "%d", &N);
		fscanf(input_fp, "%c", &ch);
		fscanf(input_fp, "%d", &M);
		fscanf(input_fp, "%c", &ch);
		fscanf(input_fp, "%d", &t);
		fscanf(input_fp, "%c", &ch);
		fscanf(input_fp, "%d", &s);
		fscanf(input_fp, "%c", &ch);
		fscanf(input_fp, "%d", &k);
		fscanf(input_fp, "%c", &ch);
		if (ch == '\n') {
			fprintf(output_fp, "%d\n", Visted(t, s, k));
			count++;
		}
	}
	fclose(input_fp);
	fclose(output_fp);
	return 0;
}