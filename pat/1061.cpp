#include <iostream>
#include <string>
#include <iomanip>
using namespace std;
enum datatype
{
	NUMBER,UPPER,LOWER,OTHER
};
datatype gettype(char c)
{
	if(c >= '0' && c <= '9')
		return NUMBER;
	else if(c >= 'A' && c <= 'Z')
		return UPPER;
	else if(c >= 'a' && c <= 'z')
		return LOWER;
	else
		return OTHER;
}
int main()
{
	string week[7] = {"MON","TUE","WED","THU","FRI","SAT","SUN"};
	string data[4];
	for(int i = 0;i < 4;++ i)
		cin >> data[i];
	int minlen = data[0].size() > data[1].size() ? data[1].size() : data[0].size();
	int idx(0);
	for(;idx < minlen;++idx)
	{
		if(gettype(data[0][idx]) == UPPER && data[0][idx] < 'H' && data[0][idx] == data[1][idx])
		{
			cout << week[data[0][idx] - 'A'] << " ";
			break;
		}
	}
	++ idx;
	bool isend = false;
	for (;idx < minlen && !isend;++ idx)
	{
		if (data[0][idx] == data[1][idx])
		{
			switch(gettype(data[0][idx]))
			{
			case NUMBER:
				cout << 0 << data[0][idx] << ":";
				isend = true;
				break;
			case UPPER:
				if (data[0][idx] <= 'N')
				{
					cout << data[0][idx] - 'A' + 10 << ":";
					isend = true;
				}
				break;
			default:
				break;
			}
		}
	}
	minlen = data[2].size() > data[3].size() ? data[3].size() : data[2].size();
	for(int i = 0;i < minlen;++ i)
	{
		if(gettype(data[2][i]) != UPPER && gettype(data[2][i]) != LOWER)
			continue;
		if(data[2][i] == data[3][i])
		{
			cout << setfill('0') << setw(2) << i;
		}
	}
}