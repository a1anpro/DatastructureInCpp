#pragma once
#include "TreeNode.h"
#include "List.h"

class ExpressionTree//表达式树 类
{
public:
	ExpressionTree() {}//默认构造
	ExpressionTree(string infix) :infix(infix) {}//用中缀表达式构造表达式树

	//初始化表达式树，得到后缀表达式
	void init();

	//输入输出中缀表达式
	void inputInfix();
	void outputInfix();

	//输出后缀表达式
	void outputSuffix();

	//得到后缀表达式树
	void makeTree();

	void seeTop();

	///////////////////////////////////////////////////////////////////////////
	//中缀转换成后缀(最终我想把这个做成一个类，直接用， 而不是把这么多函数放在其他类里面（目前这个设计思路非常不好）
	bool isOperator(const char& chr);//判断是不是操作符 
	bool isLowerEqualThan(const char& top, const char& current);//判断当前的符号和栈顶符号优先级
	int isLower(const char& top, const char& current); //内部函数 
	string toSuffix(const string& infixStr);//把中缀转换成后缀

private:
	string infix;//输入的中缀表达式
	string suffix;//转换的后缀表达式
	List<TreeNode*> ptrStack;//存放结点指针的栈
};
