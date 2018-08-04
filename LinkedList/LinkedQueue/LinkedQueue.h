//
// Created by Administrator on 2018/8/4/004.
//

#ifndef LINKEDQUEUE_LINKEDQUEUE_H
#define LINKEDQUEUE_LINKEDQUEUE_H

#include "LinkedList.h"

//定义纯虚类作为接口
template <typename T>
class Queue
{
public:
    virtual int getSize() const = 0;
    virtual bool isEmpty() const = 0;
    virtual T getFront() const = 0;
    virtual void enqueue(T e) = 0;
    virtual T dequeue() = 0;
};
template <typename T>
class LinkedQueue:public Queue<T>
{
private:
    LinkedList<T>* queue;
public:
    LinkedQueue()
    {
        queue = new LinkedList<T>();
    }
    ~LinkedQueue()
    {
        delete queue;
    }
    int getSize() const
    {
        return queue->getSize();
    }
    bool isEmpty() const
    {
        return queue->isEmpty();
    }
    T getFront() const
    {
        return queue->getFirst();
    }
    void enqueue(T e)
    {
        queue->addLast(e);
    }
    T dequeue()
    {
        return queue->removeLast();
    }
    void toString()
    {
        std::cout << "Front ";
        queue->toString();
        std::cout << " tail" << std::endl;
    }
};

#endif //LINKEDQUEUE_LINKEDQUEUE_H
