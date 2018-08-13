//
// Created by Administrator on 2018/8/13/013.
//

#ifndef GRAPH_PATH_H
#define GRAPH_PATH_H

#include <iostream>
#include <stack>
#include <cassert>
#include <vector>
using namespace std;
// 路径查询
template <typename Graph>
class Path
{
    Graph& G;       // 接收传入图的引用
    int v;          // 起始点
    bool* visited;   // 记录是否已被遍历到
    int* from;      // 记录来路,from[i]表示查找的路径上i的上一个节点

    // 图的深度优先遍历
    void dfs(int v)
    {
        // 每访问到一个节点，即将相应visited置为真
        visited[v] = true;
        // 使用自己制作的邻边迭代器遍历顶点v的边
        typename Graph::adjIterator adj(G,v);
        for( auto it = adj.begin(); !adj.end(); it = adj.next())
        {
            if(!visited[it])
            {
                from[it] = v;
                dfs(it);
            }
        }
    }

public:
    // 构造函数, 寻路算法, 寻找图graph从s点到其他点的路径
    Path(Graph& graph , int v):G(graph),v(v)
    {
        assert( v >= 0 && v < G.V());
        visited = new bool[G.V()];
        from = new int[G.V()];
        for (int i = 0; i < G.V(); ++i)
        {
            from[i] = -1;           // -1 表无来路
            visited[i] = false;     // 默认每个节点未遍历
        }
        // 寻路算法
        dfs(v);
    }
    ~Path()
    {
        delete[] visited;
        delete[] from;
    }

    // 判断v到w是否有路径
    bool hasPath(int w)
    {
        assert( w >= 0 && w < G.V() );
        return visited[w];
    }
    // 查询从v点到w点的路径, 存放在vec中
    void path(int w , vector<int>& vec)
    {
        assert( hasPath(w) );
        stack<int> s;
        // 通过from数组逆向查找到从v到w的路径, 存放到栈中
        int p = w;
        while( from[p] != -1 )
        {
            s.push(from[p]);
            p = from[p];
        }
        vec.clear();
        while (!s.empty())
        {
            vec.push_back(s.top());
            s.pop();
        }
    }
    // 打印出从v点到w点的路径
    void showPath(int w)
    {
        assert( hasPath(w) );
        vector<int> vec;
        path(w,vec);
        for (int i = 0; i < vec.size(); ++i)
        {
            cout << vec[i];
            if( i == vec.size() - 1)
                cout << "->" << w << endl;
            else
                cout << "->";
        }
    }
};
#endif //GRAPH_PATH_H
