#include <iostream>
#include <vector>
#include <map>
#include <queue>
#include <algorithm>
#include <cstdio>
#include <cstdlib>
using namespace std;
int main()
{
	freopen("input.txt","r",stdin);
	int m,n;
	scanf("%d %d",&m,&n);
	int* v = new int[m * n];
	for(int i = 0;i < m * n;++ i)
		scanf("%d",v + i);
	int times(0),res(v[0]);
	for(int i = 0;i < m * n;++ i)
	{
		if (times == 0)
		{
			res = v[i];
			times = 1;
		}
		else
		{
			if (res == v[i])
				++ times;
			else
				-- times;
		}
	}
	cout << res;
	delete[] v;
}
