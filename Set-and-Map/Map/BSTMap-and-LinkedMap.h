//
// Created by Administrator on 2018/8/6/006.
//

#ifndef MAP_BSTMAP_AND_LINKEDMAP_H
#define MAP_BSTMAP_AND_LINKEDMAP_H

#include "BST.h"
#include "LinkedList.h"

template <typename K,typename V>
class Map
{
    virtual int getSize() const = 0;
    virtual bool isEmpty() const = 0;
    virtual V get(K) const = 0;
    virtual bool contains(K) const = 0;
    virtual V remove(K) = 0;
    virtual void set(K,V) = 0;
    virtual void add(K,V) = 0;
};
template <typename K,typename V>
class BSTMap:public Map<K,V>
{
public:
    BSTMap()
    {
        bst = new BST<K,V>();
    }
    ~BSTMap()
    {
        delete bst;
    }
    int getSize() const
    {
        return bst->getSize();
    }
    bool isEmpty() const
    {
        return bst->isEmpty();
    }
    V get(K e) const {
        return bst->getValue(e);
    }
    bool contains(K e) const
    {
        return bst->contains(e);
    }
    V remove(K e)
    {
        return bst->remove(e);
    }
    void set(K e,V v)
    {
        bst->set(e,v);
    }
    void add(K e, V v)
    {
        bst->add(e,v);
    }
private:
    BST<K,V>* bst;
};
template <typename K,typename V>
class LinkedMap:public Map<K,V>
{
public:
    LinkedMap()
    {
        list = new LinkedList<K,V>();
    }
    ~LinkedMap()
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
    V get(K e) const {
        return list->getValue(e);
    }
    bool contains(K e) const
    {
        return list->contains(e);
    }
    V remove(K e)
    {
        return list->removeElement(e);
    }
    void set(K e,V v)
    {
        list->set2(e,v);
    }
    void add(K e, V v)
    {
        list->addLast(e,v);
    }

private:
    LinkedList<K,V>* list;
};
#endif //MAP_BSTMAP_AND_LINKEDMAP_H
