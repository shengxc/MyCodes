#include <iostream>
#include <string>
#include <cstdio>
#include <sstream>
using namespace std;
//cut or extend to significant
string edittosig(string s,int sig)
{
  if(sig > s.size())
  {
    int delta = sig - s.size();
    for(int i = 0;i < delta;++ i)
      s += "0";
  }
  else
    s = s.substr(0,sig);
  return s;
}
//delete useless 0 and add .
string standard(string s)
{
  if(s[0] == '.')
    s = "0" + s;
  int firstnzero = s.find_first_not_of("0");
  if(firstnzero == string::npos)
    return "0.";
  //delete pre zero
  if(s[firstnzero] != '.')
    s = s.substr(firstnzero);
  else
    s = s.substr(firstnzero - 1);
  // add .
  if(s.find(".") == string::npos)
    s = s + ".";
  //delete post zero
  s = s.erase(s.find_last_not_of("0") + 1);
  return s;
}
//change to scientific notation
string normalize(string num,int sig)
{
  num = standard(num);
  //calculate exponent
  int exp(0);
  if(num == "0.")
    exp = 0;
  else
  {
    int potidx = num.find(".");
    int nzeroidx = num.find_first_not_of("0.");
    if(num[0] == '0')
      exp = potidx - nzeroidx + 1;
    else
      exp = potidx - nzeroidx;
  }
  if(num.find_first_not_of(".0") == string::npos)
    num = "";
  else
    num = num.substr(num.find_first_not_of(".0"));
  if(num.find(".")!=string::npos)
    num = num.erase(num.find("."),1);
  //add zero to the last of string or delete reduntant numbers
  num = edittosig(num,sig);
  //format string
  string normalizednum;
  ostringstream formatstr;
  formatstr << "0." << num << "*10^" << exp;
  return formatstr.str();
}
int main()
{
  int n;
  string a,b;
  cin >> n;
  cin >> a >> b;
  string na = normalize(a,n);
  string nb = normalize(b,n);
  if(na == nb)
    cout << "YES " << na;
  else
    cout << "NO " << na << " " << nb;
 }
