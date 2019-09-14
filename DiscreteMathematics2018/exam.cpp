#include <iostream>
#include <cstdio>
#include <string>
#include <string.h>
#include <fstream>
using namespace std;
#pragma warning(disable:4996)

char Good_word[27]; //좋은문자 집합
char P_word[1001]; //패턴
char Q_word[1001]; //Q

int func(int P_size, int Q_size, int G_size) {
	int index = 0; // ? 위치 탐색 인덱스
	int star_count = 0; //별에있는 문자열중 좋은 문자 갯수 새는 변수
	int check = 0;
	int i = 0;
	int last_check;
	for (i = 0; i < P_size; i++) {
		if (P_word[i] == '?') {
			int count = 0; //좋은문자 배열 끝까지 갔는지 카운트
			for (int j = 0; j < G_size; j++, count++) {
				if (Q_word[index] == Good_word[j]) {
					index++;
					break;
				}
			}
			if (count == G_size) check = 1; //끝까지 돌았으면 NO
		}
		else if (P_word[i] == '*') {
			int star_size = Q_size - P_size;
			if (star_size >= 0) {  // !empty string 
				//int j = 0;
				for (int j = index; j <= (index + star_size); j++) {
					for (int k = 0; k < G_size; k++) {
						if (Q_word[j] == Good_word[k]) {
							star_count++;
						}
					}
				}
				if (star_count - 1 == star_size) check = 1; //*의 문자열이 전부 좋은문자집합일때
				else {
					index += star_size + 1;
				}
			}
		}
		else if (P_word[i] == Q_word[index]) index++; //자리수에있는 값이 같으면 옆으로 인덱스 옮김
		else if (P_word[i] != Q_word[index]) check = 1; //다르면 만들수 없는 문자이므로 check = 1;
		// fasle 면 판별할 필요 없으니  바로break
		if (check == 1) break;
	}
	if ((i == P_size) && (Q_word[index] == NULL)) last_check = 1;
	else if (check == 1)last_check = 0;
	return last_check;
}
int main() {
	ifstream input_fp("exam.inp");
	ofstream output_fp("exam.out");
	int last_check;
	int count = 1;
	int testCase, num;
	input_fp >> testCase;
	while (testCase--) {
		string goodWord, P, Q;
		output_fp << "Test Case: #" << count << endl;
		input_fp >> goodWord;
		for (int i = 0; i < goodWord.size(); i++)Good_word[i] = goodWord[i];
		input_fp >> P;
		for (int i = 0; i < P.size(); i++) P_word[i] = P[i];
		input_fp >> num;
		for (int i = 0; i < num; i++) {
			input_fp >> Q;
			for (int j = 0; j < Q.size(); j++) {
				Q_word[j] = Q[j];
			}
			last_check = func(P.size(), Q.size(), goodWord.size());
			if (last_check == 1) output_fp << "Yes" << endl;
			else output_fp << "No" << endl;
			memset(Q_word, 0, sizeof(Q_word));
		}
		count++;
		memset(Good_word, 0, sizeof(Good_word));
		memset(P_word, 0, sizeof(P_word));
	}

	input_fp.close();
	output_fp.close();
	return 0;
}
