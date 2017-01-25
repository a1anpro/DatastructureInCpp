#pragma once
#include <iostream>
#include <queue>
#include <vector>
using namespace std;

class AvlTree
{
public:
	//四大件
	AvlTree() 
	{
		root = NULL;//构造直接为空
	}
	AvlTree(const AvlTree &rhs)
	{
		root = NULL;//关键
		*this = rhs;
	}
	AvlTree& operator= (const AvlTree& rhs);
	~AvlTree();

	void makeEmpty();//释放所有结点的外部函数
	int height();//height只有在insert和remove之后才会有变化

	int& findMin();
	int& findMax();
	void insert(const int &element);
	void remove(const int &element);
	void print();//打印
private:
	struct AvlNode
	{
		int element;
		AvlNode *left;
		AvlNode *right;
		int height;

		AvlNode(const int &element, AvlNode *left, AvlNode *right, int height = 0)
			:element(element), left(left), right(right), height(height) {}
	};

	//成员区域
	AvlNode *root;//树根

	//函数区域
	static void makeEmpty(AvlNode *&root);
	static int height(AvlNode *root);
	static void insert(const int &element, AvlNode *&root);
	static void remove(const int &element, AvlNode *&root);//因为要修改所以是指针的引用

	static int& findMin(AvlNode *root);
	static int& findMax(AvlNode *root);

	//四个旋转函数
	static void rotateWithLeftChild(AvlNode *&root);//左左
	static void rotateWithRightChild(AvlNode *&root);//右右
	static void doubleWithRightChild(AvlNode *&root);//左右
	static void doubleWithLeftChild(AvlNode *&root);//右左

	//打印函数
	static void print(AvlNode *root);//内部打印函数
	static void bfs(vector<AvlNode*>& v, AvlNode *root);
	static void putBlank(int h);
	AvlNode* clone(AvlNode *rhs) const//内部使用的函数
	{
		if (rhs == NULL)
		{
			return NULL;//如果rhs为空，直接返回空
		}

		return new AvlNode(rhs->element, clone(rhs->left), clone(rhs->right));
	}
};
