#include<iostream>
#include<vector>
#include<queue>
#include<fstream>
using namespace std;
struct Node
{
	int num;
	Node* left;
	Node* right;
};
Node* get_tree(vector<int>& post_seq,vector<int>& in_seq,int b1,int e1,int b2,int e2)
{
	if(b1 > e1 || b2 > e2)
		return NULL;
	else
	{
		Node* n = new Node();
		n->num = post_seq[e1];
		int index;
		for(int i = b2;i <= e2; ++ i)
		{
			if(n->num == in_seq[i])
			{
				index = i;
				break;
			}
		}
		n->left = get_tree(post_seq,in_seq,b1,b1 + index - b2 - 1,b2,index - 1);
		n->right = get_tree(post_seq,in_seq,b1 + index - b2,e1 - 1,index + 1,e2);
		return n;
	}
}
void level_travel(Node* r,vector<int>& lev_seq)
{
	queue<Node*> tmp;
	tmp.push(r);
	while(!tmp.empty())
	{
		Node* n = tmp.front();
		lev_seq.push_back(n->num);
		if(n->left != NULL)
			tmp.push(n->left);
		if(n->right != NULL)
			tmp.push(n->right);
		delete n;
		tmp.pop();
	}
}
int main()
{
	int n;
	cin >> n;
	vector<int> post_seq,in_seq,lev_seq;
	for(int i = 0;i < n;++ i)
	{
		int t;
		cin >> t;
		post_seq.push_back(t);
	}	
	for(int i = 0;i < n;++ i)
	{
		int t;
		cin >> t;
		in_seq.push_back(t);
	}	
	Node* root = get_tree(post_seq,in_seq,0,post_seq.size() - 1,0,in_seq.size() - 1);
	level_travel(root,lev_seq);	
	vector<int>::iterator it;
	for(it = lev_seq.begin();it != lev_seq.end();++ it)
	{
		cout << *it;
		if(it != (lev_seq.end() - 1))
			cout << " ";
	}
}
