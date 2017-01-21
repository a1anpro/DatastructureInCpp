#pragma once
#include  <iostream>
using namespace std;

template<typename Object>
class List
{
private:
	struct Node
	{
		//默认为public
		Object data;
		Node *prev;
		Node *next;

		//Node() {}
		Node(const Object &data = Object(), Node *prev = NULL, Node *next = NULL)
			:data(data), prev(prev), next(next) {}//参数优先，局部变量优先
	};

public:
	class const_iterator
	{
	public:
		const_iterator() :current(NULL) {}

		const_iterator& operator*() const//这个const 是使这个函数为常量函数，所以current是不能被修改的
		{
			return retrieve();
		}

		//前自增
		const_iterator& operator++()const
		{
			current = current->next;
			return *this;
		}
		//后自增
		const_iterator& operator++(int)const
		{
			const_iterator old = *this;
			++(*this);
			return old;
		}
		//前自减
		const_iterator& operator--()const
		{
			current = current->prev;
			return *this;
		}
		//后自减
		const_iterator& operator--(int)const
		{
			const_iterator old = *this;
			--(*this);
			return old;
		}

		//重载==
		bool operator==(const const_iterator &rhs) const//rhs = right hand side;
		{
			return this.current == rhs.current;
		}
		bool operator!=(const const_iterator &rhs) const
		{
			return !(*this == rhs);
		}
	protected:
		Node *current;//当前结点的指针

		Object& retrieve() const//私用函数，所以放在protected保护中。这个函数是访问函数
		{
			return current->data;
		}
		const_iterator(Node *p) : current(p) {}//构造函数，只允许该类和子类用

		friend class List<Object>;
	};

	class iterator : public const_iterator
	{
	public:
		iterator() {}
		Object& operator*()
		{
			return retrieve();
		}
		//前自增 
		iterator& operator++ ()
		{
			current = current->next;
			return *this;
		}
		//后自增 
		iterator& operator++ (int)
		{
			iterator old = *this;
			++(*this);
			return old;
		}

		//前自减
		iterator& operator-- ()
		{
			current = current->prev;
			return *this;
		}
		//后自减
		iterator& operator-- (int)
		{
			iterator old = *this;
			--(*this);
			return old;
		}
	public:
		//protected:
		iterator(Node *p) :const_iterator(p) {}
	};


public:
	//构造函数
	List() {
		init();
	}
	//复制构造
	List(const List &rhs) {
		init();
		*this = rhs;
	}
	//析构函数
	~List()
	{
		clear();
		delete head;
		delete tail;
	}
	//赋值函数
	const List& operator=(const List &rhs)
	{
		if (rhs == *this)
		{
			return *this;
		}
		//
		clear();
		for (const_iterator itr = rhs.begin(); itr != rhs.end(); ++itr)
		{
			push_back(*itr);
		}
		return *this;
	}

	iterator begin() {
		return iterator(head->next);
	}
	const_iterator begin() const
	{
		return const_iterator(head->next);
	}
	iterator end() {
		return iterator(tail);
	}
	const_iterator end() const
	{
		return const_iterator(tail);
	}

	int size() const {
		return theSize;
	}
	bool empty() const
	{
		return size() == 0;
	}

	void clear()
	{
		while (!empty())
		{
			pop_front();//弹出 
		}
	}

	Object& front() {//首元 
		return *begin();
	}
	const Object& front() const {
		return *begin();
	}

	Object& back() {
		return *--end();
	}
	const Object& back() const {
		return *--end();
	}//为什么要做一套常量：后面（常成员函数，不能修改两个指针和theSize） 前面（常量） 

	void push_front(const Object& x)
	{
		insert(begin(), x);
	}
	void push_back(const Object& x)
	{
		insert(end(), x);
	}

	void pop_back()
	{
		erase(--end());
	}
	void pop_front() {
		erase(begin());
	}

	iterator insert(iterator itr, const Object& x)
	{
		Node *p = itr.current;
		++theSize;
		Node *newNode = new Node(x, p->prev, p);
		p->prev->next = newNode;
		p->prev = newNode;
		return iterator(newNode);
		//return iterator(p->prev = p->prev->next = new Node(x, p->prev, p));
	}

	//删除结点 
	iterator erase(iterator itr)
	{
		Node *p = itr.current;

		iterator retVal(p->next);

		--theSize;//长度-1
		p->prev->next = p->next;
		p->next->prev = p->prev;

		delete p;
		return retVal;
	}
	//比如删除1~3，则只会删除1、2 a
	iterator erase(iterator begin, iterator end)
	{
		for (iterator itr = begin; itr != end; )
		{
			itr = erase(itr);
		}

		return end;
	}

private:
	int theSize;
	Node *head;
	Node *tail;

	void init() {//为什么要private :为了减少代码的重写，拷贝和构造都用，外面都不能用 
		theSize = 0;
		head = new Node(Object(), NULL, tail);
		tail = new Node(Object(), head, NULL);
		/*head->next = tail;
		tail->prev = head;*/
	}
};
