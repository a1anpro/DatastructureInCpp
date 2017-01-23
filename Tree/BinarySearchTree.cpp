#pragma once
//要修改就传指针，不修改就传副本
#include <iostream>
#include <algorithm>
using namespace std;

template<typename Comparable>
class BinarySearchTree
{
public:
	BinarySearchTree();
	BinarySearchTree(const BinarySearchTree<Comparable>& rhs);
	~BinarySearchTree();

	const Comparable& findMax() const;
	const Comparable& findMin() const;

	int height() const;
	bool contains(const Comparable& x) const;//包含某元素
	bool isEmpty() const;//判断树是否为空
	
	void printTree() const//打印树
	{

	}

	void makeEmpty();//置空
	
	void insert(const Comparable& x);
	
	void remove(const Comparable& x);
	
	
	const BinarySearchTree<Comparable>& operator=(const BinarySearchTree<Comparable> &rhs);
	
private:
	struct BinaryNode{
		Comparable element;
		BinaryNode *left;
		BinaryNode *right;

		int theHeight;//添加一个结点高度

		//BinaryNode(const Comparable &theElement) {}
		BinaryNode(const Comparable &theElement, BinaryNode *lt, BinaryNode *rt)//
			: element(theElement), left(lt), right(rt) {
			theHeight = 0;//默认为0
		}
	};

	BinaryNode *root;//树根

	int height(BinaryNode *root) const;
	
	bool contains(const Comparable& x, BinaryNode *root) const;//内部函数，不对外部开放

	void insert(const Comparable& x, BinaryNode *&root);//内部插入函数
	
	void remove(const Comparable& x, BinaryNode *&root);//内部删除函数
	void makeEmpty(BinaryNode *&root);

	BinaryNode* clone(BinaryNode *root) const//申请每个元素空间 并赋值
	{
		if (root == NULL)
		{
			return NULL;
		}

		return new BinaryNode(root->element, clone(root->left), clone(root->right));
	}
	BinaryNode* findMin(BinaryNode *root) const
	{
		if (root == NULL)
		{
			return NULL;
		}
		if (root->left == NULL)
		{
			return root;
		}

		return findMin(root->left);
	}
	BinaryNode* findMax(BinaryNode *root) const;
	
};


template<typename Comparable>
BinarySearchTree<Comparable>::BinarySearchTree()
{
	root = NULL;//最开始构造的时候就要把它构造成空
}

template<typename Comparable>
BinarySearchTree<Comparable>::BinarySearchTree(const BinarySearchTree<Comparable>& rhs)
{
	*this = rhs;//直接调用赋值函数
}

template<typename Comparable>
BinarySearchTree<Comparable>::~BinarySearchTree()
{
	makeEmpty();//析构只用释放所有结点空间
}

template<typename Comparable>
const Comparable & BinarySearchTree<Comparable>::findMax() const
{
	return findMax(root);
}

template<typename Comparable>
const Comparable & BinarySearchTree<Comparable>::findMin() const
{
	return findMin(root);//递归调用,(对root的改变是安全的，因为我们值用指针的副本来进行工作
}

template<typename Comparable>
int BinarySearchTree<Comparable>::height() const
{
	return height(root);
}

template<typename Comparable>
bool BinarySearchTree<Comparable>::contains(const Comparable & x) const
{
	return contains(x, root);
	return false;
}

template<typename Comparable>
bool BinarySearchTree<Comparable>::isEmpty() const
{
	return root == NULL;//
}

template<typename Comparable>
void BinarySearchTree<Comparable>::makeEmpty()
{
	makeEmpty(root);//我们要修改的话就要用 “指针的引用”
}

template<typename Comparable>
void BinarySearchTree<Comparable>::insert(const Comparable & x)
{
	insert(x, root);
}

template<typename Comparable>
void BinarySearchTree<Comparable>::remove(const Comparable & x)
{
	remove(x, root);
}

template<typename Comparable>
const BinarySearchTree<Comparable>& BinarySearchTree<Comparable>::operator=(const BinarySearchTree<Comparable>& rhs)
{
	//if (this != &rhs)//如果不是指向一个对象
	{
		makeEmpty();//释放原对象
		root = clone(rhs.root);
	}
}

template<typename Comparable>
int BinarySearchTree<Comparable>::height(BinaryNode * root) const
{
	if (root != NULL)
	{
		return root->theHeight;
	}
	return 0;
}

template<typename Comparable>
bool BinarySearchTree<Comparable>::contains(const Comparable & x, BinaryNode * root) const
{
	if (root == NULL)//如果树为空就返回false
	{
		return false;
	}
	else if (x < root->element)
	{
		return contains(x, root->left);
	}
	else if (x > root->element)
	{
		return contains(x, root->right);
	}
	else return true;
}

template<typename Comparable>
void BinarySearchTree<Comparable>::insert(const Comparable & x, BinaryNode *& root)
{
	if (root == NULL)//如果结点为空，说明这个结点就是要插入的位置
	{
		root = new BinaryNode(x, NULL, NULL);
	}
	if (x < root->element)
	{
		insert(x, root->left);
	}
	else if (x > root->element)
	{
		insert(x, root->right);
	}
	else
	{
		;//如果有个元素操作，可以不做任何操作，也可以添加频率
	}
	root->theHeight = max(height(root->left), height(root->right)) + 1;
}

template<typename Comparable>
void BinarySearchTree<Comparable>::remove(const Comparable & x, BinaryNode *& root)
{
	if (root != NULL)
	{
		if (x < root->element)
		{
			remove(x, root->left);
		}
		else if (x > root->element)
		{
			remove(x, root->right);
		}
		else//如果这个元素就是要删除的元素，那么要考虑三种情况
		{
			if (root->left != NULL && root->right != NULL)//两个孩子
			{
				//只用把元素提上来，不用改指针
				root->element = findMin(root->right)->element;//找到右结点最小元素
															  //然后把最小元素删除即可
				remove(root->element, root->right);
			}
			else//一个孩子或者没有孩子
			{
				BinaryNode *oldRoot = root;
				root = (root->left != NULL) ? root->left : root->right;
				delete oldRoot;
			}
		}
	}
	if (root)
	{
		root->theHeight = max(height(root->left), height(root->right)) + 1;
	}
}

template<typename Comparable>
void BinarySearchTree<Comparable>::makeEmpty(BinaryNode *& root)
{
	if (root != NULL)
	{
		makeEmpty(root->left);
		makeEmpty(root->right);
		delete root;
	}
	root = NULL;//必须要置为空NULL
}

template<typename Comparable>
BinaryNode * BinarySearchTree<Comparable>::findMax(BinaryNode * root) const
{
	if (root == NULL)
	{
		return NULL;//树为空
	}
	if (root->right == NULL)
	{
		return root;
	}
	return findMax(root->right);
}




