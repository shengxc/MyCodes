#include <iostream>
#include <string>
using namespace std;
string plus1(const string& a,const string& b)//两个正数相加
{
	string res;
	int idxa = a.size() - 1;
	int idxb = b.size() - 1;
	int carry(0);
	while(idxa >= 0 && idxb >= 0)
	{
		int tmp = a[idxa] - '0' + b[idxb] - '0' + carry;
		carry = tmp / 10;
		res = (char)(tmp % 10 + '0') + res;
		-- idxa;--idxb;
	}
	while(idxa >= 0)
	{
		int tmp = a[idxa] - '0' + carry;
		carry = tmp / 10;
		res = (char)(tmp % 10 + '0') + res;
		-- idxa;
	}
	while(idxb >= 0)
	{
		int tmp = b[idxb] - '0' + carry;
		carry = tmp / 10;
		res = (char)(tmp % 10 + '0') + res;
		-- idxb;
	}
	if(carry > 0)
		res = (char)(carry + '0') + res;
	return res;
}
bool positivebigger(const string& a,const string& b)	//两个正数比较大小
{
	if (a.size() > b.size())
		return true;
	else if (a.size() == b.size())
		return a > b;
	else
		return false;
}
bool bigger(const string& a,const string& b)	//两个数比较大小
{
	if (a[0] == '-' && b[0] != '-')
		return false;
	else if (a[0] != '-' && b[0] == '-')
		return true;
	else if (a[0] == '-' && b[0] == '-')
		return positivebigger(b,a);
	else
		return positivebigger(a,b);
}
string specialminus1(const string& a,const string& b)	//大数减小数
{
	string res;
	int idxa = a.size() - 1;
	int idxb = b.size() - 1;
	int borrow(0);
	while(idxa >= 0 && idxb >= 0)
	{
		if (a[idxa] - borrow < b[idxb])
		{
			res = (char)(a[idxa] - borrow + 10 - b[idxb] + '0') + res;
			borrow = 1;
		}
		else
		{
			res = (char)(a[idxa] - borrow - b[idxb] + '0') + res;
			borrow = 0;
		}
		-- idxa;--idxb;
	}
	while(idxa >= 0)
	{
		if (a[idxa] - '0' < borrow)
		{
			res = (char)(a[idxa] - borrow + 10) + res;
			borrow = 1;
		}
		else
		{
			res = (char)(a[idxa] - borrow) + res;
			borrow = 0;
		}
		-- idxa;
	}
	int idx;
	for (idx = 0;idx < res.size();++ idx)
		if (res[idx] != '0')
			break;
	res = res.substr(idx);
	if (res.size() == 0)
		res = "0";
	return res;
}
string minus1(const string& a,const string& b)	//两个正数相减
{
	if (positivebigger(a,b))
		return specialminus1(a,b);
	else
	{
		string tmp = specialminus1(b,a);
		return '-' + tmp;
	}
}
string add(const string& a,const string& b)
{
	string res;
	if(a[0] == '-' && b[0] == '-')
	{
		res = plus1(a.substr(1),b);
		res = "-" + res;
	}
	else if(a[0] == '-' && b[0] != '-')
	{
		res = minus1(b,a.substr(1));
	}
	else if(a[0] != '-' && b[0] == '-')
	{
		res = minus1(a,b.substr(1));
	}
	else
	{
		res = plus1(a,b);
	}
	return res;
}

int main()
{
	int n;
	string a,b,c;
	cin >> n;
	for(int i = 0;i < n;++ i)
	{
		cin >> a >> b >> c;
		string res = add(a,b);
		if(bigger(res,c))
			cout << "Case #" << i + 1 << ": true" << endl;
		else
			cout << "Case #" << i + 1 << ": false" << endl;
	}
}
