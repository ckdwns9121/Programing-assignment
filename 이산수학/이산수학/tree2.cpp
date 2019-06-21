#include <fstream>
#include <vector>
#pragma warning(disable:4996)

using namespace std;
typedef struct Node {
	int vertex;
	int edge;
	int max;
}Node;

vector<vector<Node> > tree;
int max_weight, result;

int max_Length(int start, int weight) {
	int max_len, W = 0;
	if (tree[start].size() != 0) {
		for (int i = 0; i < tree[start].size(); i++) {
			int child_node = tree[start][i].vertex;
			if (child_node == 0) continue;
			max_len = max_Length(child_node, weight + tree[start][i].edge);
			if (max_len > W) W = max_len;
			if (tree[start][i].max < max_len) tree[start][i].max = max_len;
		}
		return W;
	}
	return weight; //자식 없을시 그냥 가중치값 리턴
}
void Update(int start, int weight) {
	if (tree[start].size() != 0) {
		for (int i = 0; i < tree[start].size(); i++) {
			int child_node = tree[start][i].vertex;
			if (child_node == 0) continue;
			result += weight - tree[start][i].max;
			Update(child_node, tree[start][i].max);
		}
	}
	return;
}
int main() {
	ifstream input_fp("tree2.inp");
	ofstream output_fp("tree2.out");
	int T, n;
	input_fp >> T;
	while (T--) {
		input_fp >> n;
		tree.resize(n);
		tree[0].push_back({ 0,0,0, });
		for (int u = 1; u < n; u++) {
			Node node;
			input_fp >> node.vertex >> node.edge;
			tree[node.vertex].push_back({ u, node.edge, 0 });
		}
		max_weight = max_Length(0, 0);
		tree[0][0].max = max_weight;
		Update(0, max_weight);
		output_fp << result << endl;
		tree.clear();
		result = 0;
		max_weight = 0;
	}
	input_fp.close();
	output_fp.close();
	return 0;

}