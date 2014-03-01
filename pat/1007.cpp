#include <iostream>
using namespace std;
int main()
{
	int n;
	cin >> n;
	int* data = new int[n];
	for(int i = 0;i < n;++ i)
		cin >> data[i];
	bool all_negative(true);
	for(int i = 0;i < n;++ i)
		if(data[i] >= 0)
			all_negative = false;
	if(true == all_negative)
	{
		cout << "0" << " " << data[0] << " " << data[n - 1];
		return 0;
	}
	int max(-1),sum,p1,p2;
	for(int i = 0;i < n;++ i)
	{
		sum = 0;
		for(int j = i;j < n; ++ j)
		{
			sum += data[j];
			if(sum > max)
			{
				p1 = i;
				p2 = j;
				max = sum;
			}
		}
	}
	cout << max << " " << data[p1] << " " << data[p2];
	return 0;
}