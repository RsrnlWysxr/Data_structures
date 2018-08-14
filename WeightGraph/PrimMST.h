//
// Created by Administrator on 2018/8/14/014.
//

#ifndef WEIGTHGRAPH_PRIMMST_H
#define WEIGTHGRAPH_PRIMMST_H
#include <iostream>
#include <queue>
#include <cassert>
#include <vector>
#include "Edge.h"
#include "IndexMinHeap.h"

using namespace std;

template <typename Graph, typename Weight>
class PrimMST
{
private:
    Graph &G;                               // 图的引用
    IndexMinHeap<Weight> ipq;               // 最小索引堆，放入每个节点目前最小的权值
    vector<Edge<Weight>*> edgeTo;           // 访问的点所对应的边, 算法辅助数据结构
    bool *marked;                          // 标记数组，确认节点是否已被访问
    vector<Edge<Weight>> mst;               // 记录最小生成树包含的所有边
    Weight mstWeight;                       // 记录权值

    // 访问一个节点进行的操作
    void visit(int v)
    {
        assert( !marked[v] );
        marked[v] = true;
        // 制作该节点的邻边迭代器
        // 将和节点v相连接的未访问的另一端点, 和与之相连接的边, 放入最小堆中
        typename Graph::adjIterator adj;
        for( Edge<Weight>* i = adj.begin(); adj.end(); i = adj.next())
        {
            int w = i->other(v);
            // 如果边的另一端点未被访问
            if( !marked[w] )
            {
                // 如果从没有考虑过这个端点, 直接将这个端点和与之相连接的边加入索引堆
                if ( !edgeTo[w] )
                {
                    edgeTo[w] = i;
                    ipq.add( w, i->wt() );
                }
                // 如果曾经考虑这个端点, 但现在的边比之前考虑的边更短, 则进行替换
                else if ( edgeTo[w]->wt() > i->w())
                {
                    edgeTo[w] = i;
                    ipq.change( w, i->wt() );
                }
            }
        }

    }

public:
    PrimMST(Graph &graph):G(graph),ipq(IndexMinHeap<Weight>(G.V()))
    {
        // 算法初始化
        marked = new bool[G.V()];                   // marked保存节点信息，即开节点数个空间
        for (int i = 0; i < G.V(); ++i)
        {
            marked[i] = false;      // 默认都没有被访问
            edgeTo.push_back(nullptr);
        }
        mst.clear();

        // Lazy Prim
        visit(0);
        while ( !ipq.isEmpty() )
        {
            // 使用最小索引堆找出已经访问的边中权值最小的边
            // 最小索引堆中存储的是点的索引, 通过点的索引找到相对应的边
            int v = ipq.extractMaxIndex();
            assert( edgeTo[v] );
            mst.push_back( *edgeTo[v] );
            visit( v );
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
    ~PrimMST()
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
#endif //WEIGTHGRAPH_PRIMMST_H
