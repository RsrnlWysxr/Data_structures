//
// Created by Administrator on 2018/8/6/006.
//

#ifndef HEAP_AND_PRIORITY_QUEUE_MAXHEAP_H
#define HEAP_AND_PRIORITY_QUEUE_MAXHEAP_H

#include <iostream>
#include <algorithm>
#include "Array.h"

template <typename T>
class MaxHeap
{
private:
    Array<T>* data;
public:
    MaxHeap()
    {
        data = new Array<T>();
    }
    MaxHeap(int capacity)
    {
        data = new Array<T>(capacity);
    }
    MaxHeap(T arr[],int n)
    {
        data = new Array<T>(arr,n);
        for(int i = parent(n - 1) ; i >= 0 ; --i)
        {
            siftDown(i);
        }
    }
    ~MaxHeap()
    {
        delete data;
    }
    // 返回堆中的元素个数
    int getSize() const
    {
        return data->getSize();
    }
    // 返回一个布尔值, 表示堆中是否为空
    bool isEmpty() const
    {
        return data->isEmpty();
    }
private:
    // 返回完全二叉树的数组表示中，一个索引所表示的元素的父亲节点的索引
    int parent(int index)
    {
        assert(index > 0 && index < getSize());
        return (index - 1) / 2;
    }
    // 返回完全二叉树的数组表示中，一个索引所表示的元素的左孩子节点的索引
    int leftChild(int index)
    {
        return index * 2 + 1;
    }
    // 返回完全二叉树的数组表示中，一个索引所表示的元素的右孩子节点的索引
    int rightChild(int index)
    {
        return index * 2 + 2;
    }

public:
    // 向堆中添加元素
    void add(T e)
    {
        data->addLast(e);
        siftUp(data->getSize()-1);
    }

private:
    void siftUp(int k)
    {
        while( k >0  && data->getData(parent(k)) < data->getData(k))
        {
            data->swap(parent(k),k);
            k = parent(k);
        }
    }

public:
    // 看堆中的最大元素
    T findMax()
    {
        assert(data->getSize()>0);
        return data->getData(0);
    }
    // 取出堆中最大元素
    T extractMax()
    {
        assert(data->getSize()>0);
        T ret = findMax();
        data->swap(0,data->getSize()-1);
        data->removeLast();
        siftDown(0);
        return ret;
    }

private:
    void siftDown(int k )
    {
//        int swapIndex = compare(k);
//        while (k < data->getSize() && data->getData(k) < data->getData(swapIndex))
//        {
//            data->swap(k, swapIndex);
//            k = swapIndex;
//            swapIndex = compare(k);
//        }
        ///////////////////////////////////////////////////
    // 不花费额外的函数调用开销
        while(leftChild(k) < data->getSize())
        {
            int j = leftChild(k);   //此轮循环中data[k] 和 data[j] 交换位置
            if(j + 1 < data->getSize() && data->getData(j) < data->getData(j + 1))
                j++;
            //data[j] 是 leftChild 和 rightChild 中的最大值
            if(data->getData(k) >= data->getData(j))
                break;
            data->swap(k,j);
            k = j;
        }
    }
    // 比较左右孩子大小，返回较大的孩子的索引
    int compare(int k )
    {
        int left = leftChild(k);
        int right = left + 1;
        if(left >= data->getSize()) return k;
        else if(right >= data->getSize()) return left;
        else if(data->getData(left) < data->getData(right))
            return right;
        else return left;
    }
public:
    // 取出堆中的最大元素，并且替换成元素e
    T replace(T e)
    {
        T ret = findMax();
        data->setData(0,e);
        siftDown(0);
        return ret;
    }
    void toString()
    {
        data->toString();
    }
};


#endif //HEAP_AND_PRIORITY_QUEUE_MAXHEAP_H
