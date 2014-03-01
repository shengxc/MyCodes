#include <iostream>
#include <algorithm>
#include <map>
#include <string>
#include <vector>
using namespace std;
class Record
{
public:
	string num;
	int score;
public:
	Record():num(""),score(0){}
	friend bool operator<(Record a,Record b);
	friend istream& operator >>(istream& is,Record& r);
};
inline bool operator<(Record a,Record b)
{
	if(a.score > b.score)
		return true;
	else
	{
		if(a.score == b.score)
			return a.num < b.num;
		else
			return false;
	}
}
istream& operator >>(istream& is,Record& r)
{
	string s;
	int t;
	is >> s >> t;
	if(is)
	{
		r.num = s;
		r.score = t;
	}
	else
	{
		r = Record();
	}
	return is;
}
int main()
{
	map<string,int> location_number,local_rank;
	vector<int> final_rank;
	int n,k;
	int sum(0);
	cin >> n;
	vector< vector<Record> > locations(n);
	vector<Record> total;
	for(int i = 0;i < n;++ i) 
	{
		cin >> k;
		sum += k;
		for(int j = 0;j < k;++ j)
		{
			Record t;
			cin >> t;
			locations[i].push_back(t);
		}
	}
	for(int i = 0;i < n;++ i)
		sort(locations[i].begin(),locations[i].end());
	for(int i = 0;i < n; ++i)
	{
		vector<Record>::iterator it;
		for(it = locations[i].begin();it != locations[i].end();++ it)
			total.push_back(*it);
	}
	sort(total.begin(),total.end());

	int rank(1);
	int num(1);
	final_rank.push_back(rank);
	for(size_t i = 1;i < total.size();++ i)
	{
		if(total[i].score < total[i - 1].score)
		{
			rank += num;
			num = 1;
		}
		else
			++ num;
		final_rank.push_back(rank);
	}
	
	for(size_t i = 0;i < locations.size();++ i)
	{
		rank = 1;
		num = 1;
		local_rank.insert(make_pair(locations[i][0].num,rank));
		for(size_t j = 1;j < locations[i].size();++ j)
		{
			if(locations[i][j].score < locations[i][j - 1].score)
			{
				rank += num;
				num = 1;
			}
			else
				++ num;
			local_rank.insert(make_pair(locations[i][j].num,rank));
		}
	}
	for(size_t i = 0;i < locations.size();++ i)
	{
		vector<Record>::iterator it;
		for(it = locations[i].begin();it != locations[i].end();++ it)
			location_number.insert(make_pair(it->num,i + 1));
	}

	cout << sum << endl;
	for(size_t i = 0;i < total.size();++ i)
	{
		cout << total[i].num << " " << final_rank[i] << " " << location_number[total[i].num] << " " << local_rank[total[i].num];  
		if(i != total.size() - 1)
			cout << endl;
	}
}