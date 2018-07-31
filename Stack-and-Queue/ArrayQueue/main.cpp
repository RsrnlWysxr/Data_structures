#include <iostream>
#include "ArrayQueue.h"
using namespace std;

int main()
{
    ArrayQueue<int>* queue = new ArrayQueue<int>();
    for (int i = 0; i < 10 ; ++i)
    {
        queue->enQueue(i);
    }
    queue->toString();
    cout << "Front:" << queue->getFront() << endl;
    for (int j = 0; j < 5 ; ++j)
    {
        queue->deQueue();
    }
    queue->toString();
    cout << "Front:" << queue->getFront() << endl;
    return 0;
}