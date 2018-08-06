//
// Created by Administrator on 2018/8/6/006.
//

#ifndef SET_SET_H
#define SET_SET_H

#include "LinkedList.h"
#include "BST.h"

//定义纯虚类Set为接口
template <typename T>
class Set
{
    virtual bool isEmpty() const = 0;
    virtual bool contains(T e) const = 0;
    virtual int getSize() const = 0;
    virtual void add(T e) = 0;
    virtual void remove(T e) = 0;
};
template <typename T>
class BSTSet:public Set<T>
{
public:
    //构造函数
    BSTSet()
    {
        bst = new BST<T>();
    }
    //析构函数
    ~BSTSet()
    {
        delete bst;
    }
    bool isEmpty() const
    {
        bst->isEmpty();
    }
    bool contains(T e)const
    {
        bst->contains(e);
    }
    int getSize() const
    {
        bst->getSize();
    }
    void add(T e)
    {
        bst->add(e);
    }
    void remove(T e)
    {
        bst->remove(e);
    }
private:
    BST<T>* bst;

};

template <typename T>
class LinkedSet:public Set<T>
{
public:
    //构造函数
    LinkedSet()
    {
        list = new LinkedList<T>();
    }
    //析构函数
    ~LinkedSet()
    {
        delete list;
    }
    bool isEmpty() const
    {
        list->isEmpty();
    }
    bool contains(T e)const
    {
        list->contains(e);
    }
    int getSize() const
    {
        list->getSize();
    }
    void add(T e)
    {
        if(!list->contains(e))
            list->addLast(e);
    }
    void remove(T e)
    {
        list->removeElement(e);
    }
private:
    LinkedList<T>* list;

};

#endif //SET_SET_H
