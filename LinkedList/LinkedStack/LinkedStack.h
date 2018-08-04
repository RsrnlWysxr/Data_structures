//
// Created by Administrator on 2018/8/4/004.
//
#ifndef LINKEDSTACK_LINKEDSTACK_H
#define LINKEDSTACK_LINKEDSTACK_H

#include "LinkedList.h"
//定义纯虚类作为接口
template <typename T>
class Stack
{
public:
    virtual int getSize() const = 0;
    virtual bool isEmpty() const = 0;
    virtual T peek() const = 0;
    virtual void push(T e) = 0;
    virtual T pop() = 0;
};

template < typename T>
class LinkedStack:public Stack<T>
{
private:
    LinkedList<T>* list;
public:
    LinkedStack()
    {
        list = new LinkedList<T>();
    }
    ~LinkedStack()
    {
        delete list;
    }
    int getSize() const
    {
        return list->getSize();
    }
    bool isEmpty() const
    {
        return list->isEmpty();
    }
    T peek() const
    {
        return list->getFirst();
    }
    void push(T e)
    {
        list->addFirst(e);
    }
    T pop()
    {
        return list->removeFirst();
    }
    void toString()
    {
        std::cout << "top ";
        list->toString();
        std::cout <<" bootom" <<std::endl;
    }
};
#endif //LINKEDSTACK_LINKEDSTACK_H
