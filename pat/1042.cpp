#include <iostream>
#include <stdlib.h>
#include <vector>
#include <string>
using namespace std;
const int CARDNUM = 54;
string int2str(int x)
{
	char t[4];
	sprintf(t,"%d",x);
	string res = t;
	return res;
}
void deal(string* cards,const int* const ord)
{
	string tmp[CARDNUM];
	for(int i = 0;i < CARDNUM;++ i)
		tmp[ord[i]] = cards[i];
	for(int i = 0;i < CARDNUM;++ i)
		cards[i] = tmp[i];
}
int main()
{
	string c;
	int n;
	cin >> n;
	string cards[CARDNUM];
	for(int i = 0;i < 13;++ i)
	{
		string s = int2str(i + 1);
		cards[i] = "S" + s;
		cards[i + 13] = "H" + s;
		cards[i + 26] = "C" + s;
		cards[i + 39] = "D" + s;
	}
	cards[52] = "J1";
	cards[53] = "J2";
	int ord[CARDNUM];
	for(int i = 0;i < CARDNUM;++ i)
	{
		cin >> ord[i];
		-- ord[i];
	}
	for(int i = 0;i < n;++ i)
		deal(cards,ord);
	for(int i = 0;i < CARDNUM - 1;++ i)
		cout << cards[i] << " ";
	cout << cards[CARDNUM - 1];
}
