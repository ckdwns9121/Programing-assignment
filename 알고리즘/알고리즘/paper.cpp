#include <fstream>
#include <algorithm>
#include <vector>
#define MAX 4002

using namespace std;

typedef struct Paper {
	int start_x, start_y;
	int end_x, end_y;
	int w, h;
	int area;
}Paper;

typedef struct point {
	int position;
	int index;
}Point;

vector<Paper> p;
vector<Point> x_position;
vector<Point> y_position;

int all_cover = 0;
int partially_cover = 0;
int not_cover = 0;

void resetting_vector();
void compression();

int matrix[MAX][MAX];

/* sorting by position*/
bool compare_Position(const Point& x, const Point& y) {
	return x.position < y.position;
}
/* sorting by matching_index*/
bool compare_Index(const Point& x, const Point& y) {
	if (x.index == y.index) return x.position < y.position;
	return x.index < y.index;
}

void func() {

	for (int i = 0; i < p.size(); i++) {
		int sum = 0;
		for (int x = p[i].start_x; x < p[i].end_x; x++) {
			for (int y = p[i].start_y; y < p[i].end_y; y++) {
				if (matrix[x][y] == i + 1) sum++;
			}
		}

		if (sum == p[i].area) not_cover++;
		else if (sum == 0) all_cover++;
		else partially_cover++;

	}
	return;
}


void paintingMatrix() {

	for (int i = 0; i < p.size(); i++) {
		int area = 0;
		for (int x = p[i].start_x; x < p[i].end_x; x++) {
			for (int y = p[i].start_y; y < p[i].end_y; y++) {
				matrix[x][y] = i + 1;
				area++;
			}
		}
		p[i].area = area;
	}
	return;
}

void resetting_vector() {

	/*sorting by matching_index*/
	sort(x_position.begin(), x_position.end(), compare_Index);
	sort(y_position.begin(), y_position.end(), compare_Index);

	for (int i = 0; i < x_position.size(); i++) {

		int idx = x_position[i].index;

		if (i % 2 == 0) {
			p[idx].start_x = x_position[i].position;
			p[idx].start_y = y_position[i].position;
		}
		else {
			p[idx].end_x = x_position[i].position;
			p[idx].end_y = y_position[i].position;
		}

	}

	for (int i = 0; i < p.size(); i++) {
		p[i].w = p[i].end_x - p[i].start_x;
		p[i].h = p[i].end_y - p[i].start_y;
	}

	return;
}

// point compression 
void compression() {
	int x_temp = 0;
	int y_temp = 0;
	int temp = 0;
	for (int i = 0; i < x_position.size(); i++) {
		int idx = x_position[i].index;
		if (temp == x_position[i].position) {
			x_position[i].position = --x_temp;
			x_temp++;
		}
		else if (x_position[i].position > x_temp) {
			temp = x_position[i].position;
			x_position[i].position = x_temp++;
		}
	}
	temp = 0;
	for (int i = 0; i < y_position.size(); i++) {
		int idx = y_position[i].index;
		if (temp == y_position[i].position) {
			y_position[i].position = --y_temp;
			y_temp++;
		}
		else if (y_position[i].position > y_temp) {
			temp = y_position[i].position;
			y_position[i].position = y_temp++;
		}
	}
	resetting_vector();


}

int main() {
	ifstream input("paper.inp");
	ofstream output("paper.out");
	int t;
	input >> t;
	int index = 0;
	while (t--) {
		Paper paper;
		input >> paper.start_x >> paper.start_y >> paper.w >> paper.h;
		paper.end_x = paper.start_x + paper.w;
		paper.end_y = paper.start_y + paper.h;
		p.push_back(paper);
		x_position.push_back({ paper.start_x,index });
		x_position.push_back({ paper.end_x,index });
		y_position.push_back({ paper.start_y,index });
		y_position.push_back({ paper.end_y, index++ });

	}
	sort(x_position.begin(), x_position.end(), compare_Position);
	sort(y_position.begin(), y_position.end(), compare_Position);
	compression();
	paintingMatrix();
	func();
	output << all_cover << " " << partially_cover << " " << not_cover;
	return 0;
}