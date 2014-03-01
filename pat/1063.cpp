#include <iostream>
#include <vector>
#include <hash_set>//linux下略有变化
using namespace std;
int main()
{
	freopen("input.txt","r",stdin);
	int n;
	cin >> n;
	vector<hash_set<int> > sets;
	for (int i = 0;i < n;++ i)
	{
		sets.push_back(hash_set<int>());
		int m;
		cin >> m;
		for (int j = 0;j < m;++ j)
		{
			int x;
			cin >> x;
			sets[i].insert(x);
		}
	}
	int k;
	cin >> k;
	for (int i = 0;i < k;++ i)
	{
		int intersectionsize(0);
		int unionsize;
		int a,b;
		cin >> a >> b;
		--a,--b;
		if (sets[a].size() > sets[b].size())
		{
			unionsize = sets[a].size();
			for(hash_set<int>::const_iterator it = sets[b].begin();it != sets[b].end();++ it)
			{
				if(sets[a].find(*it) != sets[a].end())
					++ intersectionsize;
				else
					++ unionsize;
			}
		}
		else
		{
			unionsize = sets[b].size();
			for(hash_set<int>::const_iterator it = sets[a].begin();it != sets[a].end();++ it)
			{
				if(sets[b].find(*it) != sets[b].end())
					++ intersectionsize;
				else
					++ unionsize;
			}
		}
		double res = (double)intersectionsize / (double)unionsize;
		res *= 100;
		printf("%2.1f%%",res);
		if (i != k - 1)
			printf("\n");
	}
}