#include <iostream>
#include <algorithm>
#include <sstream>
using namespace std;
typedef unsigned long long unl;
bool isPalindromic(string n)
{
	for(size_t i = 0,j = n.size() - 1;i < j;++ i,-- j)
		if(n[i] != n[j])
			return false;	
	return true;
}
string deal(string n)
{
	string x,r;
	string::iterator b,e;
	x = n;
	b = x.begin(); 
	e = x.end();
	reverse(b,e);
	int j(0);
	for(int i = x.size() - 1;i >= 0;-- i)
	{
		char t = (n[i] + x[i] - 2 * '0' + j) % 10 + '0';
		r = t + r;
		j = (n[i] + x[i] - 2 * '0' + j) / 10;
	}
	if(j != 0)
		r = (char)(j + '0') + r;
	return r;
}
int main()
{
	string n;
	int k;
	cin >> n >> k;
	int count(0);
	while(!isPalindromic(n) && count < k)
	{
		++ count;
		n = deal(n);
	}
	cout << n << "\n" << count;
}
