/**
 * Assignment 09 : Ladder
 */


#include <fstream>
#include <vector>
#include <algorithm>
using namespace std;

typedef struct Ladder {
	int x1,y1;
	int x2,y2;
}Ladder;

typedef struct Position {
	int point, ladder_num, y;
}Position;

vector < vector<Position >> list;
vector <int >result;
int t;

bool compare(const Position& a,const Position& b) {
	return	a.point > b.point;
}


void research(int start) {
	int ladder, position;
	int index = 0;
	ladder = list[start][index].ladder_num;
	position = list[start][index].y; 
	while (true) {
		for (int i = 0; i < list[ladder].size(); i++) {
			int temp = ladder;
			if (list[ladder][i].point == position) {
				ladder = list[temp][i + 1].ladder_num;
				position = list[temp][i + 1].y;
				if (ladder == -1 && position == -1) {
					result[temp] = start;
					return;
				}
				break;
			}
		}
	}
}
int main() {
	ifstream input("ladder.inp");
	ofstream output("ladder.out");
	int index = 0;
	input >> t;
	list.resize(t);
	result.resize(t);
	while (true){
		Ladder ladder;
		input >> ladder.x1 >> ladder.y1 >> ladder.x2 >> ladder.y2;
		if (!ladder.x1 && !ladder.x2 && !ladder.y1 && !ladder.y2) break;
		else {
			list[ladder.x1].push_back({ ladder.y1,ladder.x2, ladder.y2 });
			list[ladder.x2].push_back({ ladder.y2,ladder.x1,ladder.y1 });
			index++;
		}
	}
	for (int i = 0; i < t; i++) {
		sort(list[i].begin(), list[i].end(), compare);
		list[i].push_back({ -1,-1,-1 });
	}
	for (int i = 0; i < t; i++)
		research(i);
	
	for (int i = 0; i < t; i++)
		output << result[i]<<" ";
	


	return 0;
}