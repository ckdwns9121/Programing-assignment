#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <fstream>
#pragma warning(disable:4996)
using namespace std;

vector<int> parent;
vector<int> child;

int check_Tree() {
	int root[2] = { 0, };
	int index = 0;
	sort(child.begin(), child.end());
	sort(parent.begin(), parent.end());
	child.push_back(0);
	parent.push_back(0);
	for (int i = 0; i < child.size() - 1; i++)
		if (child[i] == child[i + 1]) return -1; //자식이 같으면 사이클 
	for (int i = 0; i < parent.size() - 1; i++) {
		if (parent[i] == parent[i + 1]) continue; //비교한거 비교해줄 필요 없음.
		if (!binary_search(child.begin(), child.end() - 1, parent[i])) { //자식과 부모중 같은놈이 없으면
			root[index++] = parent[i];
		}
	}
	if (root[0] == 0) return -1;
	else if (root[1] != 0) return -1;
	else return root[0];
}

int main() {
	ifstream input_fp("tree.inp");
	ofstream output_fp("tree.out");
	unsigned int u, v;
	int count = 1, size = 0;
	int root = 0;
	while (1) {
		while (1) {
			input_fp >> u >> v;
			if (u == -1 && v == -1) return 0;
			else if (u == 0 && v == 0) break;
			else {
				parent.push_back(u);
				child.push_back(v);
			}
		}
		output_fp << "Test Case " << count++ << ": " << check_Tree() << endl;
		child.clear(); parent.clear();
	}
	input_fp.close();
	output_fp.close();
	return 0;
}
