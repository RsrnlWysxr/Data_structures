//
// Created by Administrator on 2018/8/10/010.
//

#ifndef UNIONFIND_UNIONFIND_H
#define UNIONFIND_UNIONFIND_H
#include <iostream>
#include <cassert>

class UnionFind
{
private:
    int* parent;    // 父节点数组
    // 在后续的代码中, 不维护rank的语意, rank的值在路径压缩的过程中, 有可能不在是树的层数值
    // 只是作为比较的一个标准
    int* rank;
    int size;       // 元素个数

public:
    UnionFind(int size):size(size)
    {
        parent = new int[size];
        rank = new int[size];
        for(int i = 0 ; i < size ; i ++)
        {
            parent[i] = i;  // 每个元素的父节点是自身
            rank[i] = 1;   // 默认高度为1
        }
    }
    ~UnionFind()
    {
        delete[] parent;
        delete[] rank;
    }
    int getSize()
    {
        return size;
    }
    // 查找过程, 查找元素p所对应的集合编号
    int find(int p)
    {
        // 路径压缩
        while (p != parent[p])
        {
            parent[p] = parent[parent[p]];
            p = parent[p];
        }
        return p;

        // 递归的路径压缩（更彻底,但性能并不最优）
//        if( p != parent[p])
//            parent[p] = find(parent[p]);
//        return parent[p];
    }
    // 查看元素p和元素q是否所属一个集合
    bool isConnected(int p , int q)
    {
        return find(p) == find(q);
    }
    // 合并元素p和元素q所属的集合
    void unionElements( int p , int q)
    {
        int pRoot = find(p);
        int qRoot = find(q);
        if(qRoot == pRoot)
            return;
        // 将rank低的集合合并到rank高的集合上
        if( rank[pRoot] > rank[qRoot] )
            parent[qRoot] = pRoot;
        else if( rank[pRoot] < rank[qRoot] )
            parent[pRoot] = qRoot;
        else // rank[p] == rank[q]
        {
            parent[pRoot] = qRoot;
            rank[qRoot] += 1;
        }
    }

};
#endif //UNIONFIND_UNIONFIND_H
