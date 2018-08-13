//
// Created by Administrator on 2018/8/13/013.
//

#ifndef GRAPH_COMPONENT_H
#define GRAPH_COMPONENT_H

#include <iostream>
#include <cassert>

template < typename Graph>
class Component
{
private:
    Graph &G;       // 图的引用
    int ccount;     // 记录联通分量个数
    bool* visited;  // 记录节点是否已被访问
    int* id;        // 每个节点所对应联通分量的标记

    // 图的深度优先遍历
    void dfs(int v)
    {
        visited[v] = true;      // 标记已访问元素
        id[v] = ccount;
        typename Graph::adjIterator adj(G,v);
        for (int i = adj.begin(); !adj.end(); i = adj.next())
        {
            if(!visited[i])
                dfs(i);
        }
    }

public:
    // 构造函数, 求出无权图的联通分量
    explicit Component(Graph &graph):G(graph)
    {
        visited = new bool[G.V()];
        id = new int[G.V()];
        for (int i = 0; i < G.V(); ++i)
        {
            visited[i] = false;
            id[i] = -1;
        }
        ccount = 0;

        // 求图的联通分量
        for (int j = 0; j < G.V(); ++j)
        {
            if(!visited[j])
            {
                dfs(j);
                ccount++;
            }

        }
    }
    ~Component()
    {
        delete[] visited;
        delete[] id;
    }
    // 返回图的联通分量个数
    int count()
    {
        return ccount;
    }
    // 查询点v和点w是否联通
    bool isConnected(int v , int w)
    {
        assert( v >= 0 && v < G.V());
        assert( w >= 0 && w < G.V());
        return id[v] == id[w];
    }
};
#endif //GRAPH_COMPONENT_H
