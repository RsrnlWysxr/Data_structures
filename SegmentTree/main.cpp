#include <iostream>
#include <functional>
#include <algorithm>
#include "Segment_Tree.h"
using namespace std;

int reFun( int x , int y )
{
    if( x > y)
        return x;
    else return y;
}

int main()
{
    int arr[] ={0,1,2,3,4,5,6};
    auto fun = reFun;
    SegmentTree<int>* tree = new SegmentTree<int>(arr,sizeof(arr) / sizeof(int),fun);
    tree->toString();
    cout << tree->query(0,3) << endl;
    tree->set(3,10);
    cout << tree->query(0,3) << endl;
    tree->toString();
    return 0;
}