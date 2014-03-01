#include <cstdio>
#include <cstring>
#define MAX 100000
typedef char STR[6];
inline int string2int(STR s)
{
	int r(0);
	for(size_t i = 0;i < 5;++ i)
		r = r * 10 + s[i] - '0';
	return r;
}
int main()
{
	STR b1,b2;
	int n;
	int index;
	scanf("%s %s %d",b1,b2,&n);
	STR* hash = new STR[MAX];
	for(int i = 0;i < n;++ i)
	{
		STR t1,t2;
		char c;
		scanf("%s %c %s",t1,&c,t2);
		index = string2int(t1);
		strcpy(hash[index],t2);
	}
	bool* w = new bool[MAX];
	bool flag(false);
	while(strcmp(b1,"-1") != 0 || strcmp(b2,"-1") != 0)
	{
		if(strcmp(b1,"-1") != 0)
		{
			index = string2int(b1);
			if(w[index] == true)
			{
				flag = true;
				break;
			}
			else
				w[index] = true;
			strcpy(b1,hash[index]);
		}
		if(strcmp(b2,"-1") != 0)
		{
			index = string2int(b2);
			if(w[index] == true)
				break;
			else
				w[index] = true;
			strcpy(b2,hash[index]);
		}
	}
	if(true == flag)
		printf("%s",b1);
	else
		printf("%s",b2);
}