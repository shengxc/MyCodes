# include <stdio.h>
# include <string.h>
# include <vector>
# include <algorithm>
using namespace std;
struct stu{
	char id[10];
	char name[10];
	int score;
};
typedef struct stu Stu;
bool comp1(Stu a,Stu b)
{
	if(strcmp(a.id,b.id) < 0)
		return true;
	else
		return false;
}
bool comp2(Stu a,Stu b)
{
	if(strcmp(a.name,b.name) < 0)
		return true;
	else
	{
		if(strcmp(a.name,b.name) == 0)
		{
			if(strcmp(a.id,b.id) < 0)
				return true;
			else
				return false;
		}
		else
			return false;
	}
}
bool comp3(Stu a,Stu b)
{
	if(a.score < b.score)
		return true;
	else
	{
		if(a.score == b.score)
		{
			if(strcmp(a.id,b.id) < 0)
				return true;
			else
				return false;
		}
		else
			return false;
	}
}
int main(){
	int n,col;
	scanf("%d%d",&n,&col);
	int i;
	Stu s;
	vector<Stu> list;
	for(i = 0;i < n;++ i){
		scanf("%s%s%d", s.id, s.name,&s.score);		
		list.push_back(s);
	}
	switch(col)
	{
	case 1:
		sort(list.begin(),list.end(),comp1);
		break;
	case 2:
		sort(list.begin(),list.end(),comp2);
		break;
	case 3:
		sort(list.begin(),list.end(),comp3);
		break;
	}
	for(i=0;i<n;i++){
		printf("%s %s %d",list[i].id,list[i].name,list[i].score);
		if(i != (n-1))
			printf("\n");
	}
	return 0;
}