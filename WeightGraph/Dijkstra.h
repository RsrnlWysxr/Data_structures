//
// Created by Administrator on 2018/8/14/014.
//

#ifndef WEIGTHGRAPH_DIJKSTRA_H
#define WEIGTHGRAPH_DIJKSTRA_H

#include <iostream>
#include <vector>
#include <stack>
#include "Edge.h"
#include "IndexMinHeap.h"
using namespace std;

template <typename Graph,typename Weight>
class Dijkstra
{
private:
    Graph &G;           // 图的引用
    int s;              // 源点
    bool *marked;       // 标记数组，标记节点是否已被访问过,代表已经找到到该点的最短路径
    Weight* distTo;      // distTo[i]存储从起始点s到i的最短路径长度
    vector<Edge<Weight>*> from;     // from[i]记录最短路径中, 到达i点的边是哪一条
                                    // 可以用来恢复整个最短路径
public:
    Dijkstra(Graph &graph,int s):G(graph)
    {
        // 算法初始化
        assert(s >= 0 && s < G.V());
        this->s = s;
        marked = new bool[G.V()];
        distTo = new Weight[G.V()];
        for (int i = 0; i < G.V(); ++i)
        {
            marked[i] = false;
            distTo[i] = Weight();
            from.push_back(nullptr);
        }
        // 使用索引堆记录当前找到的到达每个顶点的最短距离
        IndexMinHeap<Weight> ipq(G.V());
        // 对于起始点s进行初始化
        distTo[s] = Weight();
        from[s] = new Edge<Weight>(s,s,Weight());
        marked[s] = true;
        ipq.add(s,distTo[s]);
        while ( !ipq.isEmpty() )
        {
            int v = ipq.extractMaxIndex();
            // distTo[v]就是s到v的最短距离
            marked[v] = true;
            // 对v的所有相邻节点进行更新
            typename Graph::adjIterator adj(G,v);
            for(Edge<Weight>* i = adj.begin(); !adj.end() ; i = adj.next())
            {
                int w = i->other(v);
                // 如果从s点到w点的最短路径还没有找到
                if( !marked[w] )
                {
                    // 如果w点以前没有访问过,
                    // 或者访问过, 但是通过当前的v点到w点距离更短, 则进行更新
                   if( from[w] == nullptr || distTo[w] > distTo[v] + i->wt())
                   {
                       distTo[w] = distTo[v] + i->wt();
                       from[w] = i;
                       if( ipq.contain(w))
                           ipq.change(w,distTo[w]);
                       else
                           ipq.add(w,distTo[w]);
                   }
                }
            }
        }
    }
    ~Dijkstra()
    {
        delete[] distTo;
        delete[] marked;
        delete[] from[0];
    }
    // 返回从s点到w点的最短路径长度
    Weight shortestPathTo(int w)
    {
        assert( w >= 0 && w < G.V() );
        assert( hasPathTo(w) );
        return distTo[w];
    }
    // 判断从s点到w点是否联通
    bool hasPathTo( int w )
    {
        assert( w >= 0 && w < G.V() );
        return marked[w];
    }
    // 寻找从s到w的最短路径, 将整个路径经过的边存放在vec中
    void shortestPath( int w, vector<Edge<Weight>> &vec )
    {
        assert(w >= 0 && w < G.V());
        assert(hasPathTo(w));

        // 通过from数组逆向查找到从s到w的路径, 存放到栈中
        stack<Edge<Weight> *> s;
        Edge<Weight> *e = from[w];
        while (e->v() != this->s)
        {
            s.push(e);
            e = from[e->v()];
        }
        s.push(e);

        // 从栈中依次取出元素, 获得顺序的从s到w的路径
        while (!s.empty())
        {
            e = s.top();
            vec.push_back(*e);
            s.pop();
        }
    }
    // 打印出从s点到w点的路径
    void showPath(int w)
    {
        assert( w >= 0 && w < G.V() );
        assert( hasPathTo(w) );

        vector<Edge<Weight>> vec;
        shortestPath(w, vec);
        for( int i = 0 ; i < vec.size() ; i ++ )
        {
            cout<<vec[i].v()<<" -> ";
            if( i == vec.size()-1 )
                cout<<vec[i].w()<<endl;
        }
    }

};
#endif //WEIGTHGRAPH_DIJKSTRA_H
