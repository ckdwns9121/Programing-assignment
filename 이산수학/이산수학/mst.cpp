#include <fstream>
#include <vector>
#include <algorithm>
#include <queue>
#include <functional>
#pragma warning(disable:4996)
#define A 10001
using namespace std;
ifstream input_fp("mst.inp");
ofstream output_fp("mst.out");
typedef struct pair<int, int> node;
typedef struct Save {
	int vertex, min_Cost;
}Save;
vector<node> graph[A];
Save save[A];
int visit_Array[A];
int index = 0;
int count_Vertex(int n) {
	int count = 0;
	for (int i = 0; i < n; i++) {
		if (visit_Array[i] == 1) {
			count++;
			visit_Array[i] = -1;
		}
	}
	return count;
}
bool compare(Save a, Save b) {
	if (a.vertex == b.vertex) return a.min_Cost < b.min_Cost;
	return a.vertex < b.vertex;
}
void prim(int start, int n) {
	if (visit_Array[start]) return;
	visit_Array[start] = 1;
	int Cost = 0, temp = 0, count = 0;
	priority_queue< node, vector<node>, greater<node> > min_Heap;
	for (int i = 0; i < graph[start].size(); i++) {
		//시작지점의 인접노드들의 정보를 전부 최소힙에 삽입
		int next_Cost = graph[start][i].first;
		int next_node = graph[start][i].second;
		min_Heap.push(node(next_Cost, next_node));
	}
	while (!min_Heap.empty()) {
		int present_Cost = min_Heap.top().first;
		int present = min_Heap.top().second;
		min_Heap.pop();
		if (visit_Array[present])continue;
		visit_Array[present] = 1;
		Cost += present_Cost;
		// 다음 정점을 우선순위 큐에 넣어준다.
		for (int i = 0; i < graph[present].size(); i++) {
			int pre_nextCost = graph[present][i].first;
			int pre_next = graph[present][i].second;
			min_Heap.push(node(pre_nextCost, pre_next));
		}
	}
	save[index].vertex = count_Vertex(n);
	save[index].min_Cost = Cost;
	index++;
}
int main() {
	int n, m;
	input_fp >> n >> m;
	for (int i = 0; i < m; i++) {
		int V1, V2, edge;
		input_fp >> V1 >> V2 >> edge;
		graph[V1].push_back(node(edge, V2));
		graph[V2].push_back(node(edge, V1));
	}
	for (int i = 0; i < n; i++) prim(i, n);
	sort(save, save + index, compare);
	for (int i = 0; i < index; i++)
		output_fp << save[i].vertex << " " << save[i].min_Cost << endl;
	input_fp.close();
	output_fp.close();
	return 0;
}
