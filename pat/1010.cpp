#include <iostream>
#include <cstdlib>
#include <fstream>
#include <algorithm>
#include <iomanip>
#include <string>
#include <exception>
#include <deque>
#include <ctime>
using namespace std;
class bigint
{
private:
	deque<int> num;
	bool sign;
	bigint positive_subtraction(const bigint x) const; //本身减去x，两个都是正数，忽略符号，且调用者大于x
	void abs()
	{
		if(false == sign)
			sign = true;
	}
	bigint subnum(deque<int>::const_iterator b,deque<int>::const_iterator e) const  //返回b,e两个迭代器之间的数构成的大数
	{
		bigint r;
		r.sign = sign;
		deque<int> t(b,e);
		r.num = t;
		return r;
	}
public:
	bigint():sign(true)
	{
		num.push_back(0);
	}
	bigint(const bigint& x)
	{
		this->num = x.num;
		this->sign = x.sign;
	}
	bigint(const int& x)
	{
		int t;
		int y = x;
		if(y < 0)
		{
			sign = false;
			y = -y;
		}
		else
			sign = true;
		while(y > 0)
		{
			t = y % 10;
			num.push_front(t);
			y /= 10;
		}
		if(0 == num.size())
			num.push_front(0);
	}
	bigint(const unsigned long long& x)
	{
		unsigned long t;
		unsigned long y = x;
		sign = true;
		while(y > 0)
		{
			t = y % 10;
			num.push_front(t);
			y /= 10;
		}
		if(0 == num.size())
			num.push_front(0);
	}
	~bigint()
	{}
	const bigint operator =(const bigint& x)
	{
		this->num = x.num;
		this->sign = x.sign;
		return *this;
	}
	const bigint operator =(const int& x)
	{
		int t;
		int y = x;
		num.clear();
		if(y < 0)
		{
			sign = false;
			y = -y;
		}
		else
			sign = true;
		while(y > 0)
		{
			t = y % 10;
			num.push_front(t);
			y /= 10;
		}
		if(0 == num.size())
			num.push_front(0);
		return *this;
	}
	const bigint operator -() const
	{
		bigint r(*this);
		r.sign = !sign;
		return r;
	}
	bool operator ==(const bigint& x) const;
	bool operator !=(const bigint& x) const;
	bool operator >(const bigint& x) const;
	bool operator >=(const bigint& x) const;
	bool operator <(const bigint& x) const;
	bool operator <=(const bigint& x) const;

	bool operator ==(const int& x) const;
	bool operator !=(const int& x) const;
	bool operator >(const int& x) const;
	bool operator >=(const int& x) const;
	bool operator <(const int& x) const;
	bool operator <=(const int& x) const;


	bigint operator +(const bigint& x) const;
	bigint operator +(const int& x) const;
	bigint operator -(const bigint& x) const;
	bigint operator -(const int& x) const;
	bigint operator *(const bigint& x) const;
	bigint operator *(const int& x) const;
	bigint operator /(const bigint& x) const;
	bigint operator /(const int& x) const;
	bigint operator %(const bigint& x) const;
	bigint operator %(const int& x) const;

	string tostring() const
	{
		string s;
		char c;
		deque<int>::const_iterator it;
		for (it = num.begin();it != num.end();++it)
		{
			c = (*it) + '0';
			s += c;
		}
		return s;
	}
};

bigint bigint::positive_subtraction(const bigint x) const
{
	int minuend,subtrahend,dif,borrow(0);
	bigint r;
	r.num.clear();
	deque<int>::const_iterator it1,it2;
	it1 = num.end();
	it2 = x.num.end();
	do 
	{
		-- it1;
		-- it2;
		minuend = *it1 - borrow;
		subtrahend = *it2;
		if(minuend < subtrahend)
		{
			dif = minuend  + 10 - subtrahend;
			borrow = 1;
		}
		else
		{
			dif = minuend - subtrahend;
			borrow = 0;
		}
		r.num.push_front(dif);
	} while (it1 != num.begin() && it2 != x.num.begin());
	if (it1 != num.begin())
	{
		do 
		{
			-- it1;
			minuend = *it1 - borrow;
			subtrahend = 0;
			if(minuend < subtrahend)
			{
				dif = minuend  + 10 - subtrahend;
				borrow = 1;
			}
			else
			{
				dif = minuend - subtrahend;
				borrow = 0;
			}
			r.num.push_front(dif);
		} while (it1 != num.begin());
	}
	if(0 == r.num.size())
		r.num.push_front(0);
	else
	{
		for(it1 = r.num.begin();it1 != r.num.end();++it1)
			if(*it1 != 0)
				break;
		if (it1 == r.num.end())
		{
			r.num.clear();
			r.num.push_front(0);
		}
	}
	deque<int>::iterator it3;
	it3 = r.num.begin();
	while((*it3 == 0) && ((it3 + 1) != r.num.end()))
	{
		r.num.erase(it3);
		it3 = r.num.begin();
	}
	return r;
}
bool bigint::operator ==(const bigint& x) const
{
	if (num.size() != x.num.size())
		return false;
	else
	{
		deque<int>::const_iterator it1,it2;
		for(it1 = num.begin(),it2 = x.num.begin();it1 != num.end();++ it1,++ it2)
			if(*it1 != *it2)
				break;
		if(it1 == num.end())
			return true;
		else
			return false;
	}
}
bool bigint::operator !=(const bigint& x) const
{
	return !(*this == x);
}

bool bigint::operator >(const bigint& x) const
{
	if (true == sign && true == x.sign)  //都正
	{
		if(num.size() > x.num.size())
			return true;
		else if (num.size() < x.num.size())
			return false;
		else
		{
			deque<int>::const_iterator it1,it2;
			for(it1 = num.begin(),it2 = x.num.begin();it1 != num.end();++ it1,++ it2)
				if(*it1 != *it2)
					break;
			if(it1 == num.end())
				return false;
			else
			{
				if(*it1 > *it2)
					return true;
				else
					return false;
			}
		}
	}
	else if (true == sign && false == x.sign)
		return true;
	else if (false == sign && true == x.sign)
		return false;
	else
	{
		if(num.size() > x.num.size())
			return false;
		else if (num.size() < x.num.size())
			return true;
		else
		{
			deque<int>::const_iterator it1,it2;
			for(it1 = num.begin(),it2 = x.num.begin();it1 != num.end();++ it1,++ it2)
				if(*it1 != *it2)
					break;
			if(it1 == num.end())
				return false;
			else
			{
				if(*it1 < *it2)
					return true;
				else
					return false;
			}
		}
	}
}
bool bigint::operator >=(const bigint& x) const
{
	return ((*this) > x || (*this == x));
}
bool bigint::operator <(const bigint& x) const
{
	return !((*this) >= x);
}
bool bigint::operator <=(const bigint& x) const
{
	return !((*this) > x);
}

bool bigint::operator ==(const int& x) const
{
	bigint y(x);
	return (*this) == y;
}
bool bigint::operator !=(const int& x) const
{
	bigint y(x);
	return (*this) != y;
}
bool bigint::operator >(const int& x) const
{
	bigint y(x);
	return (*this) > y;
}
bool bigint::operator <(const int& x) const
{
	bigint y(x);
	return (*this) < y;
}
bool bigint::operator >=(const int& x) const
{
	bigint y(x);
	return (*this) >= y;
}
bool bigint::operator <=(const int& x) const
{
	bigint y(x);
	return (*this) <= y;
}

bigint bigint::operator +(const bigint& x) const					
{
	int temp_j = 0;
	int temp_sum;
	bigint r;
	r.num.clear();   //空的结果
	deque<int>::const_iterator it1,it2;
	if(sign == x.sign)    //两数同号
	{
		r.sign = sign;
		it1 = num.end();
		it2 = x.num.end();
		do
		{
			-- it1;
			-- it2;
			temp_sum = temp_j + *it1 + *it2;
			temp_j = temp_sum / 10;
			temp_sum = temp_sum % 10;
			r.num.push_front(temp_sum);
		}while(it1 != num.begin() && it2 != x.num.begin()); //从个位开始计算直至一个数碰到最高位
		if (it1 != num.begin())  //如果第一个数比较长
		{
			do
			{
				-- it1;
				temp_sum = temp_j + *it1;
				temp_j = temp_sum / 10;
				temp_sum = temp_sum % 10;
				r.num.push_front(temp_sum);
			}while(it1 != num.begin());
		}
		else if (it2 != x.num.begin()) //如果第二个数比较长
		{
			do
			{
				-- it2;
				temp_sum = temp_j + *it2;
				temp_j = temp_sum / 10;
				temp_sum = temp_sum % 10;
				r.num.push_front(temp_sum);
			}while(it2 != x.num.begin());
		}
		else   //如果两个数一样长
		{}
		if (temp_j != 0)   //加上进位
			r.num.push_front(temp_j);
	}
	else //两数异号
	{
		bigint y;
		if(false == sign) //第一个数为负数，第二个数为正数
		{
			y = -(*this);
			if (y >= x)
			{
				r = y.positive_subtraction(x);
				r.sign = false;
			}
			else
			{
				r = x.positive_subtraction(y);
				r.sign = true;
			}
		}
		else //第一个数为正数，第二个数为负数
		{
			y = -x;
			if (*this >= y)
			{
				r = positive_subtraction(y);
				r.sign = true;
			}
			else
			{
				r = y.positive_subtraction(*this);
				r.sign = false;
			}
		}
	}
	return r;
}

bigint bigint::operator +(const int& x) const
{
	bigint y(x);
	return *this + y;
}
bigint bigint::operator -(const bigint& x) const
{
	bigint b,r;
	b = -x;
	r = (*this) + b;
	return r;
}
bigint bigint::operator -(const int& x) const
{
	bigint y(x);
	return *this - y;
}

bigint bigint::operator *(const bigint& x) const
{
	int count(-1),product,carry;
	bigint temp_result(0),r(0);
	if ((*this != 0) && (x != 0))
	{
		r.sign = ! sign ^ x.sign;
		deque<int>::const_iterator it1,it2;
		it2 = x.num.end();
		do 
		{
			carry = 0;
			temp_result.num.clear();
			++ count;
			it1 = num.end();
			-- it2;
			do 
			{
				-- it1;
				product = (*it1) * (*it2) + carry;
				carry = product / 10;
				product = product % 10;
				temp_result.num.push_front(product);
			} while (it1 != num.begin());
			if(carry != 0)
				temp_result.num.push_front(carry);
			for(int i = 0;i < count;i ++)
				temp_result.num.push_back(0);
			r = r + temp_result;
		} while (it2 != x.num.begin());
	}
	return r;
}
bigint bigint::operator *(const int& x) const
{
	bigint y(x);
	return (*this) * y;
}
bigint bigint::operator /(const bigint& x) const
{
	bigint dividend(*this),divisor(x);
	bigint temp;
	int quotient;
	deque<int>::const_iterator it1,it2,it3,it4;
	dividend.abs();
	divisor.abs();
	bigint r(0);
	if ((*this) == 0)   //被除数==0
	{
		return r;
	}
	if(x == 0)  //除数为0
	{
		return r;
	}
	if (dividend >= divisor)
	{
		r.sign = !(sign ^ x.sign);
		it1 = dividend.num.begin();
		it2 = it1;
		for(unsigned int i = 0;i < divisor.num.size();++i)
			++ it2;
		temp = dividend.subnum(it1,it2);
		do 
		{
			quotient = 0;
			while(temp < divisor && it2 != dividend.num.end())
			{
				temp = temp * 10 + *it2;
				++ it2;
				r.num.push_back(0);
			}
			while(temp >= divisor)
			{
				temp = temp - divisor;
				quotient ++;
			}
			r.num.push_back(quotient);
			if (it2 != dividend.num.end())
			{
				temp = temp * 10 + (*it2);
				it2 ++;
			}
			else
				break;
		} while (1);
		deque<int>::iterator it5;
		it5 = r.num.begin();
		while((0 == *it5) && ((it5 + 1) != r.num.end()))
		{
			r.num.erase(it5);
			it5 = r.num.begin();
		}
	}
	return r;
}

bigint bigint::operator /(const int& x) const
{
	bigint y(x);
	return (*this) / y;
}
bigint bigint::operator %(const bigint& x) const
{
	bigint quotient,r;
	if (false == sign || false == x.sign)
	{
		//	throw(runtime_error("取余操作不能有负数！！！"));
		return r;
	}
	quotient = (*this) / x;
	r = (*this) - quotient * x;
	return r;
}
bigint bigint::operator %(const int& x) const
{
	bigint y(x);
	return (*this) % y;
}

bool test(string& s,bigint r)
{
	char c = s[0];
	for(int i = 1;i < s.size();++i)
	{
		if (s[i] > c)
		{
			c = s[i];
		}
	}
	bigint t;
	if (c - '0' > 10)
		t = c - 'a' + 10;
	else
		t = c - '0';
	if(t > r - 1)
		return false;
	else
		return true;
}
bigint change(string& s,bigint r)
{
	bigint m(1);
	bigint sum(0);
	bigint rr(r);
	bigint t;
	for(int i = s.size() - 1;i >= 0;-- i)
	{
		if(s[i] - '0' > 10)
			t = s[i] - 'a' + 10;
		else
			t = s[i] - '0';
		bigint temp(t);
		sum = sum + temp * m;
		m = m * rr;
	}
	return sum;
}
int main()
{
	string a,b;
	bigint tag,radix;
	bigint a1,b1;
	bigint result(0);
	int tag1,radix1;
	cin >> a >> b >> tag1 >> radix1;
	tag = tag1;
	radix = radix1;
	string::iterator it;
	unsigned long long MAX1 = 0xFFFFFFFF;
	const bigint MAX(MAX1);
	bigint left(1),right(MAX);
	bigint mid;
	if (tag == 1)
	{
		a1 = change(a,radix);
		while(left <= right)
		{
			mid = (left + right) / 2;
			if(mid < 36 && !test(b,mid))
			{
				left = mid + 1;
				continue;
			}
			b1 = change(b,mid);
			if (a1 > b1)
				left = mid + 1;
			else if (a1 < b1)
				right = mid - 1;
			else
			{
				result = mid;
				break;
			}
		}
		right = result;
		for(mid = left;mid < right;mid = mid + 1)
		{
			if(mid < 36 && !test(b,mid))
				continue;
			b1 = change(b,mid);
			if (a1 < b1)
				break;
			else if(a1 == b1)
			{
				result = mid;
				break;
			}
		}
	}
	else
	{
		b1 = change(b,radix);
		while(left <= right)
		{
			mid = (left + right) / 2;
			if(mid < 36 && !test(a,mid))
			{
				left = mid + 1;
				continue;
			}
			a1 = change(a,mid);
			if (a1 > b1)
				right = mid - 1;
			else if (a1 < b1)
				left = mid + 1;
			else
			{
				result = mid;
				break;
			}
		}
		right = result;
		for(mid = left;mid < right;mid = mid + 1)
		{
			if(mid < 36 && !test(a,mid))
				continue;
			a1 = change(a,mid);
			if (a1 > b1)
				break;
			else if(a1 == b1)
			{
				result = mid;
				break;
			}
		}
	}
	if(result == 0)
		cout << "Impossible";
	else
		cout << result.tostring();
	return 0;
}