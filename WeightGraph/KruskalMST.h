//
// Created by Administrator on 2018/8/14/014.
//

#ifndef WEIGTHGRAPH_KRUSKALMST_H
#define WEIGTHGRAPH_KRUSKALMST_H

#include <iostream>
#include <vector>
#include <queue>
#include "Edge.h"
#include "UnionFind.h"

using namespace std;

template <typename Graph, typename Weight>
class KruskalMST
{
private:
    // 不需要辅助函数
    vector<Edge<Weight>> mst;      // MST所包含的边
    Weight mstWeight;               // MST的权值

public:
    // 构造函数, 使用Kruskal算法计算graph的最小生成树
    KruskalMST(Graph &graph)
    {
        auto pq = priority_queue<Edge<Weight>,vector<Edge<Weight>>,greater<Edge<Weight>>>();
        // 将所有点的邻边加入到最小索引堆中
        for(int i = 0; i < graph.V(); ++i)
        {
            // 制作当前节点的邻边迭代器
            typename Graph::adjIterator adj(graph,i);
            for(Edge<Weight>* j = adj.begin(); !adj.end(); j = adj.next())
            {
                 if( j->w() > j->v() )
                     pq.push(*j);
            }
        }
        // 创建一个并查集, 来查看已经访问的节点的联通情况
        UnionFind uf = UnionFind(graph.V());
        mst.clear();
        while( !pq.empty() && mst.size() < graph.V())
        {
            // 从最小堆中依次从小到大取出所有的边
            Edge<Weight> e = pq.top();
            pq.pop();
            // 如果该边的两个端点是联通的, 说明加入这条边将产生环, 扔掉这条边
            if ( uf.isConnected( e.v(),e.w() ) )
                continue;
            // 否则, 将这条边添加进最小生成树, 同时标记边的两个端点联通
            mst.push_back(e);
            uf.unionElements( e.v(),e.w() );
        }
        mstWeight = mst[0].wt();
        for(int i = 1; i < mst.size(); ++i)
            mstWeight += mst[i].wt();
    }
    ~KruskalMST(){}
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
#endif //WEIGTHGRAPH_KRUSKALMST_H
