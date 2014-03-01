#include <iostream>
#include <fstream>
#include <vector>
using namespace std;
long find_recursion(long* v1,long b1,long e1,long* v2,long b2,long e2,long num)
{
  if(e1 < b1)
    return v2[b2 + num - 1];
  if(e2 < b2)
    return v1[b1 + num - 1];
  long m1 = (b1 + e1) / 2;
  long m2 = (b2 + e2) / 2;
  if(v1[m1] <= v2[m2])
  {
    if(num <= m1 - b1 + 1 + m2 - b2)
      return find_recursion(v1,b1,e1,v2,b2,m2 - 1,num);
    else
      return find_recursion(v1,m1 + 1,e1,v2,b2,e2,num - (m1 - b1 + 1));
  }
  else
  {
    if(num <= m2 - b2 + 1 + m1 - b1)
      return find_recursion(v1,b1,m1 - 1,v2,b2,e2,num);
    else
      return find_recursion(v1,b1,e1,v2,m2 + 1,e2,num - (m2 - b2 + 1));
  }
}

long find(long* v1,long* v2,int n1,int n2,long num)//寻找第num小的数
{
  return find_recursion(v1,0,n1 - 1,v2,0,n2 - 1,num);
}
int main()
{
  int n1,n2;
  scanf("%d",&n1);
  long* v1 = new long[n1];
  for(long i = 0;i < n1;++ i)
    scanf("%ld",v1 + i);
  scanf("%d",&n2);
  long* v2 = new long[n2];
  for(long i = 0;i < n2;++ i)
    scanf("%ld",v2 + i);
  long value = find(v1,v2,n1,n2,(n1 + n2 + 1) / 2);
  cout << value;
}