#include<iostream>
#include <string>
#include <sstream>
#include <iomanip>
#include <vector>
#include <queue>
#include <map>
#include <algorithm>
using namespace std;
string calculate_time(int t)
{
	ostringstream strm;
	int h = t / 60;
	int minute = t % 60;
	int hour = 8 + h;
	strm << setw(2) << setfill('0') << hour << ":" << setw(2)<< setfill('0') << minute;
	return strm.str();
}
bool empty(vector< map<int,int> > v)
{
	for (int i = 0;i < v.size();++ i)
		if (0 != v[i].size())
			return false;
	return true;
}
int main()
{
	map<int,int> outline_waiter;
	vector<int> server_time;
	vector<int> concern;
	int m,n,k,q;
	cin >> n >> m >> k >> q;
	vector< map<int,int> > inline_waiter(n);
	for(int i = 1;i <= k;++ i)
	{
		cin >> outline_waiter[i];
		server_time.push_back(outline_waiter[i]);
	}
	for (int i = 0;i < q;++ i)
	{
		int t;
		cin >> t;
		concern.push_back(t);
	}
	map<int,int>::iterator outline_waiter_head;
	outline_waiter_head = outline_waiter.begin();
	for (int i = 0;i < n * m;++ i) //尽量把线内排满
	{
		if (0 != outline_waiter.size())
		{
			inline_waiter[i % n].insert(make_pair(outline_waiter_head->first,outline_waiter_head->second));
			outline_waiter.erase(outline_waiter_head);
			outline_waiter_head = outline_waiter.begin();
		}
		else
			break;
	}
	map<int,int> result;
	int cur = 0;
	int now = 0;
	while(!empty(inline_waiter))
	{
		map<int,int>::iterator it;
		bool flag(false);
		int min(0);
		for(int i = 0;i < n;++ i)  //寻找最近完成人
		{
			if (0 != inline_waiter[i].size())
			{
				if (false == flag)
				{
					min = i;
					flag = true;
				}
				else
				{
					it = inline_waiter[i].begin();			
					if (((inline_waiter[min]).begin())->second > it->second)
						min = i;
				}
			}
		}
		now += (inline_waiter[min].begin())->second;  //当前时间
		int min_time = inline_waiter[min].begin()->second;
		for(int i = 0;i < n;++ i) //每队列头减去相应的时间
		{
			if (0 == inline_waiter[i].size())
				continue;
			(inline_waiter[i].begin())->second -= min_time;
			if (0 == (inline_waiter[i].begin())->second)
			{
				result.insert(make_pair((inline_waiter[i].begin())->first,now));
				inline_waiter[i].erase(inline_waiter[i].begin());
				if(outline_waiter_head != outline_waiter.end())
				{
					inline_waiter[i].insert(make_pair(outline_waiter_head->first,outline_waiter_head->second));
					outline_waiter.erase(outline_waiter_head);
					outline_waiter_head = outline_waiter.begin();
				}
			}
		}
	}
	for(int i = 0;i < q;++ i)
	{
		map<int,int>::iterator it;
		it = result.find(concern[i]);
		if (it != result.end() && (it->second) - server_time[it->first - 1] < 9 * 60)
			cout << calculate_time(it->second) << endl;
		else
			cout << "Sorry" << endl;
	}

}