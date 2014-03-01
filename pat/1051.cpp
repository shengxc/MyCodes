#include <iostream>
#include <stack>
#include <cassert>
using namespace std;
int main()
{
  int m,n,k;
  cin >> m >> n >> k;
  for(int i = 0;i < k;++ i)
  {
    stack<int> stack;
    assert(stack.size() == 0);
    int cur(1);
    bool state(true);
    int j;
    for(j = 0;j < n;++ j)
    {
      int num;
      cin >> num;
      if(cur > n + 1)
      {
        state = false;
        break;
      }
      if(num >= cur)
      {
        for(int k = cur;k < num + 1;++ k)
          stack.push(k);
        if(stack.size() > m)
        {
          state = false;
          break;
        }
        stack.pop();
        cur = num + 1;
      }
      else
      {
        if(stack.size() == 0 || stack.top() != num)
        {
          state = false;
          break;
        }
        stack.pop();
      }
    }
    for(;j < n - 1;++ j)
    {
      int tmp;
      cin >> tmp;
    }
    if(state == true)
      cout << "YES\n";
    else
      cout << "NO\n";
  }
}
