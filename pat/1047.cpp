#include <iostream>
#include <cstring>
#include <set>
#include <string>
#include <algorithm>
#include <vector>
using namespace std;
struct namestr
{
	char name[5];
	bool operator< (const namestr& rhs) const
	{
		return strcmp(name,rhs.name) < 0;
	}
};
int main()
{
	int n,k;
	scanf("%d %d",&n,&k);
	vector<namestr>* courses = new vector<namestr>[k + 1];
	for (int i = 0;i < n;++ i)
	{
		namestr tmpname;
		int kk;
		scanf("%s",tmpname.name);
		scanf("%d",&kk);
		for(int j = 0;j < kk;++ j)
		{
			int tmp;
			scanf("%d",&tmp);
			courses[tmp].push_back(tmpname);
		}
	}
	for (int i = 1;i <= k;++ i)
	{
		cout << i << " " << courses[i].size() << "\n";
		sort(courses[i].begin(),courses[i].end());
		for (int j = 0;j < courses[i].size();++ j)
		{
			printf("%s\n",courses[i][j].name);
		}
	}
}
