#include <fstream>
#include <vector>
#include <queue>
#include <cstring>
#pragma warning(disable:4996)
using namespace std;

#define A 1000000
vector< vector <int > > tree;
int color_Array[A];

bool odd_Cyclecheck() {

	memset(color_Array, -1, sizeof(color_Array));
	int start = 0;
	color_Array[start] = 1;
	queue <int> q;
	q.push(start);
	while (!q.empty()) {
		int u = q.front();
		q.pop();
		for (int i = 0; i < tree[u].size(); i++) {
			int next_node = tree[u][i];
			if (color_Array[next_node] == -1) {
				color_Array[next_node] = !color_Array[u];
				q.push(next_node);
			}
			else if (color_Array[next_node] == color_Array[u])
				return true;
		}
	}
	return false;
}

int main() {
	ifstream input_fp("mst.inp");
	ofstream output_fp("mst.out");
	int testCase, n, m, u, v;
	input_fp >> testCase;
	while (testCase--) {
		input_fp >> n >> m;
		tree.resize(n);
		for (int i = 0; i < m; i++) {
			input_fp >> u >> v;
			tree[u].push_back(v);
			tree[v].push_back(u);
		}
		odd_Cyclecheck() ? output_fp << "O\n" : output_fp << "X\n";
		tree.clear();
	}
	return 0;
}