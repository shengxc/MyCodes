#include <iostream>
#include <map>
#include <iomanip>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>
#include <cassert>
#include <fstream>
using namespace std;
int trans(string s)
{
	char a,b;
	a = s[0];
	b = s[1];
	int h = (a - '0') * 10 + (b - '0');
	a = s[3];
	b = s[4];
	int m = (a - '0') * 10 + (b - '0');
	a = s[6];
	b = s[7];
	int sec = (a - '0') * 10 + (b - '0');
	int time = h * 3600 + m * 60 + sec;
	return (time - 8 * 3600);
}
int main()
{
	unsigned long long total_waiting_time(0);
	vector<int> window;
	map<int,int> people;
	int n,k;
	cin >> n >> k;
	for(int i = 0;i < n;++ i)
	{
		string arrive_time;
		int serve_time;
		cin >> arrive_time >> serve_time;
		int time = trans(arrive_time);
		people.insert(make_pair(time,serve_time * 60));
	}
	for(int i = 0;i < k; ++i)
		window.push_back(0);
	int now(0);
	map<int,int>::iterator it;
	for(it = people.begin();it != people.end();++ it)
		if (it->first > 9 * 3600)
		{
			break;
		}
	people.erase(it,people.end());
	for(it = people.begin();it != people.end();++ it)
		if (it->second > 3600)
		{
			it->second = 3600;
		}
	int x = people.size();
	map<int,int>::iterator waiting_head;
	waiting_head = people.begin();
	while(1)
	{
		if (waiting_head == people.end())
			break;
		for(int i = 0;i < window.size(); ++ i)  //对于每个窗口
		{
			if(0 == window[i])  //如果该窗口没有人
			{
				if (waiting_head->first <= now)  //如果当前队列里有人
				{
					window[i] = waiting_head->second;
					total_waiting_time += (now - waiting_head->first);
					people.erase(waiting_head);
					waiting_head = people.begin();
					if (waiting_head == people.end())
						break;
				}
				else                            //如果当前队列里没有人
				{
					int time_dif = waiting_head->first - now;
					now = waiting_head->first;
					for(int j = 0;j < window.size();++ j)
					{
						window[j] -= time_dif;
						if(window[j] < 0)
							window[j] = 0;
					}
					i = -1;
				}
			}
		}
		int min = 0xFFFFFFF;
		for(int i = 0;i < window.size(); ++ i)  //寻找需要最短服务时间的窗口
			if (min > window[i])
				min = window[i];
		now += min;
		for(int i = 0;i < window.size();++ i)  //等待需要最短服务时间的窗口完成
		{
			window[i] -= min;
		}
	}
	double r;
	if(x == 0)
		r = 0;
	else
		r = total_waiting_time / ((double) x * 60.0);
	cout << fixed << setprecision(1) << r;
}