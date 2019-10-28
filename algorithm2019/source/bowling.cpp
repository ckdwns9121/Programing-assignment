/**
 * Assignment 01 : Bowling Score
 */

#include <fstream>
#include <vector>
using namespace std;

#define MAX_SCORE 10

typedef struct Bowling {
	int score1 = 0;
	int score2 = 0;
	int bonus = 0; // finish fream's bonus
	int check = 0; //1 strike  2 spare 3 open
}Bowling;

vector<Bowling> v;

int solution() {

	int sum = 0;

	for (int i = 0; i < v.size(); i++) {
		if (v[i].check == 3) { //open
			sum += v[i].score1 + v[i].score2;
		}
		else if (v[i].check == 2) { //spare
			sum += v[i].score1 + v[i].score2 + v[i + 1].score1;
		}
		else if (v[i].check == 1) { //strike 
			if (v[i + 1].score1 == MAX_SCORE && i != 8) {
				sum += v[i].score1 + v[i + 1].score1 + v[i + 2].score1;
			}
			else {
				sum += v[i].score1 + v[i + 1].score1 + v[i + 1].score2;
			}
		}
		else { //bunus
			sum += v[i].score1 + v[i].score2 + v[i].bonus;
		}
	}

	return sum;
}

int main() {

	ifstream input("bowling.inp");
	ofstream output("bowling.out");

	int testcase;
	int score1 = 0;
	int score2 = 0;
	input >> testcase;
	while (testcase--) {

		for (int i = 0; i < MAX_SCORE; i++) {
			Bowling bowling;
			if (i < MAX_SCORE - 1) {
				input >> bowling.score1;
				if (bowling.score1 == MAX_SCORE) { //strike 
					bowling.check = 1;
					v.push_back(bowling);
					continue;
				}
				input >> bowling.score2;
				if (bowling.score1 + bowling.score2 == MAX_SCORE)//spare
					bowling.check = 2; 
				else
					bowling.check = 3;
			}
			else {
				input >> bowling.score1 >> bowling.score2;
				if (bowling.score1 + bowling.score2 >= MAX_SCORE) {
					input >> bowling.bonus;
				}
			}
			v.push_back(bowling);
		}
		output << solution() << endl;
		v.clear();
	}
	input.close();
	output.close();
	return 0;
}