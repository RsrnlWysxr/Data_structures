//
// Created by Administrator on 2018/8/7/007.
//

#ifndef HEAP_AND_PRIORITY_QUEUE_PRIORITY_QUEUE_H
#define HEAP_AND_PRIORITY_QUEUE_PRIORITY_QUEUE_H

#include "MaxHeap.h"
// 使用纯虚类作为队列接口
template <typename T>
class Queue
{
    virtual int getSize() = 0;
    virtual bool isEmpty() = 0;
    virtual void enqueue(T e) = 0;
    virtual T dequeue() = 0;
    virtual T getFront() = 0;
};
template <typename T>
class PriorityQueue:public Queue<T>
{
public:
    PriorityQueue()
    {
        maxHeap = new MaxHeap<T>();
    }
    ~PriorityQueue()
    {
        delete maxHeap;
    }
    int getSize()
    {
        return maxHeap->getSize();
    }
    bool isEmpty()
    {
        return maxHeap->isEmpty();
    }
    void enqueue(T e)
    {
        maxHeap->add(e);
    }
    T dequeue()
    {
        return maxHeap->extractMax();
    }
    T getFront()
    {
        return maxHeap->findMax();
    }

private:
    MaxHeap<T>* maxHeap;
};
#endif //HEAP_AND_PRIORITY_QUEUE_PRIORITY_QUEUE_H
