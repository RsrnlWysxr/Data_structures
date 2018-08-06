#include <iostream>
#include "MaxHeap.h"
#include <cassert>
#include "Priority-Queue.h"
template <typename T>
long double test(T test[],int n,bool isHeapify)
{
    clock_t time1 = clock();
    MaxHeap<T>* maxHeap;
    if(isHeapify)
        maxHeap = new MaxHeap<T>(test,n);
    else
    {
        maxHeap = new MaxHeap<T>();
        for(int i = 0 ; i < n ; i++)
            maxHeap->add(test[i]);
    }
    T* arr = new T[n];
    for(int i = 0 ; i < n; i++)
    {
        arr[i] = maxHeap->extractMax();
    }
    for(int i = 1; i < n; i++)
    {
        assert(arr[i - 1] >= arr[i]);
    }
    std::cout << "Test MaxHeap completed." << std::endl;
    clock_t time2 = clock();
    return (double)(time2 - time1) / CLOCKS_PER_SEC;
}



int main() {
    int n = 1000000;
    int* testdata = new int[n];
    srand(time(NULL));
    for (int i = 0; i < n ; ++i)
    {
        testdata[i] = rand() % INT32_MAX;
    }
//    PriorityQueue<int>* priorityQueue = new PriorityQueue<int>();
//    for(int i = 0 ; i < n; i ++ )
//    {
//        priorityQueue->enqueue(testdata[i]);
//    }
//    for(int i = 0 ; i < n ; i ++ )
//    {
//        std::cout << priorityQueue->dequeue() <<",";
//    }
    double time1 = test(testdata, n, false);
    std::cout << "Without heapify :" << time1 << " s " << std::endl;
    double time2 = test(testdata, n, true);
    std::cout << "With heapify :" << time2 << " s " << std::endl;
    return 0;
}