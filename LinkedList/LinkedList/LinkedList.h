//
// Created by Administrator on 2018/8/4/004.
//

#ifndef LINKEDLIST_LINKEDLIST_H
#define LINKEDLIST_LINKEDLIST_H

template <typename T>
class LinkedList
{
private:
    class Node
    {
    public:
        T e;
        Node* next;
        Node():next(nullptr){}
        Node(T e):e(e),next(nullptr){}
        Node(T e,Node* next):e(e),next(next){}
        ~Node(){next = nullptr;}
    };
    Node* dummyHead;
    int size;
    
    // 删除以node为根的链表
    
    void destroy(Node* node)
    {
    if( node->next == nullptr)
        {
            delete node;
            return;
        }
    destroy(node->next);
    delete node;
    return;
    }

public:
    LinkedList()
    {
        dummyHead = new Node();
        size = 0;
    }
    ~LinkedList()
    {
        destroy(dummyHead);
    }
    // 获取链表中的元素个数
    int getSize() const
    {
        return size;
    }
    // 返回链表是否为空
    bool isEmpty() const
    {
        return (size == 0);
    }
    // 在链表的index(0-based)位置添加新的元素e
    void add(int index,T e)
    {
        if(index > size || index < 0 )
            throw "This index is Error.";
        Node* prev = dummyHead;
        for(int i = 0 ; i < index ; ++i)
        {
            prev = prev->next;
        }
        prev->next = new Node(e,prev->next);
        ++size;
    }
    // 在链表头添加新的元素e
    void addFirst(T e)
    {
        add(0,e);
    }
    // 在链表末尾添加新的元素e
    void addLast(T e)
    {
        add(size,e);
    }
    // 获得链表的第index(0-based)个位置的元素
    T getData(int index) const
    {
        if(index >= size || index < 0 )
            throw "This index is Error.";
        Node* cur = dummyHead->next;
        for(int i = 0 ; i < index ; ++i)
        {
            cur = cur->next;
        }
        return cur->e;
    }
    // 获得链表的第一个元素
    T getFirst() const
    {
        return getData(0);
    }
    // 获得链表的最后一个元素
    T getLast() const
    {
        return getData(size - 1);
    }
    // 修改链表的第index(0-based)个位置的元素为e
    void set(int index,T e)
    {
        if(index >= size || index < 0 )
            throw "This index is Error.";
        Node* cur = dummyHead->next;
        for(int i = 0 ; i < index ; ++i)
        {
            cur = cur->next;
        }
        cur->e = e;
    }
    // 查找链表中是否有元素e
    bool contains(T e)
    {
        Node* cur = dummyHead->next;
        while(cur != nullptr)
        {
            if(cur->e == e)
                return true;
            cur = cur->next;
        }
        return false;
    }
    // 从链表中删除index(0-based)位置的元素, 返回删除的元素
    T remove(int index)
    {
        if(index >= size || index < 0 )
            throw "This index is Error.";
        Node* prev = dummyHead;
        for(int i = 0 ; i < index ; ++i)
        {
            prev = prev->next;
        }
        Node* retNode = prev->next;
        prev->next = retNode->next;
        detele retNode;
        -- size;
        return retNode->e;
    }
    // 从链表中删除第一个元素, 返回删除的元素
    T removeFirst()
    {
        return remove(0);
    }
    // 从链表中删除最后一个元素, 返回删除的元素
    T removeLast()
    {
        return remove(size - 1);
    }
    // 从链表中删除元素e
    void removeElement(T e)
    {
        Node* prev = dummyHead;
        while(prev->next != nullptr)
        {
            if(prev->next->e == e)
                break;
            prev = prev->next;
        }
        if(prev->next != nullptr)
        {
            Node* delNode = prev->next;
            prev->next = delNode->next;
            delete delNode;
            -- size;
        }
    }
    //打印链表
    void toString()
    {
        Node* cur = dummyHead->next;
        while(cur != nullptr)
        {
            if(cur->next == nullptr)
            {
                std::cout << cur->e;
                break;
            }
            std::cout << cur->e << "->";
            cur = cur->next;
        }
    }
    void toString2()
    {
        std::cout << "dummyHead->";
        Node* cur = dummyHead->next;
        while(cur != nullptr)
        {
            std::cout << cur->e << "->";
            cur = cur->next;
        }
        std::cout << "Null" << std::endl;
    }
};
#endif //LINKEDLIST_LINKEDLIST_H
