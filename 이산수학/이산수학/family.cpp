#include <iostream>
#include <fstream>
#include <cstdio>
#include <string.h>
#include <vector>
#include <algorithm>
#include <stack>
#pragma warning(disable:4996)
using namespace std;
#define A 500000

vector< vector <int> > family(A);
int visit_Array[A];
unsigned int indgree[A];
unsigned int outdgree[A];
int parent, child;
int maxsize = 0;

int dfs(int start) {

	stack<int>s;
	s.push(start);
	visit_Array[start] = 1;
	int stack_size = 0;
	while (!s.empty()) {
		int x = s.top();
		s.pop();
		for (int i = 0; i < family[x].size(); i++) {
			int next_node = family[x][i];
			if (visit_Array[next_node] == 0) {
				visit_Array[next_node] = 1;
				s.push(x);
				s.push(next_node);
				break;
			}
			else if (visit_Array[next_node] == 1) {
				stack_size = s.size();
				if (maxsize < stack_size) maxsize = stack_size;
			}
		}
	}
	return maxsize;
}

int find_root(int N) {
	int root = 0;
	for (int i = 1; i < N + 1; i++) {
		if (indgree[i] == 0 && outdgree[i] != 0) {
			root = i;
			return root;
		}
	}
}
int main() {
	ifstream input_fp("family.inp");
	ofstream output_fp("family.out");
	int testCase, N;
	int root = 0;
	input_fp >> testCase;
	while (testCase--) {
		input_fp >> N;
		for (int i = 1; i < N; i++) {
			input_fp >> parent >> child;
			family[parent].push_back(child);
			family[child].push_back(parent);
			indgree[child]++; outdgree[parent]++;
		}
		root = find_root(N);
		for (int i = 0; i < N; i++) sort(family[i].begin(), family[i].end());
		maxsize = dfs(root);
		output_fp << maxsize + 1 << endl;
		maxsize = 0; root = 0;
		family.clear();
		family.resize(A);
		memset(indgree, 0, sizeof(indgree));
		memset(outdgree, 0, sizeof(outdgree));
		memset(visit_Array, 0, sizeof(visit_Array));
	}
	input_fp.close();
	output_fp.close();
	return 0;
}