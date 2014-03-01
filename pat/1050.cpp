#include <iostream>
#include <map>
#include <string>
#include <vector>
int const MAXLEN = 10000;
using namespace std;
int main()
{
	map<char,vector<int> > hash;
	string s;
	bool* flag = new bool[MAXLEN];
	getline(cin,s);
	for (int i = 0;i < s.length();++ i)
	{
		hash[s[i]].push_back(i);
		flag[i] = true;
	}
	string ss;
	getline(cin,ss);
	for (int i = 0;i < ss.length();++ i)
	{
		if (hash.count(ss[i]) == 0)
			continue;
		for (vector<int>::iterator it = hash[ss[i]].begin();it != hash[ss[i]].end();++ it)
			flag[*it] = false;
	}
	for(int i = 0;i < s.length();++ i)
	{
		if (flag[i] == true)
			cout << s[i];
	}
}