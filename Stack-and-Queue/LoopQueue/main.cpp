#include <iostream>
#include "LoopQueue.h"
int main()
{
    auto queue = new LoopQueue<int>();
    for (int i = 0; i < 10; ++i)
    {
        queue->enQueue(i);
        queue->toString();
    }
    queue->enQueue(20);
    queue->enQueue(33);
    queue->toString();
    queue->deQueue();
    queue->toString();
    std::cout << "Front:" << queue->getFront() << std::endl;
    return 0;
}