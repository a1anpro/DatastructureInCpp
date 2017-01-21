/*设计思想：
	先把输入的一般算式转换成后缀表达式，然后解析后缀表达式，计算结果；

	遇到操作数，就输出操作数；
	遇到操作符，	 如果栈空：压栈
				 栈不空：比较该元素和栈顶元素的优先级，如果当前元素优先级低于或者等于 栈顶元素优先级，那么就输出
				 并弹出栈顶元素。该元素压入(如果是“（”也压入)
						如果当前元素优先级高于栈顶元素优先级，直接压栈
			字符串全部读完之后，如果栈不空，就依次输出并弹出栈顶；
*/

/*声明：*/
bool isOperator(const char& chr);//判断是不是操作符 
bool isLowerEqualThan(const char& top, const char& current)//判断当前的符号和栈顶符号优先级
int isLower(const char& top, const char& current); //内部函数 
string toSuffix(const string& infixStr);//把中缀转换成后缀


/*实现*/
bool isOperator(const char& chr)
{
	return chr == '(' || chr == ')' || chr == '+' || chr == '-' || chr == '*' || chr == '/' || chr == '^';
}

int isLower(const char& top, const char& current)
{
	int level[256] = { 0 };
	level['^'] = 3;//优先级
	level['+'] = level['-'] = 1;//
	level['*'] = level['/'] = 2;//

	return level[current] - level[top];//返回差值
}

bool isLowerEqualThan(const char& top, const char& current)
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

string toSuffix(const string& infixStr)//把中缀转换成后缀
{
	string outStr;
	List<char> operatorStack;//装运算符的栈

	for (int i = 0; i < (int)infixStr.size(); ++i)
	{
		if (isOperator(infixStr[i]))//如果是操作符的话
		{
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
		outStr += operatorStack.back();
		operatorStack.pop_back();
	}
	return outStr;
}
