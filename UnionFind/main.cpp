#include <iostream>
#include "UnionFind.h"

using namespace std;

int main()
{
    srand(time(NULL));
    int n = 10000000;
    clock_t start = clock();
    UnionFind u(n);
    for(int i = 0 ; i < n ; i++)
    {
        int a = rand() % n;
        int b = rand() % n;
        u.find(a);
        u.find(b);
        u.isConnected(a,b);
        u.unionElements(a,b);
    }
    clock_t end = clock();
    cout << 2 * n << "ops  time:" << double(end - start) / CLOCKS_PER_SEC << "s" << endl;
    return 0;
}