#include <iostream>
#include <queue>	
#include <utility>
#define MAX 500
#define INFINITY 0x7fffffff
using namespace std;
struct node
{
	int first;
	int second;
};
bool operator<(node a,node b)
{
	return a.first > b.first;
}
node make_pair(int f,int s)
{
	node tmp;
	tmp.first = f;
	tmp.second = s;
	return tmp;
}
node Dij(int edge[MAX][MAX],int vetex[MAX],int n,int s,int e)
{
	int* d = new int[n];
	int* count = new int[n];
	bool* visited = new bool[n];
	int* total = new int[n];
	for(int i = 0;i < n;++ i)
	{
		d[i] = INFINITY;
		visited[i] = false;
		count[i] = 0;
		total[i] = 0;
	}
	d[s] = 0;
	count[s] = 1;
	total[s] = vetex[s];
	priority_queue<node> q;
	q.push(make_pair(d[s],s));	
	while(!q.empty())
	{
		node tmp = q.top();	
		q.pop();
		int u = tmp.second;
		if(visited[u])
			continue;
		visited[u] = true;
		for(int i = 0;i < n;++ i)
		{
			if(INFINITY == edge[u][i] || u == i)
				continue;
			if(d[u] + edge[u][i] < d[i])
			{
				d[i] = d[u] + edge[u][i];
				q.push(make_pair(d[i],i));
				count[i] = count[u];
				total[i] = total[u] + vetex[i];
			}
			else if(d[u] + edge[u][i] == d[i])
			{
				if(total[i] < total[u] + vetex[i])
					total[i] = total[u] + vetex[i];
				count[i] += count[u];
			}
		}
	}
	node p = make_pair(count[e],total[e]);
	delete[] d;
	delete[] count;
	delete[] total;
	delete[] visited;
	return p;
}
int main()
{
//	freopen("test.txt","r",stdin);
	int edge[MAX][MAX];
	int vetex[MAX];
	int n,m,c1,c2;
	cin >> n >> m >> c1 >> c2;
	for(int i = 0;i < n;++ i)
		for(int j = 0;j < n;++ j)
			if(i != j)
				edge[i][j] = INFINITY;
			else
				edge[i][j] = 0;
	for (int i = 0;i < n;++ i)
		cin >> vetex[i];
	for (int i = 0;i < m;++ i)
	{
		int t1,t2,dis;
		cin >> t1 >> t2 >> dis;
		edge[t1][t2] = dis;
		edge[t2][t1] = dis;
	}
	node result = Dij(edge,vetex,n,c1,c2);
	cout << result.first << " " << result.second;
}
