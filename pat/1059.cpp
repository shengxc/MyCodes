#include <iostream>
#include <string>
#include <cmath>
#include <set>
#include <map>
using namespace std;
class bits
{
public:
	bits(unsigned long n) : m_size(n),m_bytes(n / 8 + 1)
	{
		m_data = new unsigned char[m_bytes];
		for(unsigned long i = 0;i < m_bytes;++ i)
			m_data[i] = 0;
	}
	void set(unsigned long index)
	{
		unsigned long byteindex = index / 8;
		int subindex = index % 8;
		unsigned char org = 0x80;
		for (int i = 0;i < subindex;++ i)
			org >>= 1;
		m_data[byteindex] |= org;
	}
	bool test(unsigned long index)
	{
		unsigned long byteindex = index / 8;
		int subindex = index % 8;
		unsigned char org = 0x80;
		for (int i = 0;i < subindex;++ i)
			org >>= 1;
		return (m_data[byteindex] & org) != 0;
	}
	~bits()
	{
		delete[] m_data;
	}
private:
	unsigned char* m_data;
	unsigned long m_size;
	unsigned long m_bytes;
};
void print(const map<unsigned long,int>& res)
{
	for(map<unsigned long,int>::const_iterator it = res.begin();it != res.end();++ it)
	{
		if (it->second == 1)
			cout << it->first;
		else
			cout << it->first << "^" << it->second;
		if(-- res.end() != it)
			cout << "*";
	}
}
int main()
{
	set<unsigned long> primes;
	unsigned long n;
	cin >> n;
	cout << n << "=";
	unsigned long cur(2);
	unsigned long max((unsigned long)sqrt(double(n)));
	bits cand(max + 1);
	map<unsigned long,int> result;
	// 计算素数
	while(cur <= max)
	{
		unsigned long x = cur + 1;
		primes.insert(cur);
		for (unsigned long i = cur;i <= max;i += cur)
			cand.set(i);
		for (;x <= max;++ x)
		{
			if (!cand.test(x))
			{
				cur = x;
				break;
			}
		}
		if(cur != x)
			break; 
	}
	// 从素数中寻找	
	for(set<unsigned long>::iterator it = primes.begin();it != primes.end();)
	{
		if (n % (*it) == 0)
		{
			n /= (*it);
			if (result.count(*it) == 0)
				result.insert(make_pair(*it,1));
			else
				result[*it] = result[*it] + 1;
		}
		else
			++ it;
		if (primes.count(n) != 0)
		{
			if (result.count(n) == 0)
				result.insert(make_pair(n,1));
			else
				result[n] = result[n] + 1;
			break;
		}
	}
	if (result.empty())
		result.insert(make_pair(n,1));
	//输出
	print(result);
}