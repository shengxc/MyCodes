#include <iostream>
#include <vector>
#include <map>
#include <queue>
#include <algorithm>
#include <cstdio>
#include <cstdlib>
using namespace std;
enum type{BST,BSTMIR,OTHER};
struct Node
{
	Node(int n,Node* l = NULL,Node* r = NULL):num(n),left(l),right(r){}
	int num;
	Node* left;
	Node* right;
};
bool isbstpre(const vector<int>& v,int a,int b)
{
	if (a > b)
		return true;
	int idx;
	for (idx = a + 1;idx <= b;++ idx)
		if (v[idx] >= v[a])
			break;
	for (int i = idx + 1;i <= b;++ i)
		if (v[i] < v[a])
			return false;
	if (isbstpre(v,a + 1,idx - 1) && isbstpre(v,idx + 1,b))
		return true;
	else
		return false;
}
bool isbstmirpre(const vector<int>& v,int a,int b)
{
	if (a > b)
		return true;
	int idx;
	for (idx = a + 1;idx <= b;++ idx)
		if (v[idx] < v[a])
			break;
	for (int i = idx + 1;i <= b;++ i)
		if (v[i] >= v[a])
			return false;
	if (isbstmirpre(v,a + 1,idx - 1) && isbstmirpre(v,idx + 1,b))
		return true;
	else
		return false;
}
type gettype(const vector<int>& v)
{
	if (isbstpre(v,0,v.size() - 1))
		return BST;
	else if(isbstmirpre(v,0,v.size() - 1))
		return BSTMIR;
	else
		return OTHER;
}
Node* getbst(vector<int>& v,int a,int b)
{
	if (a > b)
		return NULL;
	int idx;
	for (idx = a + 1;idx <= b;++ idx)
		if (v[idx] >= v[a])
			break;
	Node* root = new Node(v[a],getbst(v,a + 1,idx - 1),getbst(v,idx,b));
	return root;
}
Node* getbstmir(vector<int>& v,int a,int b)
{
	if (a > b)
		return NULL;
	int idx;
	for (idx = a + 1;idx <= b;++ idx)
	{
		if (v[idx] < v[a])
			break;
	}
	Node* root = new Node(v[a],getbstmir(v,a + 1,idx - 1),getbstmir(v,idx,b));
	return root;
}
Node* gettreeroot(vector<int>& v)
{
	type t = gettype(v);
	switch(t)
	{
	case BST:
		return getbst(v,0,v.size() - 1);
	case BSTMIR:
		return getbstmir(v,0,v.size() - 1);
	case OTHER:
		return NULL;
	}
}
void posttravel(Node* root,Node* last)
{
	if (root == NULL)
		return;
	posttravel(root->left,last);
	posttravel(root->right,last);
	cout << root->num;
	if (root != last)
		cout << " ";
}
int main()
{
	freopen("input.txt","r",stdin);
	int n;
	cin >> n;
	vector<int> v;
	for(int i = 0;i < n;++ i)
	{
		int tmp;
		cin >> tmp;
		v.push_back(tmp);
	}
	Node* root = gettreeroot(v);
	if (root == NULL)
	{
		cout << "NO" << endl;
	}
	else
	{
		cout << "YES" << endl;
		posttravel(root,root);
	}
}
