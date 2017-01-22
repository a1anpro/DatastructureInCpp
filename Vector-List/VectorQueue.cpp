#pragma once
#pragma warning( disable : 4290 ) 
#include <stdlib.h>

class EmptyException {};//空队列异常（自定义）

template<typename Object>
class Queue
{
public:
	//构造函数
	Queue(int initCapacity = 10)//默认大小为10
	{
		init(initCapacity);
	}
	//赋值函数
	Queue& operator= (const Queue& rhs);
	//赋值构造函数
	Queue(const Queue& rhs)
	{
		*this = rhs;
	}
	//析构函数
	~Queue();

	int size() const;

	bool empty() const;
	bool full() const;//const是来保护this的

	void resize(int newCapacity);
	//void check();
	bool checkEmpty() const;
	//void emptyOperation() const;

	void enqueue(const Object& x);
	Object& dequeue(); ///如果为空的话怎么处理，返回什么？

	Object& back() const;
	Object& front() const;
private:
	Object *queue;//数组2
	int theFront;
	int theRear;
	int theCapacity;//数组容量

	void init(int initCapacity)
	{
		theCapacity = initCapacity;
		theFront = 0;
		theRear = -1;
		queue = new Object[theCapacity];
	}
};


template<typename Object>
Queue<Object>& Queue<Object>::operator= (const Queue& rhs)
{
	if (this != &rhs)
	{
		delete[] this;//释放原来的数组
		theCapacity = rhs.theCapacity;//新容量
		this = new Object[theCapacity];

		theFront = 0;
		theRear = -1;
		for (int i = 0; (i + rhs.theFront) % theCapacity != rhs.theRear; ++i)
		{
			queue[++theRear] = rhs.queue[(i + rhs.theFront) % theCapacity];
		}

		queue[++theRear] = rhs.queue[rhs.theRear];
	}

	return *this;
}

template<typename Object>
Queue<Object>::~Queue()
{
	theCapacity = 0;
	theFront = 0;
	theRear = -1;
	delete [] queue;
}

template<typename Object>
int Queue<Object>::size() const
{
	int temp = theRear + 1 - theFront;
	if (temp < 0)
	{
		return (-temp) % theCapacity;
	}
	return temp%theCapacity;
}

template<typename Object>
bool Queue<Object>::empty() const
{
	return size() == 0;
}

template<typename Object>
bool Queue<Object>::full() const//const是来保护this的
{
	return size() == theCapacity;
}

template<typename Object>
void Queue<Object>::resize(int newCapacity)
{
	//Queue *old = this;//保存原来的内容

	Object *oldArray = this->queue;

	this->queue = new Object[newCapacity];//新开辟数组空间
										  //this->theCapacity = newCapacity;//赋值新空间
	int tempF = 0;
	int tempR = -1;

	for (int i = 0; (i + theFront) % theCapacity != theRear; ++i)
	{
		this->queue[++tempR] = oldArray[(i + theFront) % theCapacity];
	}
	this->queue[++tempR] = oldArray[theRear];
	//此时queue、theRear、theFront都已经更新
	this->theCapacity = newCapacity;//全部更新
	delete[] oldArray;//释放空间
}
//
//template<typename Object>
//void Queue<Object>::check() throw emptyException
//{
//
//}

template<typename Object>
bool Queue<Object>::checkEmpty() const 
{
	if (empty())//如果队列为空，则不能出队列
	{
		return 1;
	}
	else
		return 0;
}

template<typename Object>
void Queue<Object>::enqueue(const Object& x)
{
	if (full())//如果队列已经满了，就重新分配尺寸
	{
		resize(theCapacity * 2 + 1);
	}

	this->queue[++theRear] = x;
}

template<typename Object>
Object& Queue<Object>::dequeue()///如果为空的话怎么处理，返回什么？
{	

	/*try
	{
		
	}
	catch (EmptyException)
	{
		cout << "the queue is empty!" << endl;
	}*/
	int temp = theFront;
	theFront++;
	return this->queue[temp];
}

template<typename Object>
Object& Queue<Object>::front() const
{
	/*try
	{
		check();
	}
	catch (EmptyException)
	{
		cout << "the queue is empty!" << endl;
	}*/

	return queue[theFront];

}

template<typename Object>
Object& Queue<Object>::back() const
{
	/*try
	{
		check();
	}
	catch (EmptyException)
	{
		cout << "the queue is empty!" << endl;
	}*/

	return queue[theRear];
	
}
