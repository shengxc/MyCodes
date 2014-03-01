#include <iostream>
#include <set>
#include <map>
#include <string>
#include <vector>
using namespace std;
int flag[10000];
int main()
{
	int n;
	scanf("%d",&n);
	vector<int> data;
	map<int,bool> m;
	for (int i = 0;i < n;++ i)
	{
		int tmp;
		scanf("%d",&tmp);
		data.push_back(tmp);
		++ flag[tmp];
	}
	for (int i = 0;i < n;++ i)
	{
		if (flag[data[i]] == 1)
		{
			cout << data[i];
			return 0;
		}
	}
	cout << "None";
	return 0;
}