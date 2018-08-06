//
// Created by Administrator on 2018/8/6/006.
//

#ifndef HEAP_AND_PRIORITY_QUEUE_ARRAY_H
#define HEAP_AND_PRIORITY_QUEUE_ARRAY_H

#include <iostream>
#include <cassert>
template < class T >
class Array
{
private:
    T *data;
    int size;
    int capacity;
public:
    // 构造函数，传入数组的容量capacity构造Array
    Array(int capacity)
    {
        this -> capacity = capacity;
        data = new T[capacity];
        size = 0;
    }
    // 传入一个数组，进行拷贝
    Array(T arr[],int n)
    {
        data = new T[n];
        size = n;
        capacity = n;
        for (int i = 0; i < n; ++i)
        {
            data[i] = arr[i];
        }
    }
    // 无参数的构造函数，默认数组的容量capacity=10
    Array()
    {
        capacity = 5;
        data = new T[capacity];
        size = 0;
    }
    // 获取数组的容量
    int getCapacity() const
    {
        return capacity;
    }
    // 获取数组中的元素个数
    int getSize() const
    {
        return size;
    }
    // 返回数组是否为空
    bool isEmpty() const
    {
        return (size == 0);
    }
    // 在index索引的位置插入一个新元素e
    void insert(int index ,T e)
    {
        if(index < 0 || index > size)
            throw "this index is bad.";
        if(size == capacity)
        {
            resize(2 * capacity);
        }
        for(int i = size ; i > index -1 ; i--)
            data[i] = data[i-1];
        data[index] = e;
        size ++;
    }
    // 向所有元素后添加一个新元素
    void addLast(T e)
    {
        insert(size,e);
    }
    // 在所有元素前添加一个新元素
    void addFirst(T e)
    {
        insert(0,e);
    }
    // 获取index索引位置的元素
    T getData(int index)
    {
        if(index < 0 || index >= size)
            throw "this index is bad.";
        return data[index];
    }
    // 修改index索引位置的元素为e
    void setData(int index , T e)
    {
        if(index < 0 || index > size)
            throw "this index is bad.";
        data[index] = e;
    }
    // 查找数组中是否有元素e
    bool contains(T e)
    {
        for(int i = 0; i < size ; i++)
        {
            if(data[i] == e)
                return true;
        }
        return false;
    }
    // 查找数组中元素e所在的索引，如果不存在元素e，则返回-1
    int find(T e)
    {
        for(int i = 0; i < size ; i++)
        {
            if(data[i] == e)
                return i;
        }
        return -1;
    }
    // 从数组中删除index位置的元素, 返回删除的元素
    T remove(int index)
    {
        if(index < 0 || index > size)
            throw "this index is bad.";
        T ret = data[index];
        for(int i = index; i < size ; i++)
        {
            data[i] = data[i + 1];
        }
        size--;
        if(size <= capacity / 4 && capacity / 2 != 0 )
        {
            resize(capacity / 2);
        }
        return ret;
    }
    // 从数组中删除第一个元素, 返回删除的元素
    void removeFirst()
    {
        remove(0);
    }
    // 从数组中删除最后一个元素, 返回删除的元素
    void removeLast()
    {
        remove(size - 1);
    }
    // 从数组中删除元素e
    void removeElement(T e)
    {
        remove(Find(e));
    }
    void swap(int a, int b)
    {
        assert(a >= 0 && a < size && b >= 0 && b < size);
        T tmp = getData(a);
        setData(a,getData(b));
        setData(b,tmp);
    }
    void toString()
    {
        for (int i = 0; i < getSize(); ++i)
        {
            if(i == getSize() - 1)
            {
                std::cout << getData(i) << std::endl;
                break;
            }
            std::cout << getData(i) << ",";
        }
    }

private:
    // 将数组空间的容量变成newCapacity大小
    void resize(int newcapacity)
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
#endif //HEAP_AND_PRIORITY_QUEUE_ARRAY_H
