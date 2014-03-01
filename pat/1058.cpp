#include <iostream>
#include <string>
using namespace std;
int main()
{
	unsigned long long a[3],b[3];
	unsigned long long res[3];
	char hole;
	for(int i = 0;i < 3;++ i)
	{
		cin >> a[i];
		if (i != 2)
			cin >> hole;
	}
	for(int i = 0;i < 3;++ i)
	{
		cin >> b[i];
		if (i != 2)
			cin >> hole;
	}
	int jw(0);
	for (int i = 2;i >= 0;-- i)
	{
		switch(i)
		{
		case 2:
			res[i] = (a[i] + b[i]) % 29;
			jw = (a[i] + b[i]) / 29;
			break;
		case 1:
			res[i] = (a[i] + b[i] + jw) % 17;
			jw = (a[i] + b[i] + jw) / 17;
			break;
		case 0:
			res[i] = a[i] + b[i] + jw;
			break;
		}
			
	}
	for (int i = 0;i < 3;++ i)
	{
		cout << res[i];
		if (i < 2)
			cout << ".";
	}
}