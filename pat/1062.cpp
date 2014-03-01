#include <iostream>
#include <cstring>
#include <vector>
#include <algorithm>
using namespace std;
const int MAX_PEOPLE = 100000;
struct person
{
	char id[9];
	int v;
	int t;
	int tag;
};
int comp(const void* a,const void* b)
{
	person* x = (person*) a;
	person* y = (person*) b;
	if (x->tag > y->tag)
		return -1;
	else if (x->tag == y->tag)
	{
		if (x->v + x->t > y->v + y->t)	
			return -1;
		else if (x->v + x->t == y->v + y->t)
		{
			if (x->v > y->v)
				return -1;
			else if (x->v == y->v)
			{
				if (strcmp(x->id,y->id) < 0)
					return -1;
				else
					return 1;
			}
			else
				return 1;
		}
		else
			return 1;

	}
	else
		return 1;
}
int main()
{
	int n,l,h;
	int size(0);
	scanf("%d %d %d",&n,&l,&h);
	person* people = new person[MAX_PEOPLE];
	for (int i = 0;i < n;++ i)
	{
		scanf("%s %d %d",&people[size].id,&people[size].v,&people[size].t);
		if (people[size].v < l || people[size].t < l)
			continue;
		if (people[size].v >= h && people[size].t >= h)
			people[size].tag = 4;
		else if(people[size].v >= h && people[size].t < h)
			people[size].tag = 3;
		else if(people[size].v < h && people[size].t < h && people[size].v >= people[size].t)
			people[size].tag = 2;
		else
			people[size].tag = 1;
		++ size;
	}
	qsort(people,size,sizeof(person),comp);
	printf("%d\n",size);
	for (int i = 0;i < size;++ i)
		printf("%s %d %d\n",people[i].id,people[i].v,people[i].t);
	delete[] people;
}