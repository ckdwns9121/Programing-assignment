#include <iostream>
#include <vector>
#include <fstream>
#include <queue>
#include <algorithm>
#pragma warning(disable:4996)
using namespace std;
#define A 10001

int BFS_weight, DFS_weight;
vector< vector <int> > tree;
int matrix[A][A];
int visit_Array[A];

void dfs(int start) {
	if (visit_Array[start] == 1)return; //방문했을시 return
	visit_Array[start] = 1; //방문안했으면 1
	for (int i = 0; i < tree[start].size(); i++) {
		int x = tree[start][i];
		if (!visit_Array[x]) {
			DFS_weight += matrix[start][x];
			dfs(x);
		}
	}
}
void bfs(int start) {

	if (visit_Array[start] == 1) return; //방문시 return;
	queue<int> q;
	visit_Array[start] = 1;
	q.push(start);

	while (!q.empty()) {
		int x = q.front();
		q.pop();
		for (int i = 0; i < tree[x].size(); i++) {
			int next_node = tree[x][i];
			if (!visit_Array[next_node] && matrix[next_node][x] != 0) {//방문하지않았으면
				//printf("BFS: %d 에서 %d로 이동\n", start, y);
				BFS_weight += matrix[next_node][x];
				visit_Array[next_node] = 1;
				q.push(next_node);
			}
		}
	}
}

int main() {
	ifstream input_fp("cycle.inp");
	ofstream output_fp("cycle.out");
	int testCase, n, m, u, v, w, k, start_point;
	input_fp >> testCase;
	while (testCase--) {
		input_fp >> n >> m;
		tree.resize(n);
		for (int i = 0; i < m; i++) {
			input_fp >> u >> v >> w;
			matrix[u][v] = w; //가중치설정
			matrix[v][u] = w; //가중치설정
			tree[u].push_back(v); //정점연결 
			tree[v].push_back(u); //정점연결
		}
		//오름차순으로 sorting
		for (int i = 0; i < n; i++) sort(tree[i].begin(), tree[i].end());
		input_fp >> k;
		for (int i = 0; i < k; i++) {
			input_fp >> start_point;
			//시작지점 받고 dfs bfs수행
			dfs(start_point);
			memset(visit_Array, 0, sizeof(visit_Array));
			bfs(start_point);
			memset(visit_Array, 0, sizeof(visit_Array));
			//printf("n=%d m=%d start=%d DFS:%d BFS:%d\n", n, m, start, DFS_weight, BFS_weight);
			output_fp << "n=" << n << " m=" << m << " start=" << start_point << " DFS:" << DFS_weight << " BFS:" << BFS_weight << endl;
			DFS_weight = 0; BFS_weight = 0;
		}
		tree.clear();
	}
	input_fp.close();
	output_fp.close();
	return 0;
}