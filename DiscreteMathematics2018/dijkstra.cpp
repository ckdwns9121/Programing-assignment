#include <iostream>
#include <vector>
#include <queue>
#include <fstream>
#include <algorithm>
#define INF 2147483647
using namespace std;

ifstream fcin("dijkstra.inp");
ofstream fcout("dijkstra.out");

int N, M;
int u, v, w;
struct inf {
	int prev, v, w, n;
};
vector<vector<inf> > vec;
vector<int> prev_vertex;
vector<vector<int> > ans;
bool operator<(inf A, inf B) { return (A.w == B.w ? A.n < B.n : A.w > B.w); }

void tracking(int n, int ans_n)
{
	if (prev_vertex[n] == -INF) // dist = INF
	{
		ans[ans_n].push_back(0);
		return;
	}
	if (prev_vertex[n] == -1)
		return;
	if (ans[prev_vertex[n]].size() > 0)
	{
		for (int i = 0; i < ans[prev_vertex[n]].size(); i++)
			ans[ans_n].push_back(ans[prev_vertex[n]][i]);
		return;
	}
	ans[ans_n].push_back(prev_vertex[n]);
	return tracking(prev_vertex[n], ans_n);
}
void dijkstra()
{
	vector<int> dist(N, INF);
	vector<int> visited(N);
	vector<int> prev_edge_number(N, -INF);
	prev_vertex.resize(N, -INF);
	ans.resize(N);

	dist[0] = 0;
	prev_vertex[0] = -1;
	priority_queue<inf> pq; // using dijkstra
	pq.push({ -1,0,0,-1 });

	while (!pq.empty())
	{
		int prev = pq.top().prev;
		int cur = pq.top().v;
		int w = pq.top().w;
		int n = pq.top().n;
		pq.pop();

		if (dist[cur] == w && prev_edge_number[cur] < n)
		{
			prev_edge_number[cur] = n;
			prev_vertex[cur] = prev;
		}
		if (visited[cur]) continue;
		visited[cur] = 1;

		for (int i = 0; i < vec[cur].size(); i++)
		{
			int next = vec[cur][i].v;
			if (dist[next] >= vec[cur][i].w + dist[cur])
			{
				dist[next] = vec[cur][i].w + dist[cur];
				pq.push({ cur, next, dist[next], vec[cur][i].n });
			}
		}
	}
	for (int i = 1; i < N; i++)
	{
		ans[i].push_back(i);
		tracking(i, i);
		for (int j = ans[i].size() - 1; j >= 0; j--)
			fcout << "V" << ans[i][j] << " ";
		fcout << "(" << (dist[i] == INF ? -1 : dist[i]) << ")\n";
	}
}
int main()
{
	fcin >> N >> M;
	vec.resize(N);

	for (int i = 0; i < M; i++)
	{
		fcin >> u >> v >> w;
		vec[u].push_back({ u,v,w,i });
	}
	dijkstra();
}