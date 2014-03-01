#include <cstring>
#include <cstdio>
#include <cstdlib>
#include <cassert>
#include <queue>
using namespace std;
#define MAX 10001
struct Node
{
	int v;
	Node* pre;
	Node* next;
	Node()
	{
		v = -1;
		pre = NULL;
		next = NULL;
	}
	Node(int x)
	{
		v = x;
		pre = NULL;
		next = NULL;
	}
};
struct List
{
	Node* head;
	Node* tail;
	List()
	{
		head = new Node();
		tail = head;
	}
	void push(int x)
	{
		Node* node = new Node(x);
		node->pre = tail;
		tail->next = node;
		tail = tail->next;
	}
	~List()
	{
		Node* t = head;
		while(t != NULL)
		{
			Node* t2 = t->next;
			delete t;
			t = t2;
		}
		head = NULL;
		tail = NULL;
	}
};
struct Edge
{
	int a,b;
}edge[MAX];
int BFS_Search(List* g,int n,int root)
{
	queue<int> q;
	q.push(root);
	bool visited[MAX];
	int depth[MAX];
	memset(visited,false,sizeof(visited));
	depth[root] = 0;
	visited[root] = true;
	int count(1);
	while(!q.empty())
	{
		int v = q.front();
		q.pop();
		for(Node* index = g[v].head->next;index != NULL;index = index->next)
		{
			if(visited[index->v])
				continue;
			++ count;
			depth[index->v] = depth[v] + 1;
			q.push(index->v);
			visited[index->v] = true;
		}
		if(n == count)
			break;
	}
	int max(-1);
	for(int i = 1;i <= n;++ i)
	{
		if(depth[i] > max)
			max = depth[i];
	}
	return max;
}
int findcate(int k,int* belong)
{
	int t = k;
	while(k != belong[k])
		k = belong[k];
	belong[t] = k;
	return k;
}
void union_vetex(int a,int b,int* belong)
{
	int fa = findcate(a,belong);
	int fb = findcate(b,belong);
	if(fa < fb)
		belong[b] = fa;
	else
		belong[a] = fb;
}
int comp(const void* a,const void* b)
{
	return *(int*)a - *(int*)b;
}
int main()
{
	int n;
	scanf("%d",&n);
	List g[MAX];
	int degree[MAX];
	int belong[MAX];
	memset(degree,0,sizeof(degree));
	for(int i = 0;i < n - 1;++ i)
	{
		int a,b;
		scanf("%d %d",&a,&b);
		g[a].push(b);
		g[b].push(a);
		++ degree[a];
		++ degree[b];
		edge[i].a = a;
		edge[i].b = b;
	}
	for(int i = 1;i <= n;++ i)
		belong[i] = i;
	for(int i = 0;i < n - 1;++ i)
		union_vetex(edge[i].a,edge[i].b,belong);
	qsort(belong,n,sizeof(int),comp);
	int componts(1);
	int tmp_cate = belong[1];
	for(int i = 2;i <= n;++ i)
	{
		if(belong[i] != tmp_cate)
		{
			tmp_cate = belong[i];
			++ componts;
		}
	}
	if(componts > 1)
	{
		printf("Error: %d components",componts);
	}
	else
	{
		int depth;
		int max = -1;
		int final_depth[MAX];
		memset(final_depth,0,sizeof(final_depth));
		for(int root = 1;root <= n;++ root)
		{
			if(degree[root] > 1)
				continue;
			else
			{
				depth = BFS_Search(g,n,root);
				final_depth[root] = depth;
				if(depth > max)
					max = depth;
			}
		}
		for(int i = 1;i <= n;++ i)
			if(max == final_depth[i])
				printf("%d\n",i);
	}
}