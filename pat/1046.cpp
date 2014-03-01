#include <iostream>
#include <vector>
using namespace std;
inline int getdist(const int* const dist,int a,int b,int size)
{
	int res(0);
	for(int i = a;i != b;i = (i + 1) % size)
		res += dist[i];
	return res;
}
int main()
{
	freopen("input.txt","r",stdin);
	int n;
	scanf("%d",&n);
	int* distance = new int[n];
	int* innerdist = new int[n + 1];
	innerdist[0] = 0;
	int total(0);
	for(int i = 0;i < n;++ i)
		scanf("%d",distance + i);
	for(int i = 0;i < n;++ i)
	{
		total += distance[i];
		innerdist[i + 1] = total;
	}
	int k;
	scanf("%d",&k);
	for (int i = 0;i < k;++ i)
	{
		int x,y;
		scanf("%d %d",&x,&y);
		--x,--y;
		int max = x > y ? x : y;
		int min = x > y ? y : x;
		int a = innerdist[max] - innerdist[min];
		int b = total - a;
		int res = a < b ? a : b;
		cout << res << "\n";
	}
	delete[] distance;
}