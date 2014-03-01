#include <iostream>
#include <string>
using namespace std;
string change(int x)
{
	string s;
	while(x != 0)
	{
		int t = x % 13;
		x /= 13;
		if(0 <= t && t<= 9)
		{
			char c = (char)(t + '0');
			s = c + s;
		}
		else
		{
			char c = (char)(t - 10 + 'A');
			s = c + s;
		}
	}
	if(s.size() == 1)
		s = '0' + s;
	if(s.size() == 0)
		s = "00";
	return s;
}
int main()
{
	int r,g,b;
	cin >> r >> g >> b;
	string mr,mg,mb;
	mr = change(r);
	mg = change(g);
	mb = change(b);
	cout << "#" + mr + mg + mb;
}