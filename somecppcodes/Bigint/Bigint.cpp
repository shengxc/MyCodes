#include "Bigint.h"
#include <sstream>
#include <exception>
#include <stdexcept>
#include <cstdlib>
#include <climits>
Bigint::Bigint(int i)
{
  ostringstream os;
  os << i;
  num = os.str();
  if(i >= 0)
    positive = true;
  else
  {
    positive = false;
    num = num.substr(1);
  }
}
string Bigint::delprezero(const string& s)
{
  int idx;
  for(idx = 0;idx < s.size();++ idx)
    if(s[idx] != '0')
      break;
  if(idx == s.size())
    -- idx;
  return s.substr(idx);
}
const bool Bigint::less(const string& numa,const string& numb)
{
#ifdef _DEBUG
  cout << numa << "<" << numb << "\t";
#endif
  if(numa.size() < numb.size())
    return true;
  else
  {
    if(numa.size() == numb.size())
    {
      for(int i = 0;i < numa.size(); ++ i)
      {
        if(numa[i] < numb[i])
          return true;
        else if(numa[i] > numb[i])
          break;
        else
          continue;
      }
    }
  }
  return false;
}
const bool Bigint::operator<(const Bigint& rhs) const
{
  if(positive && rhs.positive)
  {
    return Bigint::less(num,rhs.num);
  }
  else if(!positive && !rhs.positive)
  {
    return Bigint::less(rhs.num,num);
  }
  else if(!positive && rhs.positive)
    return true;
  else
    return false;
}
const bool Bigint::operator==(const Bigint& rhs) const
{
  if(positive == rhs.positive && num == rhs.num)
    return true;
  return false;
}
const bool Bigint::operator<=(const Bigint& rhs) const
{
  return (*this < rhs) || (*this == rhs);
}
const bool Bigint::operator>(const Bigint& rhs) const
{
  return !((*this < rhs) || (*this == rhs));
}
const bool Bigint::operator>=(const Bigint& rhs) const
{
  return !(*this < rhs);
}
const bool Bigint::operator!=(const Bigint& rhs) const
{
  return !(*this == rhs);
}

istream& operator>>(istream& is,Bigint& rhs)
{
  string s;
  is >> s;
  if(s[0] == '-')
  {
    rhs.positive = false;
    s = s.substr(1);
  }
  else
  {
    rhs.positive = true;
  }
  for(int i = 0;i < s.size();++ i)
    if(!(s[i] <= '9' && s[i] >= '0'))
      throw runtime_error("All input characters must be digits from 0 to 9!");
  rhs.num = s;
  return is;
}
ostream& operator<<(ostream& os,const Bigint& rhs)
{
  if(!rhs.positive)
    os << "-";
  os << rhs.num;
  return os;
}
int Bigint::extend(string& a,string& b)
{
  int lena = a.size();
  int lenb = b.size();
  if(lena < lenb)
    for(int i = 0;i < lenb - lena;++ i)
      a = '0' + a;
  else
    for(int i = 0;i < lena - lenb;++ i)
      b = '0' + b;
  int len = lena > lenb ? lena : lenb;
  return len;
}
const string Bigint::add(const string& na,const string& nb)
{
  string res;
  string numa(na),numb(nb);
  int len = Bigint::extend(numa,numb);
  int carry(0);
#ifdef _DEBUG
//  cout << "add " << numa << " " << numb << endl;
#endif
  for(--len;len >= 0;--len)
  {
    int a = numa[len] - '0';
    int b = numb[len] - '0';
    int sum = a + b + carry;
    res = (char)(sum % 10 + '0') + res;
    carry = sum / 10;
#ifdef _DEBUG
 //   cout << a << "+" << b << "=" << sum % 10 << " carry " << carry << endl;
#endif
  }
  if(carry != 0)
    res = (char)(carry + '0') + res;
  return res;
}

const string Bigint::minus(const string& na,const string& nb)
{
  string res;
  string numa(na),numb(nb);
  int len = Bigint::extend(numa,numb);
  int borrow(0);
#ifdef _DEBUG
//  cout << "minus " << numa << " " << numb << endl;
#endif
  for(--len;len >= 0;--len)
  {
    int a = numa[len] - '0';
    int b = numb[len] - '0';
    int diff = a - borrow - b;
#ifdef _DEBUG
 //   cout << a << "-" << borrow << "-" << b << "=" << diff << endl;
#endif
    if(diff < 0)
    {
      diff += 10;
      borrow = 1;
    }
    else
      borrow = 0;
    res = (char)(diff + '0') + res;
  }
  return delprezero(res);
}
const Bigint Bigint::operator+(const Bigint& rhs) const
{
  string sum;
  bool flag;
  if((positive && rhs.positive) || (!positive && !rhs.positive))
  {
    sum = add(num,rhs.num);
    flag = positive;
  }
  else
  {
    if(less(num,rhs.num))
    {
      sum = Bigint::minus(rhs.num,num);
      flag = rhs.positive;
    }
    else
    {
      sum = Bigint::minus(num,rhs.num);
      flag = positive;
    }
  }
  if(sum == "0")
    flag = true;
  return Bigint(sum,flag);
}

const Bigint Bigint::operator-(const Bigint& rhs) const
{
  string diff;
  bool flag;
  if(positive && rhs.positive)
  {
    if(Bigint::less(num,rhs.num))
    {
      diff = Bigint::minus(rhs.num,num);
      flag = false;
    }
    else
    {
      diff = Bigint::minus(num,rhs.num);
      flag = true;
    }
  }
  else if((positive && !rhs.positive) || (!positive && rhs.positive))
  {
    diff = Bigint::add(num,rhs.num);
    flag = positive;
  }
  else
  {
    if(less(num,rhs.num))
    {
      diff = Bigint::minus(rhs.num,num);
      flag = true;
    }
    else
    {
      diff = minus(num,rhs.num);
      flag = false;
    }
  }
  if(diff == "0")
    flag = true;
  return Bigint(diff,flag);
}

const string Bigint::multiply(const string& na,const string& nb)
{
  const string *pa(NULL),*pb(NULL);
  if(na.size() < nb.size())
  {
    pa = &nb;
    pb = &na;
  }
  else
  {
    pa = &na;
    pb = &nb;
  }
  const string &a(*pa),&b(*pb);
#ifdef _DEBUG
  cout << "mult " << a << " " << b << endl;
#endif
  string offset("");
  string res("0");
  for(int i = b.size() - 1;i >= 0;-- i)
  {
    string tmpres = "";
    int carry(0);
    int iterb = b[i] - '0';
    for(int j = a.size() - 1;j >= 0;-- j)
    {
      int itera = a[j] - '0';
      int product = itera * iterb + carry;
      carry = product / 10;
      tmpres = (char)(product % 10 + '0') + tmpres;
    }
    if(carry != 0)
      tmpres = (char)(carry + '0') + tmpres;
    tmpres += offset;
    tmpres = delprezero(tmpres);
#ifdef _DEBUG
    cout << a << " * " << iterb << "=" << tmpres << endl;
#endif
   res = add(res,tmpres);
    offset += "0";
  }
  return res;
}
const string Bigint::divide(const string& na,const string& nb)
{

  if(nb == "0")
      throw runtime_error("Divisor can not be 0!");
  string res("");
  if(na.size() < nb.size())
    return "0";
  string divided = na.substr(0,nb.size());
  for(int i = 0;i < na.size() - nb.size() + 1;++ i)
  {
#ifdef _DEBUG
    cout << "divided=" << divided << endl;
#endif
    int tmpquotient(1);
    string tmpproduct = nb;
    for(;less(tmpproduct,divided);tmpproduct = add(tmpproduct,nb),++tmpquotient);
    if(tmpproduct != divided)
    {
      -- tmpquotient;
      tmpproduct = minus(tmpproduct,nb);
    }
    res += (char)(tmpquotient + '0');
#ifdef _DEBUG
    cout << divided << "/" << nb << "=" << tmpquotient << endl;
#endif
    divided = minus(divided,tmpproduct);
    if(divided == "0")
      divided = na[nb.size() + i];
    else
      divided = divided + na[nb.size() + i];
  }
  return delprezero(res);
}
const Bigint Bigint::operator*(const Bigint& rhs) const
{
  bool p;
  p = !(positive ^ rhs.positive);
  string s = multiply(num,rhs.num);
  if(s == "0")
    p = true;
  return Bigint(s,p);
}
const Bigint Bigint::operator/(const Bigint& rhs) const
{
  bool p;
  p = !(positive ^ rhs.positive);
  string s = divide(num,rhs.num);
  if(s == "0")
    p = true;
  return Bigint(s,p);
}
const Bigint Bigint::operator%(const Bigint& rhs) const
{
  return (*this) - (*this / rhs) * rhs;
}

const Bigint Bigint::operator+=(const Bigint& rhs)
{
  *this = (*this) + rhs;
  return *this;
}

const Bigint Bigint::operator-=(const Bigint& rhs)
{
  *this = (*this) - rhs;
  return *this;
}

const Bigint Bigint::operator*=(const Bigint& rhs)
{
  *this = (*this) * rhs;
  return *this;
}

const Bigint Bigint::operator/=(const Bigint& rhs)
{
  *this = (*this) / rhs;
  return *this;
}

const Bigint Bigint::operator%=(const Bigint& rhs)
{
  *this = (*this) % rhs;
  return *this;
}
Bigint& Bigint::operator++()
{
  (*this) = (*this) + 1;
  return *this;
}

Bigint Bigint::operator++(int)
{
  Bigint ret(*this);
  (*this) = (*this) + 1;
  return ret;
}

Bigint& Bigint::operator--()
{
  (*this) = (*this) - 1;
  return *this;
}

Bigint Bigint::operator--(int)
{
  Bigint ret(*this);
  (*this) = (*this) - 1;
  return ret;
}

int Bigint::toint() const
{
  Bigint maxint(INT_MAX);
  if((*this) > INT_MAX)
    throw runtime_error("Too big to be int!");
  int res(0);
  for(int i = num.size() - 1;i >= 0;-- i)
    res = res * 10 + (num[i] - '0');
  return res;
}

/*
int main()
{
  srand(time(0));
  for(unsigned int i = 0;i < 0xffffffff;++ i)
  {
    int a = rand() % 10000 - 5000;
    int b = rand() % 10000 - 5000;
    if(b == 0)
      ++ b;
    Bigint aa(a),bb(b);
    if((Bigint)(a + b) != aa + bb || (Bigint)(a - b) != aa - bb || (Bigint)(a * b) != aa * bb ||(Bigint)(a / b) != aa / bb || (Bigint)(a % b) != aa % bb)
    {
      cout << "a=" << a << "\t" << "b=" << b << "\t###\t";
      cout << "aa=" << aa << "\t" << "bb=" << bb << endl;
      cout << "a+b=" << a + b << "\t" << "aa+bb=" << aa + bb << endl;
      cout << "a-b=" << a - b << "\t" << "aa-bb=" << aa - bb << endl;
      cout << "a*b=" << a * b << "\t" << "aa*bb=" << aa * bb << endl;
      cout << "a/b=" << a / b << "\t" << "aa/bb=" << aa / bb << endl;
      cout << "a%b=" << a % b << "\t" << "aa%bb=" << aa % bb << endl;
      break;
    }
    else
    {
      cout << i << endl;
    }
  }
}
*/
