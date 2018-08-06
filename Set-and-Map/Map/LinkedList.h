//
// Created by Administrator on 2018/8/4/004.
//

#ifndef LINKEDLIST_LINKEDLIST_H
#define LINKEDLIST_LINKEDLIST_H

template <typename T,typename V>
class LinkedList
{
private:
    class Node
    {
    public:
        T e;
        V v;
        Node* next;
        Node():next(nullptr){}
        Node(T e,V v):e(e),v(v),next(nullptr){}
        Node(T e,V v,Node* next):e(e),v(v),next(next){}
        ~Node(){next = nullptr;}
    };
    Node* dummyHead;
    int size;
    // 递归实现释放空间
    void destroy(Node* node)
    {
        if(!node->next)
        {
            destroy(node->next);
            delete node;
            -- size;
        }
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
    // 获取元素e的值value
    V getValue(T e)
    {
        Node* cur = dummyHead->next;
        while(cur)
        {
            if(e == cur->e)
                return cur->v;
            cur = cur->next;
        }
        return 0;
    }
    // 在链表的index(0-based)位置添加新的元素e
    void add(int index,T e,V v)
    {
        if(index > size || index < 0 )
            throw "This index is Error.";
        Node* prev = dummyHead;
        for(int i = 0 ; i < index ; ++i)
        {
            prev = prev->next;
        }
        prev->next = new Node(e,v,prev->next);
        ++size;
    }
    // 在链表头添加新的元素e
    void addFirst(T e,V v)
    {
        add(0,e,v);
    }
    // 在链表末尾添加新的元素e
    void addLast(T e,V v)
    {
        add(size,e,v);
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
    // 修改链表元素为e的value值
    void set2(T e,V v)
    {
        Node* cur = dummyHead->next;
        while(cur)
        {
            if(e == cur->e)
            {
                cur->v = v;
                break;
            }
            cur = cur->next;
        }
        return;
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
        retNode->next = nullptr;
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
    V removeElement(T e)
    {
        Node* prev = dummyHead;
        while(prev->next != nullptr)
        {
            if(prev->next->e == e)
                break;
            prev = prev->next;
        }   // 循环结束表示找到e所在节点的前一个节点 或 null
        if(prev->next != nullptr)
        {
            Node* delNode = prev->next;
            prev->next = delNode->next;
            delNode->next = nullptr;
            -- size;
            return delNode->v;
        }
        return -1;
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
            std::cout << cur->e << ":" << cur->v << "->";
            cur = cur->next;
        }
    }
    void toString2()
    {
        std::cout << "dummyHead->";
        Node* cur = dummyHead->next;
        while(cur != nullptr)
        {
            std::cout << cur->e << ":" << cur->v << "->";
            cur = cur->next;
        }
        std::cout << "Null" << std::endl;
    }
};
#endif //LINKEDLIST_LINKEDLIST_H
