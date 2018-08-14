//
// Created by Administrator on 2018/8/14/014.
//

#ifndef WEIGTHGRAPH_BELLMANFOLD_H
#define WEIGTHGRAPH_BELLMANFOLD_H

#include <iostream>
#include <stack>
#include <vector>
#include "Edge.h"

template <typename Graph, typename Weight>
class BellmanFord
{
private:
    Graph &G;           // 图的引用
    int s;              // 源点
    Weight* distTo;      // distTo[i]存储从起始点s到i的最短路径长度
    vector<Edge<Weight>*> from;     // from[i]记录最短路径中, 到达i点的边是哪一条
                                    // 可以用来恢复整个最短路径
    bool hasNegativeCycle;          // 标记图中是否有负权环

    // 判断图中是否有负权环
    bool detectNegativeCycle()
    {
        for( int i = 0 ; i < G.V() ; i ++ )
        {
            typename Graph::adjIterator adj(G,i);
            for(Edge<Weight>* e = adj.begin(); !adj.end() ; e = adj.next())
            {
                if( !from[e->w()] || distTo[e->w()] > distTo[e->v()] + e->wt())
                    return  true;
            }
        }
        return false;
    }

public:
    BellmanFord(Graph &graph,int s):G(graph)
    {
        // 算法初始化
        assert(s >= 0 && s < G.V());
        this->s = s;
        distTo = new Weight[G.V()];
        for (int i = 0; i < G.V(); ++i)
        {
            distTo[i] = Weight();
            from.push_back(nullptr);
        }
        // 对于起始点s进行初始化
        distTo[s] = Weight();
        from[s] = new Edge<Weight>(s,s,Weight());

        // Bellman-Ford的过程
        // 进行V-1次循环, 每一次循环求出从起点到其余所有点, 最多使用pass步可到达的最短距离
        for(int pass = 1 ; pass < G.V() ; pass++)
        {
            // 每次循环中对所有的边进行一遍松弛操作
            // 遍历所有边的方式是先遍历所有的顶点, 然后遍历和所有顶点相邻的所有边
            for(int i = 0 ; i < G.V() ; i++)
            {
                // 对e的所有边进行遍历
                typename Graph::adjIterator adj(G,i);
                for(Edge<Weight>* e = adj.begin(); !adj.end() ; e = adj.next())
                {
                    // 对于每一个边首先判断e->v()可达
                    // 之后看如果e->w()以前没有到达过， 可以更新distTo[e->w()]
                    // 或者e->w()以前虽然到达过, 但是通过这个e可以获得一个更短的距离, 即可以进行一次松弛操作, 也可以更新distTo[e->w()]
                    if( !from[e->w()] || distTo[e->w()] > distTo[e->v()] + e->wt())
                    {
                        distTo[e->w()] = distTo[e->v()] + e->wt();
                        from[e->w()] = e;
                    }
                }
            }
        }
        hasNegativeCycle = detectNegativeCycle();
    }
    ~BellmanFord()
    {
        delete[] distTo;
        delete[] from[0];
    }
    // 返回图中是否有负权环
    bool negativeCycle()
    {
        return hasNegativeCycle;
    }

    // 返回从s点到w点的最短路径长度
    Weight shortestPathTo( int w )
    {
        assert( w >= 0 && w < G.V() );
        assert( !hasNegativeCycle );
        assert( hasPathTo(w) );
        return distTo[w];
    }

    // 判断从s点到w点是否联通
    bool hasPathTo( int w )
    {
        assert( w >= 0 && w < G.V() );
        return from[w] != NULL;
    }

    // 寻找从s到w的最短路径, 将整个路径经过的边存放在vec中
    void shortestPath( int w, vector<Edge<Weight>> &vec )
    {
        assert( w >= 0 && w < G.V() );
        assert( !hasNegativeCycle );
        assert( hasPathTo(w) );

        // 通过from数组逆向查找到从s到w的路径, 存放到栈中
        stack<Edge<Weight>*> s;
        Edge<Weight> *e = from[w];
        while( e->v() != this->s )
        {
            s.push(e);
            e = from[e->v()];
        }
        s.push(e);

        // 从栈中依次取出元素, 获得顺序的从s到w的路径
        while( !s.empty() )
        {
            e = s.top();
            vec.push_back( *e );
            s.pop();
        }
    }

    // 打印出从s点到w点的路径
    void showPath(int w)
    {
        assert( w >= 0 && w < G.V() );
        assert( !hasNegativeCycle );
        assert( hasPathTo(w) );

        vector<Edge<Weight>> vec;
        shortestPath(w, vec);
        for( int i = 0 ; i < vec.size() ; i ++ )
        {
            cout << vec[i].v() << " -> ";
            if( i == vec.size()-1 )
                cout << vec[i].w() << endl;
        }
    }
};
#endif //WEIGTHGRAPH_BELLMANFOLD_H
