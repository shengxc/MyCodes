#include<iostream>
#include <string>
#include <iomanip>
#include <vector>
#include <algorithm>
using namespace std;
const int WHITE = 0;
const int GRAY = 1;
const int BLACK = 2;
void DFS_VISIT(const vector< vector<int> >& G,int u,vector<int>& color,vector<int>& f,int& time)
{
	color[u] = GRAY;
	time ++;
	for (int i = 0;i < G.size();++i)
		if (1 == G[u][i] && WHITE == color[i])
			DFS_VISIT(G,i,color,f,time);
	color[u] = BLACK;
	time ++;
	f[u] = time;
}
int DFS(const vector< vector<int> >& G,vector<int>& order,vector<int>& f) //对于图G以order数组的顺序进行深度优先搜索，返回每个顶点的finish time存入f
{																		 
	int count = 0;
	vector<int> color(G.size(),WHITE);
	if (0 == order.size())
		for(int i = 0;i < G.size();++ i)
			order.push_back(i);
	if (0 == f.size())
		for(int i = 0;i < G.size();++i)
			f.push_back(0);
	int t = 0;
	for (int i = 0;i < order.size();++ i)
		if(WHITE == color[order[i]])
		{
			count ++;
			DFS_VISIT(G,order[i],color,f,t);
		}
	return count;
}
int strongly_connected_components(const vector< vector<int> >& G)
{
	vector<int> order,f;
	DFS(G,order,f);
	vector<int> b,e;
	sort(f.begin(),f.end());
	reverse(f.begin(),f.end());
	return DFS(G,order,f);
}
int main()
{
	int n,m,k;
	int a,b,concern;
	cin >> n >> m >> k;
	vector<int> init_temp(n,0);
	vector< vector<int> > init_graph(n,init_temp);
	for (int i = 0;i < m;++ i)
	{
		cin >> a >> b;
		init_graph[a - 1][b - 1] = 1;
		init_graph[b - 1][a - 1] = 1;
	}
	//初始图构造完成
	for(int i = 0;i < k;++ i)
	{
		vector< vector<int> > concern_graph(init_graph);
		cin >> concern;
		concern --;
		for(int j = 0;j < n;++j)   //删除关心的节点
		{
			concern_graph[concern][j] = 0;
			concern_graph[j][concern] = 0;
		}
		int result = strongly_connected_components(concern_graph);
		cout << result - 2 << endl;
	}

}