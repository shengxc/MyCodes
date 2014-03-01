#include <iostream>
#include <string>
#include <vector>
using namespace std;
struct student
{
	string name;
	char gender;
	string id;
	int grade;
};
int main()
{
	student *minm(NULL), *maxf(NULL);
	int n;
	cin >> n;
	int max(-1),min(101);
	for (int i = 0;i < n;++ i)
	{
		student s;
		cin >> s.name >> s.gender >> s.id >> s.grade;
		if (s.gender == 'M')
		{
			if(s.grade < min)
			{
				min = s.grade;
				if(minm == NULL)
					minm = new student(s);
				else
					*minm = s;
			}
		}
		if (s.gender == 'F')
		{
			if (s.grade > max)
			{
				max = s.grade;
				if (maxf == NULL)
					maxf = new student(s);
				else
					*maxf = s;
			}
		}
	}
	bool na = false;
	if (maxf != NULL)
		cout << maxf->name << " " << maxf->id << endl;
	else
	{
		cout << "Absent" << endl;
		na = true;
	}
	if (minm != NULL)
		cout << minm->name << " " << minm->id << endl;
	else
	{
		cout << "Absent" << endl;
		na = true;
	}
	if(na)
		cout << "NA";
	else
		cout << maxf->grade - minm->grade;
}