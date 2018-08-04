#include <iostream>
#include "LinkedQueue.h"

int main()
{
    LinkedQueue<int>* link = new LinkedQueue<int>();
    for(int i = 0 ; i < 10 ; ++i)
    {
        link->enqueue(i);
    }
    link->toString();
    std::cout << "size:" << link->getSize() << std::endl;
    std::cout << "getFront:" << link->getFront() << std::endl;
    std::cout << "dequeue:" << link->dequeue() << std::endl;
    link->toString();
}