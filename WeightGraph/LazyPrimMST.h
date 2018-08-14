//
// Created by Administrator on 2018/8/14/014.
//

#ifndef WEIGTHGRAPH_LAZYPRIMMST_H
#define WEIGTHGRAPH_LAZYPRIMMST_H

#include <iostream>
#include <queue>
#include <cassert>
#include <vector>
#include "Edge.h"

using namespace std;

template <typename Graph, typename Weight>
class LazyPrimMST
{
private:
    Graph &G;                               // 图的引用
    priority_queue<Edge<Weight>,vector<Edge<Weight>>,greater<Edge<Weight>>> pq;        // 最小堆，放入边
    bool *marked;                          // 标记数组，确认节点是否已被访问
    vector<Edge<Weight>> mst;               // 记录最小生成树包含的所有边
    Weight mstWeight;                          // 记录权值

    // 访问一个节点进行的操作
    void visit(int v)
    {
        assert( !marked[v] );
        marked[v] = true;
        // 制作该节点的邻边迭代器
        // 将和节点v相连接的所有未访问的边放入最小堆中
        typename Graph::adjIterator adj(G,v);
        for( Edge<Weight>* i = adj.begin(); !adj.end(); i = adj.next() )
            if( !marked[i->other(v)] )
                pq.push(*i);
    }

public:
    LazyPrimMST(Graph &graph):G(graph)
    {
        // 算法初始化
        pq = priority_queue<Edge<Weight>,vector<Edge<Weight>>,greater<Edge<Weight>>>();         // 最小堆中放边,自定义为逆序排列（小到大）
        marked = new bool[G.V()];                   // marked保存节点信息，即开节点数个空间
        for (int i = 0; i < G.V(); ++i)
        {
            marked[i] = false;      // 默认都没有被访问
        }
        mst.clear();

        // Lazy Prim
        visit(0);
        while ( !pq.empty() )
        {
            // 使用最小堆找出已经访问的边中权值最小的边
            Edge<Weight> e = pq.top();
            pq.pop();
            // 如果已经被访问了，则扔掉这条边
            if( marked[e.w()] == marked[e.v()])
                continue;
            // 否则，放入最小生成树中
            mst.push_back(e);
            // 接下来访问和这条边相连，还未被访问的点
            if( !marked[e.v()] )
                visit( e.v() );
            else
                visit( e.w() );
        }
        // 计算最小生成树的权值
        // 初始化mstWeight
        mstWeight = mst[0].wt();
        for (int j = 1; j < mst.size(); ++j)
        {
            mstWeight += mst[j].wt();
        }
    }
    // 析构函数
    ~LazyPrimMST()
    {
        delete[] marked;
    }
    // 返回最小生成树的所有边
    vector<Edge<Weight>> mstEdges()
    {
        return mst;
    }
    // 返回最小生成树的权值
    Weight result()
    {
        return mstWeight;
    }
};
#endif //WEIGTHGRAPH_LAZYPRIMMST_H
