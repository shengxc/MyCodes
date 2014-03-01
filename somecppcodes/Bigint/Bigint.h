#include <string>
#include <iostream>
using namespace std;
class Bigint
{
public:
  Bigint(int i = 0);
  // compare
  const bool operator<(const Bigint& rhs) const;
  const bool operator==(const Bigint& rhs) const;
  const bool operator<=(const Bigint& rhs) const;
  const bool operator>(const Bigint& rhs) const;
  const bool operator>=(const Bigint& rhs) const;
  const bool operator!=(const Bigint& rhs) const;
  // caculate
  const Bigint operator+(const Bigint& rhs) const;
  const Bigint operator-(const Bigint& rhs) const;
  const Bigint operator*(const Bigint& rhs) const;
  const Bigint operator/(const Bigint& rhs) const;
  const Bigint operator%(const Bigint& rhs) const;
  const Bigint operator+=(const Bigint& rhs);
  const Bigint operator-=(const Bigint& rhs);
  const Bigint operator*=(const Bigint& rhs);
  const Bigint operator/=(const Bigint& rhs);
  const Bigint operator%=(const Bigint& rhs);
  Bigint& operator++();
  Bigint operator++(int);
  Bigint& operator--();
  Bigint operator--(int);
  // IO
  friend istream& operator>>(istream& is,Bigint& rhs);
  friend ostream& operator<<(ostream& os,const Bigint& rhs);
  // other
  int toint() const;
private:
  bool positive;
  string num;
private:
  // some useful functions
  Bigint(const string& s,const bool& p) : num(s),positive(p){}
  static int extend(string& a,string& b);//extend the shorter number to equal to the longer,return their length
  static const string add(const string& na,const string& nb);// add two positive int numbers;
  static const string minus(const string& na,const string& nb);// minus two positive int numbers and it requires numa >= numb;
  static const string multiply(const string& na,const string& nb);// multiply two positive numbers
  static const string divide(const string& na,const string& nb);// divide two positive numbers
  static const bool less(const string& numa,const string& numb);// compare two positive numbers
  inline static string delprezero(const string& s);// delete previous zeros
};
istream& operator>>(istream& is,Bigint& rhs);
ostream& operator<<(ostream& os,const Bigint& rhs);
