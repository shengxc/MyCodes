#include <iostream>
#include <string>
using namespace std;
int main()
{
	int n;
	cin >> n;
	int base(1);
	int lower(0),current(0),higher(0);
	int res(0);
	while(n / base != 0)
	{
		lower = n - (n / base) * base;
		current = (n / base) % 10;
		higher = n / (base * 10);
		switch(current)
		{
		case 0:
			res += higher * base;
			break;
		case 1:
			res += higher * base + lower + 1;
			break;
		default:
			res += (higher + 1) * base;
			break;
		}
		base *= 10;
	}
	cout << res;
}