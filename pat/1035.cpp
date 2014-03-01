#include <iostream>
#include <string>
#include <vector>
using namespace std;
struct user
{
	string username;
	string pwd;
	bool operator== (const user& rhs) const
	{
		if (pwd == rhs.pwd)
			return true;
		else
			return false;
	}
};
user change(const user& u)
{
	user res(u);
	for (int i = 0;i < res.pwd.size();++ i)
	{
		switch(res.pwd[i])
		{
		case '1':
			res.pwd[i] = '@';
			break;
		case '0':
			res.pwd[i] = '%';
			break;
		case 'l':
			res.pwd[i] = 'L';
			break;
		case 'O':
			res.pwd[i] = 'o';
			break;
		default:
			break;
		}
	}
	return res;
}
int main()
{
	int n;
	vector<user> users;
	cin >> n;
	for (int i = 0;i < n;++ i)
	{
		user u;
		cin >> u.username >> u.pwd;
		users.push_back(u);
	}
	vector<user> res;
	for (int i = 0;i < n;++ i)
	{
		user u = change(users[i]);
		if (!(u == users[i]))
			res.push_back(u);
	}
	if (res.size() == 0)
		if (users.size() == 1)		
			cout << "There is 1 account and no account is modified";
		else
			cout << "There are " << users.size() << " accounts and no account is modified";
	else
	{
		cout << res.size() << endl;
		for (int i = 0;i < res.size(); ++ i)
			cout << res[i].username << " " << res[i].pwd << endl;
	}
}