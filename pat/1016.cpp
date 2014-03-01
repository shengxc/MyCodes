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
string month;
class Time
{
private:
	string t;
public:
	Time(string x):t(x)
	{}
	Time()
	{}
	bool operator <(const Time x) const
	{
		return t < x.t;
	}
	bool operator <=(const Time x) const
	{
		return (t < x.t) || (t == x.t);
	}
	int operator -(const Time x) const
	{
		int r(0);
		int d1,d2,h1,h2,m1,m2;
		char c;
		istringstream istrm1(t),istrm2(x.t);
		istrm1 >> d1 >> c >> h1 >> c >> m1;
		istrm2 >> d2 >> c >> h2 >> c >> m2;
		if(m1 < m2)
		{
			r = r + m1 + 60 - m2;
			h1 --;
		}
		else
			r = r + m1 - m2;
		if (h1 < h2)
		{
			r = r + (h1 + 24 - h2) * 60;
			d1 --;
		}
		else
			r = r + (h1 - h2) * 60;
		r = r + (d1 - d2) * 24 * 60;
		return r;
	}
	string gettime() const
	{
		return t;
	}
	void increase_hour()
	{
		char c1,c2;
		c1 = t[0];
		c2 = t[1];
		int d = (c1 - '0') * 10 + (c2 - '0');
		c1 = t[3];
		c2 = t[4];
		int h = (c1 - '0') * 10 + (c2 - '0');
		h ++;
		if (h > 23)
		{
			h -= 24;
			d ++;
		}
		t[0] = d / 10 + '0';
		t[1] = d % 10 + '0';
		t[3] = h / 10 + '0';
		t[4] = h % 10 + '0';
		t[6] = '0';
		t[7] = '0';
	}
	int get_remain_minutes()
	{
		char c1 = t[6];
		char c2 = t[7];
		int minute = (c1 - '0') * 10 + (c2 - '0');
		return (60 - minute);
	}
	int get_hour()
	{
		char c1,c2;
		c1 = this->t[3];
		c2 = this->t[4];
		int hour = (c1 - '0') * 10 + (c2 - '0');
		return hour;
	}
};
class Record
{
public:
	string type;
	Time time;
public:
	Record(string ttime,string ttype):type(ttype)
	{
		month = ttime.substr(0,2);
		time = ttime.substr(3);
	}
	bool operator <(Record x) const
	{
		return time < x.time;
	}
};
double calculate_price(Time s,Time e,const vector<int>& rate)
{
	int sum(0);
	int b = s.get_remain_minutes();
	int h = s.get_hour();
	sum += rate[h] * b;
	s.increase_hour();
	while(s <= e)
	{
		h = s.get_hour();
		sum += rate[h] * 60;
		s.increase_hour();
	}
	b = e.get_remain_minutes();
	h = e.get_hour();
	sum -= rate[h] * b;
	double result = (double)sum / 100.0;
	return result;
}
int main()
{
	int n;
	vector<int> rate;
	for(int i = 0;i < 24;++i)
	{
		int t;
		cin >> t;
		rate.push_back(t);
	}
	map< string,vector<Record> > records;
	cin >> n;
	for(int i = 0;i < n; ++i)
	{
		string name;
		cin >> name;
		string time;
		cin >> time;
		string type;
		cin >> type;
		Record r(time,type);
		map< string,vector<Record> >::iterator it = records.find(name);
		if (it != records.end())
			(it->second).push_back(r);
		else
			(records[name]).push_back(r);
	}
	map< string,vector<Record> >::iterator it;
	for (it = records.begin();it != records.end();++ it)
	{
		ostringstream os;
		double total(0);
		sort((it->second).begin(),(it->second).end());
		vector<Record>::iterator record_it1 = (it->second).begin();
		vector<Record>::iterator record_it2 = record_it1 + 1;
		while(record_it2 != (it->second).end())
		{
			if ((record_it1->type == "on-line") && (record_it2->type == "off-line"))
			{
				os << (record_it1->time).gettime() << " " << (record_it2->time).gettime() << " " << (record_it2->time) - (record_it1->time) << " {1}quot;;
				double price = calculate_price(record_it1->time,record_it2->time,rate);
				os << fixed << setprecision(2) << price << endl;
				total += price;
				record_it1 = record_it2 + 1;
			}
			else
				record_it1 ++;
			if (record_it1 != (it->second).end())
				record_it2 = (record_it1 + 1);
			else
				record_it2 = (it->second).end();
		}
		if (os.str() != "")
		{
			cout << it->first << " " << month << endl;
			cout << os.str();
			cout << "Total amount: {1}quot; << fixed << setprecision(2) << total << endl;
		}
	}
}