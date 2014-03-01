#include <iostream>
#include <algorithm>
#include <map>
#include <string>
#include <vector>
using namespace std;
struct node 
{
	int num;
	string ownaddr;
	string nextaddr;
};
bool operator< (const node& n1,const node& n2)
{
	return n1.num < n2.num;
}
int main()
{
	int n;
	string orgaddr;
	cin >> n >> orgaddr;
	map<string,node> data;			//未经处理的数据
	for (int i = 0;i < n;++ i)
	{
		node tmpnode;
		cin >> tmpnode.ownaddr >> tmpnode.num >> tmpnode.nextaddr;
		data.insert(make_pair(tmpnode.ownaddr,tmpnode));
	}
	vector<node> list;				//链表
	while(true)
	{
		map<string,node>::const_iterator tmpit;
		tmpit = data.find(orgaddr);
		if (tmpit == data.end())
			break;
		list.push_back(tmpit->second);
		orgaddr = (tmpit->second).nextaddr;
		if (orgaddr == "-1")
			break;
	}
	data.clear();
	if (list.size() == 0)
	{
		cout << "0 -1";
	}
	else
	{
		sort(list.begin(),list.end());
		cout << list.size() << " " << list[0].ownaddr << "\n";
		for (int i = 0;i < list.size() - 1;++ i)
			cout << list[i].ownaddr << " " << list[i].num << " " << list[i + 1].ownaddr << "\n";
		cout << list[list.size() - 1].ownaddr << " " << list[list.size() - 1].num << " -1";
	}
	
}