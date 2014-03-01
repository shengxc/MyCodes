#include<iostream>
#include<fstream>
#include<hash_map>
#include<string>
#include<sstream>
#include<algorithm>
using namespace std;
using namespace __gnu_cxx;
struct str_hash//哈希函数对象
{
	size_t operator()(const string& str) const
	{
		unsigned long __h = 0;
		for(size_t i = 0;i < str.size();++ i)
			__h = 5 * __h + str[i];
		return size_t(__h);
	}
};
int main()
{
	vector<string> num;//存储每个序号
	hash_multimap<string,int,str_hash> title,author,keywords,publisher,year; //存储搜索项到序号的hash
	string x,t,a,k,p,y;
	int n;
	string dustbin;
	cin >> n;
	getline(cin,dustbin);
	for(int i = 0;i < n;++ i)
	{
		getline(cin,x);
		getline(cin,t);
		getline(cin,a);
		getline(cin,k);
		getline(cin,p);
		getline(cin,y);			
		num.push_back(x);
		title.insert(make_pair(t,i));
		author.insert(make_pair(a,i));
		publisher.insert(make_pair(p,i));
		year.insert(make_pair(y,i));
		size_t pos1 = 0;
		size_t pos2 = 0;
		while(pos2 != string::npos)
		{
			pos2 = k.find(' ',pos1);
			string tmp = k.substr(pos1,pos2 - pos1);
			pos1 = pos2 + 1;
			keywords.insert(make_pair(tmp,i));
		}
	}
	cin >> n;
	getline(cin,dustbin);   
	vector<string> query;
	for(int i = 0;i < n;++ i)
	{
		string tmp;
		getline(cin,tmp);
		query.push_back(tmp);
	}
	vector<string> result;
	ostringstream os;
	for(size_t i = 0;i < query.size();++ i)
	{
		result.clear();
		os << query[i] << endl;
		int count;
		char c = (query[i])[0];
		string s = (query[i]).substr(3);
		hash_multimap<string,int,str_hash>::iterator it;
		switch(c)
		{
		case '1':
			count = title.count(s);
			it = title.find(s);
			if(count > 0)
				for(int j = 0;j < count;++ j)
				{
					result.push_back(num[it->second]);
					++ it;
				}
			if(result.size() > 0)
			{
				sort(result.begin(),result.end());
				for(size_t j = 0;j < result.size();++ j)
				{
					os << result[j];
					if(!((j == result.size() - 1) && (i == query.size() - 1)))
						os << endl;
				}
			}
			else
			{
				os << "Not Found";
				if(i != query.size() - 1)
					os << endl;
			}
			break;
		case '2':
			count = author.count(s);
			it = author.find(s);
			if(count > 0)
				for(int j = 0;j < count;++ j)
				{
					result.push_back(num[it->second]);
					++ it;
				}
			if(result.size() > 0)
			{
				sort(result.begin(),result.end());
				for(size_t j = 0;j < result.size();++ j)
				{
					os << result[j];
					if(!((j == result.size() - 1) && (i == query.size() - 1)))
						os << endl;
				}
			}
			else
			{
				os << "Not Found";
				if(i != query.size() - 1)
					os << endl;
			}
			break;
		case '3':
			count = keywords.count(s);
			it = keywords.find(s);
			if(count > 0)
				for(int j = 0;j < count;++ j)
				{
					result.push_back(num[it->second]);
					++ it;
				}
			if(result.size() > 0)
			{
				sort(result.begin(),result.end());
				for(size_t j = 0;j < result.size();++ j)
				{
					os << result[j];
					if(!((j == result.size() - 1) && (i == query.size() - 1)))
						os << endl;
				}
			}
			else
			{
				os << "Not Found";
				if(i != query.size() - 1)
					os << endl;
			}
			break;
		case '4':
			count = publisher.count(s);
			it = publisher.find(s);
			if(count > 0)
				for(int j = 0;j < count;++ j)
				{
					result.push_back(num[it->second]);
					++ it;
				}
			if(result.size() > 0)
			{
				sort(result.begin(),result.end());
				for(size_t j = 0;j < result.size();++ j)
				{
					os << result[j];
					if(!((j == result.size() - 1) && (i == query.size() - 1)))
						os << endl;
				}
			}
			else
			{
				os << "Not Found";
				if(i != query.size() - 1)
					os << endl;
			}
			break;
		case '5':
			count = year.count(s);
			it = year.find(s);
			if(count > 0)
				for(int j = 0;j < count;++ j)
				{
					result.push_back(num[it->second]);
					++ it;
				}
			if(result.size() > 0)
			{
				sort(result.begin(),result.end());
				for(size_t j = 0;j < result.size();++ j)
				{
					os << result[j];
					if(!((j == result.size() - 1) && (i == query.size() - 1)))
						os << endl;
				}
			}
			else
			{
				os << "Not Found";
				if(i != query.size() - 1)
					os << endl;
			}
			break;
		default:
			cout << "Not Found";
			if(i != query.size() - 1)
				cout << endl;
			break;
		}
	}
	cout << os.str();
}