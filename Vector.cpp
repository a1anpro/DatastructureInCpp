#include <iostream>
using namespace std;

template<typename Object>
class Vector{
public:
	//���캯��
	explicit Vector(int initCapacity = 0)
	:theCapacity(initCapacity + SPARE_CAPACITY), theSize(0)
	{
		objects = new Object[theCapacity];
	}
	//���ƹ��캯��
	Vector(const Object& rhs)
	{
		operator=(rhs);
	} 
	//��������
	~Vector()
	{
		delete [] objects;
	} 
	
	//��ֵ���غ��� 
	Object& operator=(const Object& rhs)
	{
		if (this != rhs)//���ָ���Ƿ�ָ��ͬһ����ַ
		{
			//�������ͬһ��������ô���и���
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
		if (newSize > theSize)//�����ʹ�õĳߴ��ԭ���ĳߴ�Ҫ��Ļ����͸��� 
		{
			reserve(2*newSize + 1);
		}
		theSize = newSize;//�����ԭ���ĳ��Ȼ�ҪС�Ļ�����ֱ�ӡ�Ĩȥ������Ķ��� 
	}
	
	void reserve(int newCapacity)
	{
		if (newCapacity < theCapacity)
		{
			return ;//����µ�����ҪС��ԭ���������Ļ����Ͳ����κβ��� 
		}
		
		//����Ҫ��ԭ�������ݸ��Ƶ��µ�������,��ô����Ҫ����ԭ��������
		Object* oldArray = objects;//����ָ�뱣���ֳ�
		objects = new Object[newCapacity];//�¿��ռ�
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
	
	//ѹ��Ԫ�ص�ĩβ
	void push_back(const Object& x)
	{
		if (theSize == theCapacity)
		{
			reserve(2 * theSize + 1);
		}
		
		objects[theSize++] = x;
	} 
	//����ĩβԪ��
	void pop_back()
	{
		if (empty())
		{
			cout <<"the Vector is empty!";
			return ;
		}
		theSize--;
	}
	
	//����ĩβԪ��
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
		SPARE_CAPACITY = 16//Ĭ�����ӳ��� 
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
