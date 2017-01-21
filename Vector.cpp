#include <iostream>
using namespace std;

template<typename Object>
class Vector{
public:
	//构造函数
	explicit Vector(int initCapacity = 0)
	:theCapacity(initCapacity + SPARE_CAPACITY), theSize(0)
	{
		objects = new Object[theCapacity];
	}
	//复制构造函数
	Vector(const Object& rhs)
	{
		operator=(rhs);
	} 
	//析构函数
	~Vector()
	{
		delete [] objects;
	} 
	
	//赋值重载函数 
	Object& operator=(const Object& rhs)
	{
		if (this != rhs)//检查指针是否指向同一个地址
		{
			//如果不是同一个区域，那么进行复制
			delete [] objects;
			
			theSize = rhs.theSize();
			theCapacity = rhs.theCapacity;
			
			objects = new Object[rhs.capacity()];
			for (int i = 0; i < size(); ++i)
			{
				objects[i] = rhs.objects[i];
			}
		}
		return *this; 
	}
	
	void resize(int newSize)
	{
		if (newSize > theSize)//如果新使用的尺寸比原来的尺寸要大的话，就更新 
		{
			reserve(2*newSize + 1);
		}
		theSize = newSize;//如果比原来的长度还要小的话，就直接“抹去”超界的对象； 
	}
	
	void reserve(int newCapacity)
	{
		if (newCapacity < theCapacity)
		{
			return ;//如果新的容量要小于原来的容量的话，就不做任何操作 
		}
		
		//现在要把原来的内容复制到新的数组内,那么首先要保存原来的数组
		Object* oldArray = objects;//申请指针保留现场
		objects = new Object[newCapacity];//新开空间
		for (int i = 0; i < size(); ++i)
		{
			objects[i] = oldArray[i];
		} 
		
		theCapacity = newCapacity;
		
		delete [] oldArray;
	}
	
	Object& operator[] (int index)
	{
		return objects[index];
	}
	const Object& operator[] (int index) const
	{
		return objects[index];
	}
	
	//压入元素到末尾
	void push_back(const Object& x)
	{
		if (theSize == theCapacity)
		{
			reserve(2 * theSize + 1);
		}
		
		objects[theSize++] = x;
	} 
	//弹出末尾元素
	void pop_back()
	{
		if (empty())
		{
			cout <<"the Vector is empty!";
			return ;
		}
		theSize--;
	}
	
	//返回末尾元素
	Object& back() const
	{
		if (empty())
		{
			cout <<"the Vector is empty!";
			return NULL;
		}
		return objects[theSize - 1];
	} 
	
	bool empty()
	{
		return size() == 0;
	}
	int size() const
	{
		return theSize;
	}
	int capacity() const
	{
		return theCapacity;
	}
	enum{
		SPARE_CAPACITY = 16//默认增加长度 
	};

	typedef Object* iterator;
	typedef const Object* const_iterator;
	
	iterator begin()
	{
		return &objects[0];
	}
	const_iterator begin() const
	{
		return &objects[0];
	}
	iterator end()
	{
		return &objects[theSize - 1];
	}
	const_iterator end() const
	{
		return &objects[theSize - 1];
	}

private:
	int theSize;
	int theCapacity;
	Object* objects;
};

int main()
{
	return 0;
}
