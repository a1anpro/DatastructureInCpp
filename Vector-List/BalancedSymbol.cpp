#include <iostream>
using namespace std;

template<typename Object>
class Stack{
public:
	Stack(int theSize = INIT_SIZE){
		this->theSize = theSize;
		data = new Object[theSize];
		theTop = 0;
	}
	
	int size() const{
		return theSize;
	}
	bool empty() const{
		return size() == 0;
	}
	
	Object& top() const{
		if (empty())
		{
			cout <<"the stack is empty!";
			//return;
		}
		
		return data[theTop-1];
	}
	void push(const Object &x)
	{
		if (theTop + 1 == theSize)//如果栈满了 
		{
			//...
		}
		
		data[theTop++] = x;
	}
	void pop()
	{
		if (theTop == 0)//栈是空的 
		{
			//..
		}
		theTop--;//直接舍弃top的元素 
	}
	bool isOk(const char &chr)
	{
		bool ok = 0;
		char temp = top();
		if (temp == '(' && chr == ')')
		{
			ok = 1;
		}
		else if(temp == '[' && chr == ']')
		{
			ok = 1;
		}
		else if (temp == '<' && chr == '>')
		{
			ok = 1;
		}
		return ok;
	}
	
	enum{
		INIT_SIZE = 10
	};
private:
	Object *data;
	int theSize;
	int theTop;
};

int main()
{
	Stack<char> stack;
	
	bool ok = 1;
	string str;
	cin >>str;

	//cout<<"size:"<<str.size()<<endl;
	for (int i = 0; i < str.size()&&ok; ++i)
	{
		if (str[i] == '[' || str[i] == '(' || str[i] == '<')
		{
			cout << str[i];

			stack.push(str[i]);
		}
		else if (stack.isOk(str[i]))
		{
			cout << str[i];
			stack.pop();
		}
		else
		{
			ok = 0;
		}
	}
	//cout << stack.empty()<<endl;
	if (stack.empty())
	{
		ok = 0;
	}
	
	cout << ok;
	
	return 0;
} 
