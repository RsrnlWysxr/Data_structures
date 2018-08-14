//
// Created by Administrator on 2018/8/13/013.
//

#ifndef WEIGTHGRAPH_EDGE_H
#define WEIGTHGRAPH_EDGE_H

#include <iostream>
#include <cassert>
#include <ostream>

using namespace std;
// 定义支持模板类的两个顶点之间的边
template <typename  Weight>
class Edge
{
private:
    int a,b;        // 两个顶点
    Weight weight;  // 边的权重

public:
    Edge(int a, int b, Weight weight):a(a),b(b),weight(weight){}
    Edge(){}
    ~Edge(){}

    int v() { return a; }
    int w() { return b; }
    Weight wt() const  { return weight; }  // 返回权值
    // 给定一个顶点，返回另一个顶点
    int other( int x )
    {
        assert( x == a || x == b);
        return x == a ? b : a;
    }
    // 输出边的信息
    friend ostream& operator<<(ostream &os, const Edge &e)
    {
        os << e.a << "-" << e.b << ":" << e.weight;
        return os;
    }
    // 边的大小比较，是对边的权值的大小比较
    bool operator<(const Edge<Weight> &e) const
    {
        return this->weight < e.wt();
    }
    bool operator<=(const Edge<Weight> &e) const
    {
        return this->weight <= e.wt();
    }
    bool operator>=(const Edge<Weight> &e) const
    {
        return this->weight >= e.wt();
    }
    bool operator>(const Edge<Weight> &e) const
    {
        return this->weight > e.wt();
    }
    bool operator==(const Edge<Weight> &e) const
    {
        return this->weight == e.wt();
    }
};

#endif //WEIGTHGRAPH_EDGE_H
