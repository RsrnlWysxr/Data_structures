#include <iostream>
using namespace std;


template < class T >
class Array
{
	private:
		T *data;
		int size;
		int capacity;
	public:
		// 构造函数，传入数组的容量capacity构造Array
		Array(int temcapacity)
		{
			capacity = temcapacity;
			data = new T[capacity];
			size = 0;
		}
		// 无参数的构造函数，默认数组的容量capacity=10
		Array()
		{
			capacity = 10;
			data = new T[capacity];
			size = 0;
		}
		// 获取数组的容量
		int Getcapacity() const
		{
			return capacity;
		}
		// 获取数组中的元素个数
		int Getsize() const
		{
			return size;
		}
		// 返回数组是否为空
		bool Isempty() const
		{
			return (size == 0);
		}
		// 在index索引的位置插入一个新元素e
		void Inserte(int index ,T e)
		{
			if(index < 0 || index > size)
				throw "this index is bad.";
			if(size == this->Getcapacity())
			{
				Resize(2 * this->Getcapacity());
			}
			for(int i = size ; i > index -1 ; i--)
				data[i] = data[i-1];
			data[index] = e;
			size ++;
		}
		// 向所有元素后添加一个新元素
		void Addlast(T e)
		{
			Inserte(size,e);
		}
		// 在所有元素前添加一个新元素
		void Addfirst(T e)
		{
			Inserte(0,e);
		}
		// 获取index索引位置的元素
		T Getdata(int index)
		{
			if(index < 0 || index > size)
				throw "this index is bad.";
			return data[index];
		}
		// 修改index索引位置的元素为e
		void Setdata(int index , T e)
		{
			if(index < 0 || index > size)
				throw "this index is bad.";
			data[index] = e;
		}
		// 查找数组中是否有元素e
		bool Contains(T e)
		{
			for(int i = 0; i < size ; i++)
			{
				if(data[i] == e)
					return true;
			}
			return false;
		}
		// 查找数组中元素e所在的索引，如果不存在元素e，则返回-1
		int Find(T e)
		{
			for(int i = 0; i < size ; i++)
			{
				if(data[i] == e)
					return i;
			}
			return -1;
		}
		// 从数组中删除index位置的元素, 返回删除的元素
		T Remove(int index)
		{
			if(index < 0 || index > size)
				throw "this index is bad.";
			T ret = data[index];
			for(int i = index; i < size ; i++)
			{
				data[i] = data[i + 1];
			}
			size--;
			if(size <= this->Getcapacity() / 4 && this->Getcapacity() / 2 != 0 )
			{
				Resize(this->Getcapacity() / 2);
			}
			return ret;
		}
		// 从数组中删除第一个元素, 返回删除的元素
		T Removefirst()
		{
			return Remove(0);
		}
		// 从数组中删除最后一个元素, 返回删除的元素
		T Removelast()
		{
			return Remove(size - 1);
		}
		// 从数组中删除元素e
		void Removeelement(T e)
		{
			Remove(find(e));
		}
		// 将数组空间的容量变成newCapacity大小
		
	private:
		void Resize(int newcapacity)
		{
			capacity = newcapacity;
			T* newdata = new T[capacity];
			for(int i = 0; i < size; i++)
			{
				newdata[i] = data[i];
			}
			data = newdata;
		}
};
//定义纯虚类作为接口
template <class T>
class Stack
{
	public:
		virtual int getSize() const = 0;	//获取目前元素个数
		virtual bool isEmpty() const = 0;	//判断Stack是否为空
		virtual void push(T e) = 0;			//进栈
		virtual T pop() = 0;				//出栈
		virtual T peek() const = 0;			//获取栈顶元素
};
template <class T>
class ArrayStack : public Stack<T>
{
	private:
		Array<T>* array;	//使用Array作为Stack的底层实现
	public:
		ArrayStack()
		{
			array = new Array<T>();
		}
		ArrayStack(int capacity)
		{
			array = new Array<T>(capacity);
		}
		~ArrayStack()
		{
			delete[] array;
		}
		int getSize() const
		{
			return array->Getsize();
		}
		bool isEmpty() const
		{
			return array->Isempty();
		}
		void push(T e)
		{
			array->Addlast(e);
		}
		T pop()
		{
			return array->Removelast();
		}
		T peek() const
		{
			return array->Getdata(getSize()-1);
		}
		void toString()
		{
			cout << "Stack:size" << getSize() << ".\n";
			cout << "bottom -> ";
			for(int i = 0 ; i < getSize() ; ++i)
			{
				if(i == getSize() - 1)
					{
						cout << array->Getdata(i) << "-> top" << endl;
						return;
					}
				cout << array->Getdata(i) << "->";
			}
		}
};
