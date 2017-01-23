#include <iostream>
#include "ExpressionTree.h"
#include <string>
#include "MyStream.h"
using namespace std;

void ExpressionTree::init()
{
	inputInfix();//调用输入
	suffix = toSuffix(infix);//在init的时候就得到后缀表达式；避免其他函数再次调用
	//还差一个得到表达式树的函数(done)
	makeTree();

}

void ExpressionTree::inputInfix()
{
	cout << "input the infix :  ";
	cin >> infix;
}

void ExpressionTree::outputInfix()
{
	cout << infix << endl;
}

void ExpressionTree::outputSuffix()
{
	cout << suffix << endl;
}

void ExpressionTree::makeTree()
{
	MyStream ms;//
	TreeNode *tempNode;
	int tempNum = 0;
	//遍历后缀表达式，构造结点
	for (int i = 0; i < (int)suffix.size(); ++i)
	{
		if (suffix[i] >= '0' && suffix[i] <= '9')//数字
		{
			tempNum = tempNum * 10 + suffix[i] - '0';
			continue;//
		}
		if (suffix[i] == ' ' && !isOperator(suffix[i-1]))//碰到空格,并且上一个元素不是符号的话(即上一个为数)(ok)
		{
			tempNode = new TreeNode(ms.IntToString(tempNum), NULL, NULL);//把tempNum转换成string
			ptrStack.push_back(tempNode);//构造一个结点之后入栈
			tempNum = 0;
		}
		if (isOperator(suffix[i]))//如果是运算符
		{
			TreeNode *b = ptrStack.back();
			ptrStack.pop_back();
			TreeNode *a = ptrStack.back();
			ptrStack.pop_back();
			
			//这一步构造操作符的步骤没有完成
			tempNode = new TreeNode(ms.CharToString(suffix[i]), a, b);//构造树的重要步骤
			ptrStack.push_back(tempNode);
		}

	}
}

void ExpressionTree::seeTop()
{
	TreeNode *temp = ptrStack.back();
	cout << temp->getData() << endl;
}

bool ExpressionTree::isOperator(const char& chr)
{
	return chr == '(' || chr == ')' || chr == '+' || chr == '-' || chr == '*' || chr == '/' || chr == '^';
}

int ExpressionTree::isLower(const char& top, const char& current)
{
	int level[256] = { 0 };
	level['^'] = 3;//优先级
	level['+'] = level['-'] = 1;//
	level['*'] = level['/'] = 2;//

	return level[current] - level[top];//返回差值
}

bool ExpressionTree::isLowerEqualThan(const char& top, const char& current)
{
	if (isLower(top, current) <= 0)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

string ExpressionTree::toSuffix(const string& infixStr)//把中缀转换成后缀
{
	string outStr;
	List<char> operatorStack;//装运算符的栈

	for (int i = 0; i < (int)infixStr.size(); ++i)
	{
		if (isOperator(infixStr[i]))//如果是操作符的话
		{
			outStr += " ";
			if (operatorStack.empty())
			{
				operatorStack.push_back(infixStr[i]);//栈空 直接压栈
			}
			else //栈不空
			{
				if (infixStr[i] == '(')//如果是"(",直接压入
				{
					operatorStack.push_back(infixStr[i]);
				}
				else if (infixStr[i] == ')')
				{
					while (operatorStack.back() != '(')//如果碰到右括号后，栈顶元素不是(，就一直弹出栈，直到（
					{
						outStr += operatorStack.back();//一个一个的加到输出字符串
						operatorStack.pop_back();
					}
					//此时栈顶是"("
					operatorStack.pop_back();//直接弹出
				}
				else if (isLowerEqualThan(operatorStack.back(), infixStr[i]))//比较栈顶元素和当前元素,如果当前元素
																			 //小于等于栈顶:
				{
					outStr += operatorStack.back();//先输出栈顶元素
					operatorStack.pop_back();//然后弹出栈顶元素
					operatorStack.push_back(infixStr[i]);//再将当前元素压入栈内;
				}
				else//如果当前元素比栈顶元素优先级高的话，就压栈
				{
					operatorStack.push_back(infixStr[i]);
				}
			}
		}
		else //如果是操作数的话
		{
			outStr += infixStr[i];//就把该操作数放入输出数组
		}
	}

	while (!operatorStack.empty())
	{
		outStr += " ";
		outStr += operatorStack.back();
		operatorStack.pop_back();
	}
	return outStr;
}
/*
设计流程：
	表达式树有一个初始化函数，在初始化的时候输入中缀表达式，然后直接得到后缀表达式存入成员变量，不要在其他函数要用的时候
	 反复调用 中缀转后缀的函数
*/
