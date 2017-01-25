#include <iostream>
#include "AvlTree.h"
#include <algorithm>
#include <queue>
#include <vector>
#include <iomanip>
using namespace std;

AvlTree::~AvlTree()
{
	makeEmpty();//释放所有结点
	root = NULL;
}

AvlTree & AvlTree::operator=(const AvlTree & rhs)
{
	if (this != &rhs)
	{
		makeEmpty();//全部清空
		clone(rhs.root);
	}
	return *this;
}

void AvlTree::makeEmpty()
{
	makeEmpty(root);
}
void AvlTree::makeEmpty(AvlNode *& root)
{
	if (root != NULL)
	{
		makeEmpty(root->left);
		makeEmpty(root->right);

		delete root;
	}
}


int AvlTree::height()
{
	return height(root);
}
int & AvlTree::findMin()
{
	return findMin(root);
}
int & AvlTree::findMax()
{
	return findMax(root);
}
int AvlTree::height(AvlNode * root)
{
	return root == NULL ? -1 : root->height;
}


void AvlTree::insert(const int & element)
{
	insert(element, root);
}
void AvlTree::insert(const int & element, AvlNode *& root)
{
	if (root == NULL)
	{
		root = new AvlNode(element, NULL, NULL);
	}
	else if (element < root->element)
	{
		insert(element, root->left);//插入元素

		if (height(root->left) - height(root->right) == 2)//判断是否失去平衡
		{
			//再判断是单旋转还是双旋转
			if (element < root->left->element)//说明是左子树的左插入
			{
				//进行左左单旋转
				rotateWithLeftChild(root);
			}
			else
			{
				//进行左右双旋转 
				doubleWithRightChild(root);
			}
		}
	}
	else if (element > root->element)
	{
		insert(element, root->right);
		if (height(root->right) - height(root->left) == 2)//向右插入元素后，会增加右边的深度，所以会右失衡
		{
			if (element > root->right->element)
			{
				//右右深度增加
				rotateWithRightChild(root);
			}
			else
			{
				doubleWithLeftChild(root);
			}
		}
	}

	root->height = max(height(root->left), height(root->right)) + 1;
}

void AvlTree::remove(const int & element)
{
	if (root != NULL)
	{
		//不为空才能删除
		remove(element, root);
	}
}
void AvlTree::remove(const int & element, AvlNode *& root)
{
	if (root != NULL)
	{
		if (element < root->element)
		{
			remove(element, root->left);
			root->height = max(height(root->left), height(root->right)) + 1;//更新高度

		}
		else if (element > root->element)
		{
			remove(element, root->right);
			root->height = max(height(root->left), height(root->right)) + 1;//更新高度

		}
		else//此时已经找到 要删除的元素 
		{
			//三种情况：该删除元素的两个孩子都为空，一个为空，两个都不空（最复杂）
			if (root->left != NULL && root->right != NULL)//两个都不为空
			{
				root->element = findMin(root->right);//找右边子树的最小值

				remove(root->element, root->right);
			}
			else//要么两个都为空，有一个为空
			{
				AvlNode *oldNode = root;//保存
				root = root->left == NULL ? root->right : root->left;
				delete oldNode;
			}
		}
	}
}

int & AvlTree::findMin(AvlNode * root)
{
 	if (root->left == NULL)
	{
		return root->element;
	}
	else
	{
		return findMin(root->left);
	}
}

int & AvlTree::findMax(AvlNode * root)
{
	if (root->right == NULL)
	{
		return root->element;
	}
	else
	{
		return findMax(root->right);
	}
}

//四个旋转函数
void AvlTree::rotateWithLeftChild(AvlNode *& root)
{
	AvlNode *temp = root->left;
	root->left = temp->right;
	temp->right = root;
	root->height = max(height(root->left), height(root->right)) + 1;
	temp->height = max(height(temp->left), root->height) + 1;
	root = temp;
}
void AvlTree::rotateWithRightChild(AvlNode *& root)
{
	AvlNode *temp = root->right;
	root->right = temp->left;
	temp->left = root;

	root->height = max(height(root->left), height(root->right)) + 1;
	temp->height = max(height(temp->right), root->height) + 1;
	root = temp;
}

void AvlTree::doubleWithRightChild(AvlNode *& root)
{
	rotateWithRightChild(root->left);//对左孩子进行右单旋转
	rotateWithLeftChild(root);//现在已经成了左左状态，直接进行左左单旋转
}

void AvlTree::doubleWithLeftChild(AvlNode *& root)
{
	rotateWithLeftChild(root->right);
	rotateWithRightChild(root);
}

void AvlTree::print()
{
	print(root);
}
void AvlTree::print(AvlNode * root)
{
	int h = 0;
	vector<AvlNode*> v;
	int cnt = 0;
	bfs(v, root);//直接用一个v，免得要进行vector的额外赋值操作
	h = root->height+1;

	for (int i = 1; i <= h; ++i)
	{
		putBlank((1<<(h-i + 1))/2);
		for (int k = 0; k < (1 << (i - 1)); ++k)
		{
			if (v[cnt])
			{
				cout << setw(2) << v[cnt]->element;
			}
			else
			{
				cout << "  ";
			}
			putBlank((1 << (h - i + 1)) / 2);
			cnt++;
		}
		putchar('\n');
	}
}

void AvlTree::bfs(vector<AvlNode*>& v, AvlNode * root)
{
	AvlNode *a;
	queue<AvlNode*> q;//存放结点的指针的队列
	int cnt = 0;//计算结点个数

	if (root)//如果不为空
	{
		//计算高度后得到最多结点个数
		cnt = (1 << (root->height+1)) - 1;//对1 移位运运算////////////////
		q.push(root);//根结点入队

		while (v.size() != cnt)
		{
			a = q.front();//获取队列的队首
			q.pop();
			v.push_back(a);

			if (a != NULL)//如果a不为空
			{
				q.push(a->left);
				q.push(a->right);
			}
			else
			{
				q.push(NULL);
				q.push(NULL);
			}
		}
	}
}

void AvlTree::putBlank(int h)
{
	while (h--)
	{
		putchar(' ');
	}
}
