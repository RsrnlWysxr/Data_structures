#include <iostream>
#include "DenseGraph.h"
#include "SparseGraph.h"
#include "ReadGraph.h"
#include "Path.h"
#include "Component.h"
#include "ShortPath.h"

using namespace std;

int main()
{
    string filename = "textG1.txt";
    SparseGraph g1(13, false);
    ReadGraph<SparseGraph> readGraph(g1,filename);
    g1.show();
    ShortPath<SparseGraph> shortPath(g1,0);
    shortPath.showPath(4);
    cout << shortPath.length(4);
//    Component<SparseGraph> component(g1);
//    cout << component.count() << endl;
//    cout << component.isConnected(0,8) << endl;
//    Path<SparseGraph> p1(g1,0);
//    p1.showPath(6);
//    cout << "/////////////////////////////////////////" << endl;
//    DenseGraph g2(13, false);
//    ReadGraph<DenseGraph>readGraph1(g2,filename);
//    g2.show();













    //    int N = 20;
//
//    srand(time(NULL));
//
//    // Sparse Graph
//    SparseGraph g1(N, false);
//    for(int i = 0 ; i < N; i++)
//    {
//        int a = rand() % N;
//        int b = rand() % N;
//        g1.addEdge(a,b);
//    }
//
//    // O(E)
//    for(int v = 0; v < N; v++)
//    {
//        cout << v << ":";
//        SparseGraph::adjIterator adj(g1,v);
//        for(auto it = adj.begin(); !adj.end(); it = adj.next())
//            cout << it << " ";
//        cout << endl;
//    }
//
//    cout << "//////////////////////////////////////////////////" << endl;
//
//    DenseGraph g2(N, false);
//    for(int i = 0; i < N; i++)
//    {
//        int a = rand() % N;
//        int b = rand() % N;
//        g2.addEdge(a,b);
//    }
//
//    // O(V^2)
//    for (int v = 0; v < N; ++v)
//    {
//        cout << v << ":";
//        DenseGraph::adjIterator adj(g2,v);
//        for(auto it = adj.begin(); !adj.end() ; it = adj.next())
//            cout << it << " ";
//        cout << endl;
//    }
    return 0;
}