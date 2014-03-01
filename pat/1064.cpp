#include <iostream>
#include <vector>
#include <map>
#include <queue>
#include <algorithm>
#include <cstdio>
#include <cstdlib>
using namespace std;
int getroot(int a,int b)
{
	if(a == b)
		return a;
	int level(0);
	int nodenum = b - a + 1;
	while(nodenum != 0)
	{
		nodenum >>= 1;
		++ level;
	}
	nodenum = b - a + 1;
	int remain = nodenum - ((1 << (level - 1)) - 1);
	int destidx;
	if(remain > (1 << (level - 2))) 
	{
		int delta = (1 << (level - 2)) - (remain - (1 << (level - 2)));
		destidx = (nodenum - delta) / 2 + delta;
	}
	else
	{
		destidx = (nodenum - remain) / 2 + remain;
	}
	return a + destidx;
}
int main()
{
	int n;
	cin >> n;
	vector<int> v;
	for(int i = 0;i < n;++ i)
	{
		int tmp;
		cin >> tmp;
		v.push_back(tmp);
	}
	sort(v.begin(),v.end());
	queue<pair<int,int> > qu;
	qu.push(make_pair(0,v.size() - 1));
	vector<int> res;
	while(!qu.empty())
	{
		pair<int,int> elem = qu.front();
		qu.pop();
		int root = getroot(elem.first,elem.second);
		res.push_back(v[root]);
		if(elem.first < elem.second)
		{
			if (elem.first <= root - 1)
				qu.push(make_pair(elem.first,root - 1));
			if (root + 1 <= elem.second)
				qu.push(make_pair(root + 1,elem.second));
		}
	}
	for(int i = 0;i < res.size() - 1;++ i)
		cout << res[i] << " ";
	cout << res[res.size() - 1];
}
