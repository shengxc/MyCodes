#include <iostream>
#include <cstring>
using namespace std;
const int MAX_NUM = 501;
int main()
{
  int n,m;
  cin >> n >> m;
  int hash_table[MAX_NUM];
  memset(hash_table,0,sizeof(int) * MAX_NUM);
  for(int i = 0;i < n;++ i)
  {
    int tmp;
    cin >> tmp;
    ++ hash_table[tmp];
  }
  for(int i = 0;i < MAX_NUM;++ i)
  {
    if(hash_table[i] != 0)
    {
      int dst = m - i;
      if(dst < 0 || dst > MAX_NUM - 1)
        continue;
      -- hash_table[i];
      if(hash_table[dst] != 0)
      {
        cout << i << " "<< dst;
        return 0;
      }
      ++ hash_table[i];
    }
  }
  cout << "No Solution";
}
