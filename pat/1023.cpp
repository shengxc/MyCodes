#include <iostream>
#include <string>
#include <vector>
using namespace std;
bool comp(string a,string b)
{
	if(a.size() != b.size())
		return false;
	vector<int> v(10,0);
	for(size_t i = 0;i < a.size();++ i)
		++ v[a[i] - '0'];
	for(size_t i = 0;i < b.size();++ i)
		-- v[b[i] - '0'];
	for(size_t i = 0;i < v.size();++ i) 
		if(v[i] != 0)
			return false;
	return true;
}

int main()
{
	string s;
	string r;
	cin >> s;
	int j(0);
	for(int i = s.size() - 1;i >= 0; -- i)
	{
		char c = ((s[i] - '0') * 2 + j) % 10 + '0';
		r = c + r;
		j = ((s[i] - '0') * 2 + j) / 10;
	}
	if(j != 0)
		r = (char) (j + '0') + r;
	if(comp(s,r))
		cout << "Yes\n" << r;
	else
		cout << "No\n" << r; 
}