#include <iostream>
#include <iomanip>
#include "DenseGraph.h"
#include "SparseGraph.h"
#include "ReadGraph.h"
#include "LazyPrimMST.h"
#include "PrimMST.h"
#include "KruskalMST.h"

using namespace std;


int main()
{
    // 测试最小生成树算法
    string filename = "textG1.txt";
    int V = 8;

    SparseGraph<double> g = SparseGraph<double>(V, false);
    ReadGraph<SparseGraph<double>, double> readGraph(g, filename);

    // Test Prim MST
    cout << "Test Kruskal MST:" << endl;
    KruskalMST<SparseGraph<double>, double> kruskalMST(g);
    vector<Edge<double>> mstk = kruskalMST.mstEdges();
    for( int i = 0 ; i < mstk.size() ; i ++ )
        cout<< mstk[i] <<endl;
    cout<< "The MST weight is: " << kruskalMST.result() << endl;
    cout << endl;

    // Test Prim MST
    cout << "Test Prim MST:" << endl;
    // 算法复杂度 O(E logV)
    LazyPrimMST<SparseGraph<double>, double> PrimMST(g);
    vector<Edge<double>> mst = PrimMST.mstEdges();
    for( int i = 0 ; i < mst.size() ; i ++ )
        cout<< mst[i] <<endl;
    cout<< "The MST weight is: " << PrimMST.result() << endl;
    cout << endl;

    // Test Lazy Prim MST
    cout << "Test Lazy Prim MST:" << endl;
    // 算法复杂度 O(E logE)
    LazyPrimMST<SparseGraph<double>, double> lazyPrimMST(g);
    vector<Edge<double>> mstLazy = lazyPrimMST.mstEdges();
    for( int i = 0 ; i < mstLazy.size() ; i ++ )
        cout<< mstLazy[i] <<endl;
    cout<< "The MST weight is: " << lazyPrimMST.result() << endl;
    cout << endl;

// 测试有权图和有权图的读取
//    string filename = "textG1.txt";
//    int V = 8;
//    cout<<fixed<<setprecision(2);
//
//    // Test Weighted Dense Graph
//    DenseGraph<double> g1 = DenseGraph<double>(V, false);
//    ReadGraph<DenseGraph<double>,double> readGraph1(g1, filename);
//    g1.show();
//    cout<<endl;
//
//    // Test Weighted Sparse Graph
//    SparseGraph<double> g2 = SparseGraph<double>(V, false);
//    ReadGraph<SparseGraph<double>,double> readGraph2(g2, filename);
//    g2.show();
//    cout<<endl;

    return 0;
}