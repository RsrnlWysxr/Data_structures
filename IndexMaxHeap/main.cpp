#include <iostream>
#include "IndexMaxHeap.h"

using namespace std;

int main()
{
    auto heap = new IndexMaxHeap<int>(5);
    heap->add(0,3);
    heap->add(1,2);
    heap->add(2,0);
    heap->add(3,4);
    heap->add(4,5);
    cout << heap->extractMax() << endl;
    heap->change(2,6);
    heap->toSting();
    cout << endl;
    cout << heap->extractMax() << endl;
    return 0;
}