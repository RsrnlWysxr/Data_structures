#include <iostream>
#include "LinkedStack.h"
int main()
{
    LinkedStack<int>* link = new LinkedStack<int>();
    for(int i = 0 ; i < 10 ; ++i)
    {
        link->push(i);
    }
    link->toString();
    std::cout << "size:" << link->getSize() << std::endl;
    std::cout << "peek:" << link->peek() << std::endl;
    std::cout << "pop:" << link->pop() << std::endl;
    link->toString();
}