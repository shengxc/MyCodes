#include <iostream>
#include <vector>
#include <queue>
#include <list>
#include <utility>
#include <string>
#include <algorithm>
using namespace std;
#define INFINITY 10000
bool comp(pair<int,int> a,pair<int,int> b)
{
	if(a.second < b.second)
		return true;
	else
		return false;
}
class person
{
public:
	int start;
	int during;
	int vip;
};
bool operator<(person a,person b)
{
	return a.start > b.start;
}
class table
{
public:
	int count;
	int vip;
	int remain;
};
int time2int(string t)
{
	int h,m,s;
	h = (t[0] - '0') * 10 + t[1] - '0';
	m = (t[3] - '0') * 10 + t[4] - '0';
	s = (t[6] - '0') * 10 + t[7] - '0';
	return (h - 8) * 3600 + m * 60 + s;
}
string int2time(int t)
{
	int h = t / 3600;
	int m = (t - h * 3600) / 60;
	int s = t - h * 3600 - m * 60;
	h += 8;
	string ret("00:00:00");
	ret[0] = (h / 10) + '0';
	ret[1] = (h % 10) + '0';
	ret[3] = (m / 10) + '0';
	ret[4] = (m % 10) + '0';
	ret[6] = (s / 10) + '0';
	ret[7] = (s % 10) + '0';
	return ret;
}
int getminute(int a,int b)
{
	int ret = (b - a) / 60;
	if((b - a) % 60 >= 30)
		++ ret;
	return ret;
}
int main()
{
	int n;
	cin >> n;
	priority_queue<person> people;
	for(int i = 0;i < n;++ i)
	{
		string t;
		cin >> t;
		int d;
		cin >> d;
		int v;
		cin >> v;
		person tmp;
		tmp.start = time2int(t);
		tmp.during = d * 60;
		if(tmp.during > 7200)
			tmp.during = 7200;
		tmp.vip = v;
		people.push(tmp);
	}
	int k,m;
	cin >> k >> m;
	vector<table> tables(k);
	for(int i = 0;i < k;++ i)
	{
		tables[i].count = 0;
		tables[i].remain = 0;
		tables[i].vip = 0;
	}
	for(int i = 0;i < m;++ i)
	{
		int tmp;
		cin >> tmp;
		tables[tmp - 1].vip = 1;
	}
	vector< pair<int,int> > result;
	int now(0);
	list<person> cur;
	int number_of_vip_in_cur(0);
	while(now < (21 - 8) * 3600 && !(people.empty() && cur.empty()))
	{
		while(!people.empty() && people.top().start <= now)
		{
			if(people.top().vip == 1)
				++ number_of_vip_in_cur;
			cur.push_back(people.top());
			people.pop();
		}
		if(cur.empty())
		{
			if(!people.empty())
			{
				int past = now;
				now = people.top().start;
				for(int i = 0;i < k;++ i)
				{
					tables[i].remain -= (now - past);
					if(tables[i].remain <= 0)
						tables[i].remain = 0;
				}
				continue;
			}
		}

		for(int i = 0;i < k;++ i)            //先处理VIP桌子和VIP人
		{
			if(!cur.empty())
			{
				if(tables[i].remain == 0 && tables[i].vip == 1)		//有空的VIP桌
				{
					list<person>::iterator it;
					for(it = cur.begin();it != cur.end();++ it)
						if(it->vip == 1)
							break;
					if(it != cur.end())								//队列中有VIP
					{
						tables[i].remain = it->during;
						++ tables[i].count;
						result.push_back(make_pair(it->start,now));
						cur.erase(it);
					}
				}
			}
			else
				break;

		}
		for(int i = 0;i < k;++ i)
		{
			if(!cur.empty())	//如果当前队列中有人
			{
				if(tables[i].remain == 0)
				{
					tables[i].remain = cur.front().during;
					++ tables[i].count;
					result.push_back(make_pair(cur.front().start,now));
					cur.pop_front();
				}
			}
			else
				break;
		}


		int min(INFINITY);
		for(int i = 0;i < k;++ i)
			if(tables[i].remain < min)
				min = tables[i].remain;
		now += min;
		for(int i = 0;i < k;++ i)
		{
			tables[i].remain -= min;
		}
	}
	sort(result.begin(),result.end(),comp);
	for(size_t i = 0;i < result.size();++ i)
	{
		string a = int2time(result[i].first);
		string b = int2time(result[i].second);
		int minutes = getminute(result[i].first,result[i].second);
		cout << a << " " << b << " " << minutes << endl;
	}
	for(int i = 0;i < k;++ i)
	{
		cout << tables[i].count;
		if(i != k - 1)
			cout << " ";
	}
	return 0;
	
}