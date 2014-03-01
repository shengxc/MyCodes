#include <iostream>
#include <algorithm>
#include <map>
#include <string>
#include <vector>
using namespace std;
bool cmp(const string& a,const string& b)
{
	string s1 = a + b;
	string s2 = b + a;
	return s1 < s2;
}
bool zero(const string& x)
{
	for(int i = 0;i < x.size();++ i)
		if (x[i] != '0')
			return false;
	return true;
}
int main()
{
	int n;
	vector<string> data;
	cin >> n;
	for(int i = 0;i < n;++ i)
	{
		string tmp;
		cin >> tmp;
		data.push_back(tmp);
	}
	sort(data.begin(),data.end(),cmp);
	int idx(0);
	while(idx < data.size())
	{
		if (zero(data[idx]))
			++ idx;
		else
			break;
	}
	if (idx == data.size())
		cout << "0";
	else
	{
		data[idx] = data[idx].substr(data[idx].find_first_not_of('0'));
		for (int i = idx;i < data.size();++ i)
			cout << data[i];
	}
}