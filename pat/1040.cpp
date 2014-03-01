#include <iostream>
#include <cstring>
#include <vector>
#include <algorithm>
using namespace std;
const int MAX = 1001;
bool sym(char* str,int a,int b)
{
	int mid;
	if ((b - a) % 2 == 1)
	{
		mid = a + (b - a) / 2;
		for (int i = 1;i <= (b - a) / 2;++ i)
			if (str[mid - i] != str[mid + i])
				return false;
		return true;
	}
	else
	{
		int x(a),y(b - 1);
		while(x < y)
		{
			if (str[x] != str[y])
				return false;
			++ x;
			-- y;
		}
		return true;
	}
}
int main()
{
	char str[MAX];
	gets(str);
	int len = strlen(str);
	int min(0),max(0),sublen(1);
	for (int cur = 1;cur <= len;++ cur)
	{
		int tmplen(-1);
		for(int i = cur - 2;i >= 0;i = i - 1)
			if (sym(str,i,cur))
				tmplen = cur - i;
		if (tmplen > sublen)
			sublen = tmplen;
	}
	cout << sublen;
}