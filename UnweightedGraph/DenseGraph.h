//
// Created by Administrator on 2018/8/13/013.
//

#ifndef GRAPH_DENSEGRAPH_H
#define GRAPH_DENSEGRAPH_H

#include <iostream>
#include <vector>
#include <cassert>
using namespace std;

// 稠密图 - 邻接矩阵
class DenseGraph
{
private:
    int n;      // 节点数
    int m;      // 边数
    bool directed;  // 是否为有向图
    vector<vector<bool>> g;     // 邻接矩阵

public:
    // 构造函数
    DenseGraph(int n,bool directed):n(n),directed(directed)
    {
        m = 0;      // 初始化边数为0
        // g初始化为n*n的布尔矩阵, 每一个g[i][j]均为false, 表示没有任和边
        g = vector<vector<bool>>(n,vector<bool>(n,false));
    }
    ~DenseGraph(){}

    int V(){ return n; }    // 返回节点数
    int E(){ return m; }    // 返回边数

    // 向图中添加一个边
    // 默认无平行边
    void addEdge(int v,int w)
    {
        assert( v >= 0 && v < n);
        assert( w >= 0 && w < n);
        if (hasEdge(v,w))
            return;

        g[v][w] = true;
        if (!directed)
            g[w][v] = true;

        m++;
    }
    // 验证图中是否有从v到w的边
    bool hasEdge(int v,int w)
    {
        assert( v >= 0 && v < n);
        assert( w >= 0 && w < n);
        return g[v][w];
    }
    void show()
    {

        for( int i = 0 ; i < n ; i ++ )
        {
            for( int j = 0 ; j < n ; j ++ )
                cout << g[i][j] << "\t";
            cout << endl;
        }
    }

    // 邻边迭代器, 传入一个图和一个顶点,
    // 迭代在这个图中和这个顶点向连的所有顶点
    class adjIterator
    {
    private:
        DenseGraph &G;      // 图G的引用
        int v;      // 接收传入的节点
        int index;

    public:
        adjIterator(DenseGraph& graph,int v):G(graph)
        {
            assert( v >= 0 && v < G.n);
            this->v = v;
            this->index = -1;     // 索引从-1开始, 因为每次遍历都需要调用一次next()
        }
        ~adjIterator(){}

        // 返回图G中与顶点v相连接的第一个顶点
        int begin()
        {
            // 索引从-1开始, 因为每次遍历都需要调用一次next()
            index = -1;
            return next();
        }
        int next()
        {
            // 从当前index开始向后搜索, 直到找到一个g[v][index]为true
            for(index += 1; index < G.n ; index ++)
            {
                if(G.g[v][index])
                    return index;
                // 若没有顶点和v相连接, 则返回-1
                return -1;
            }
        }
        // 查看是否已经迭代完了图G中与顶点v相连接的所有顶点
        bool end()
        {
            return index >= G.n;
        }
    };
};
#endif //GRAPH_DENSEGRAPH_H
