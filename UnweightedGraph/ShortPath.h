//
// Created by Administrator on 2018/8/13/013.
//

#ifndef GRAPH_SHORTPATH_H
#define GRAPH_SHORTPATH_H

#include <iostream>
#include <cassert>
#include <queue>
#include <vector>
#include <stack>

using namespace std;

template <typename Graph>
class ShortPath
{
private:
    Graph &G;       // 图的引用
    int v;          // 起始点
    bool *visited;    // 记录是否已访问
    int *from;      // 记录路径，from[i]表示查找的路径上i的上一个节点
    int *ord;       // 记录路径中节点的次序。ord[i]表示i节点在路径中的次序。

public:
    ShortPath(Graph &graph,int v):G(graph)
    {
        assert( v >= 0 && v < G.V());
        this->v = v;
        visited = new bool[G.V()];
        from = new int[G.V()];
        ord = new int[G.V()];
        for (int i = 0; i < G.V(); ++i)
        {
            visited[i] = false;
            from[i] = -1;
            ord[i] = -1;
        }
        // 无向图最短路径算法, 从v开始广度优先遍历整张图
        // 使用队列结构辅助
        queue<int> q;

        q.push(v);
        visited[v] = true;
        ord[v] = 0;     // 设置起始点节点次序为0
        while(!q.empty())
        {
            int cur = q.front();
            q.pop();
            // 制作cur的邻边迭代器
            typename Graph::adjIterator adj(G,cur);
            for(auto it = adj.begin(); !adj.end(); it = adj.next())
            {
                if(!visited[it])
                {
                    q.push(it);
                    visited[it] = true;
                    from[it] = cur;
                    ord[it] = ord[cur] + 1;
                }
            }
        }
    }
    ~ShortPath()
    {
        delete[] visited;
        delete[] from;
        delete[] ord;
    }
    // 查询从v点到w点是否有路径
    bool hasPath( int w )
    {
        assert( w >= 0 && w < G.V());
        return visited[w];
    }
    // 查询从v点到w点的路径, 存放在vec中
    void path( int w , vector<int> &vec)
    {
        assert( hasPath(w) );

        // 通过from数组逆向查找到从v到w的路径, 存放到栈中
        stack<int> s;
        int p = from[w];
        while ( p != -1)
        {
            s.push(p);
            p = from[p];
        }
        vec.clear();
        // 从栈中依次取出元素, 获得顺序的从v到w的路径
        while ( !s.empty())
        {
            vec.push_back(s.top());
            s.pop();
        }
    }
    // 打印出从v点到w点的路径
    void showPath(int w)
    {
        assert( w >= 0 && w < G.V());
        vector<int> vec;
        path( w , vec );
        for (int i = 0; i < vec.size(); ++i)
        {
            cout << vec[i];
            if(i == vec.size() - 1)
                cout << "->" << w << endl;
            else
                cout << "->";
        }
    }
    // 查看从v点到w点的最短路径长度
    int length(int w)
    {
        assert( w >= 0 && w < G.V());
        return ord[w];
    }
};
#endif //GRAPH_SHORTPATH_H
