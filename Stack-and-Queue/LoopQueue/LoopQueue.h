//
// Created by Administrator on 2018/8/1/001.
//

#ifndef LOOPQUEUE_LOOPQUEUE_H
#define LOOPQUEUE_LOOPQUEUE_H

//定义纯虚类作为接口
template < typename T >
class Queue
{
    virtual int getSize() const = 0;        //获取Queue元素个数
    virtual bool isEmpty() const = 0;       //判断Queue是否为空
    virtual T getFront() const = 0;         //获取队首元素
    virtual void enQueue(T e) = 0;          //入队
    virtual T deQueue() = 0;                //出队
};
template < typename T >
class LoopQueue:public Queue<T>
{
private:
    T* data;
    int front,tail,realcapacity;

public:
    LoopQueue()     //浪费一个空间
    {
        realcapacity = 11;
        data = new T[realcapacity];
        front = 0;
        tail = 0;
    }
    LoopQueue(int capacity)
    {
        realcapacity = capacity + 1;
        data = new T[realcapacity];
        front = 0;
        tail = 0;
    }
    ~LoopQueue()
    {
        delete [] data;
    }
    int getCapacity() const
    {
        return realcapacity - 1;
    }
    int getSize() const
    {
        return (tail + realcapacity - front) % realcapacity;
    }
    bool isEmpty() const
    {
        return (tail == front);
    }
    bool isFull() const
    {
        return (tail + 1 == front);
    }
    T getFront() const
    {
        if(isEmpty())
            throw "This queue is empty";
        return data[front];
    }
    void enQueue(T e)
    {
        if((tail + 1) % realcapacity == front)
            resize(realcapacity * 2 - 1);
        data[tail] = e;
        tail = (tail + 1) % realcapacity;
    }
    T deQueue()
    {
        if(isEmpty())
            throw "This queue is empty";
        T ret = getFront();
        data[front] = 0;
        front = (front + 1) % realcapacity;
        if(getSize() <= (realcapacity - 1) / 4 && getSize() / 2 != 0)
            resize((realcapacity + 1) / 2);
        return ret;
    }
    void toString()
    {
        std::cout << "Queue: size = " << getSize() << ", capacity = " << realcapacity - 1 << std::endl;
        std::cout << "front [";
        for (int i = front; i != tail; i = (i + 1) % realcapacity)
        {
            std::cout << data[i];
            if ((i + 1) % realcapacity != tail)
            {
                std::cout << ", ";
            }
        }
        std::cout << "] tail" << std::endl;
    }

private:
    void resize(int newcapacity)
    {
        T* newdata = new T[realcapacity];
        for (int i = 0; i < getSize(); ++i)
            newdata[i] = data[(front + i) % realcapacity];
        data = newdata;
        front = 0;
        tail = getSize();
        realcapacity = newcapacity;
    }
};

#endif //LOOPQUEUE_LOOPQUEUE_H
