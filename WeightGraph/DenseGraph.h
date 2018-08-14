//
// Created by Administrator on 2018/8/13/013.
//

#ifndef GRAPH_DENSEGRAPH_H
#define GRAPH_DENSEGRAPH_H

#include <iostream>
#include <vector>
#include <cassert>
#include "Edge.h"

using namespace std;

// 稠密图 - 邻接矩阵
template < typename Weight>
class DenseGraph
{
private:
    int n;      // 节点数
    int m;      // 边数
    bool directed;  // 是否为有向图
    vector<vector<Edge<Weight>*>> g;     // 邻接矩阵

public:
    // 构造函数
    DenseGraph(int n,bool directed):n(n),directed(directed)
    {
        m = 0;      // 初始化边数为0
        // g初始化为n*n的布尔矩阵, 每一个g[i][j]均为false, 表示没有任和边
        g = vector<vector<Edge<Weight>*>>(n, vector<Edge<Weight>*>(n,NULL));
    }
    ~DenseGraph()
    {
        for (int i = 0; i < n; ++i)
        {
            for (int j = 0; j < n; ++j)
            {
                if( g[i][j] != NULL)
                    delete g[i][j];
            }
        }
    }

    int V(){ return n; }    // 返回节点数
    int E(){ return m; }    // 返回边数

    // 向图中添加一个边
    // 默认无平行边
    void addEdge(int v, int w, Weight weight)
    {
        assert( v >= 0 && v < n);
        assert( w >= 0 && w < n);
        // 如果从v到w已经有边, 删除这条边
        if (hasEdge(v,w))
        {
            delete g[v][w];
            if( v != w && !directed)
                delete g[w][v];
            m--;
        }

        g[v][w] = new Edge<Weight>(v,w,weight);
        if( v != w && !directed)
            g[w][v] = new Edge<Weight>(v,w,weight);
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
                if( g[i][j] )
                    cout << g[i][j]->wt() << "\t";
                else
                    cout << "NULL\t";
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
        Edge<Weight>* begin()
        {
            // 索引从-1开始, 因为每次遍历都需要调用一次next()
            index = -1;
            return next();
        }
        Edge<Weight>* next()
        {
            // 从当前index开始向后搜索, 直到找到一个g[v][index]为true
            for(index += 1; index < G.n ; index ++)
            {
                if( G.g[v][index] )
                    return G.g[v][index];
                // 若没有顶点和v相连接, 则返回-1
                return NULL;
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
