//
// Created by Administrator on 2018/8/10/010.
//

#ifndef SEGMENT_TREE_SEGMENT_TREE_H
#define SEGMENT_TREE_SEGMENT_TREE_H

#include <iostream>
#include <functional>
#include <cassert>


// 底层使用静态数组实现
using namespace std;

template <typename T>
class SegmentTree
{
private:
    T* data;    // 接收外部传入数组，辅助构建线段树
    T* tree;
    int size;
    function<T(T,T)> fun;

    // 递归创建线段树
    // 在treeIndex的位置创建表示区间[l...r]的线段树
    void buildSegmentTree(int treeIndex , int l , int r )
    {
        if( l == r )
        {
            tree[treeIndex] = data[l];
            return;
        }
        int leftTreeIndex = leftChild(treeIndex);
        int rightTreeIndex = rightChild(treeIndex);
        int mid = l + ( r - l ) / 2;
        buildSegmentTree( leftTreeIndex , l , mid);
        buildSegmentTree( rightTreeIndex, mid +  1, r);
        tree[treeIndex] = fun(tree[rightTreeIndex],tree[leftTreeIndex]);
    }

    // 返回完全二叉树的数组表示中，一个索引所表示的元素的左孩子节点的索引
    int leftChild(int index)
    {
        return index * 2 + 1;
    }
    // 返回完全二叉树的数组表示中，一个索引所表示的元素的右孩子节点的索引
    int rightChild(int index)
    {
        return index * 2 + 2;
    }
    // 在以treeIndex为根的线段树中[l...r]的范围里，搜索区间[queryL...queryR]的值
    T query(int treeIndex , int l ,int r , int queryL , int queryR)
    {
        if( l == queryL && r == queryR)
            return tree[treeIndex];
        int mid = l + ( r - l ) / 2;
        if( queryR <= mid)
            return query(leftChild(treeIndex),l,mid,queryL,queryR);
        if( queryL >= mid + 1)
            return query(rightChild(treeIndex),mid + 1,r,queryL,queryR);
        // 不在单个区间，需要操作两个区间
        T retLeft =  query(leftChild(treeIndex),l, mid,queryL,mid);
        T retRight = query(rightChild(treeIndex),mid + 1,r,mid + 1,queryR);
        return fun(retLeft,retRight);
    }
    // 在以treeIndex为根线段树中，修改Index的值为e
    void set(int treeIndex , int l , int r ,int index , T e)
    {
        if( l == r )
        {
            tree[treeIndex] = e;
            return;
        }
        int mid = l + ( r - l ) / 2;
        if( index <= mid)
            set(leftChild(treeIndex),l,mid,index,e);
        else // index >= mid + 1
            set(rightChild(treeIndex),mid + 1, r,index,e);
        tree[treeIndex] = fun(tree[leftChild(treeIndex)],tree[rightChild(treeIndex)]);
    }
public:
    // 构造函数
    // 传入数组，数组长度，以及操作函数
    SegmentTree( T* arr,int size,function<T(T,T)> fun )
    {
        this->size = size;
        this->fun = fun;
        data = new T[size]();      // 加() --> 调用内置类型的默认构造函数
        for(int i = 0 ; i < size; i ++)
        {
            data[i] = arr[i];
        }
        this->tree = new T[4 * size];  // 加() --> 调用内置类型的默认构造函数
        // 创建线段树
        buildSegmentTree(0 , 0 , size - 1);
    }
    // 析构函数
    ~SegmentTree()
    {
        delete[] data;
        delete[] tree;
    }
    // 获取线段树元素数
    int getSize()
    {
        return  size;
    }
    // 获取底层数组元素
    int getData(int index)
    {
        assert(index >= 0 && index < size);
        return data[index];
    }
    // 查找指定区间的值
    T query(int queryL , int queryR)
    {
        assert(queryL >= 0 && queryR < size && queryL <= queryR);
        return query(0,0,size - 1,queryL,queryR);
    }
    // 更新元素
    void set(int index , T e)
    {
        assert( index >= 0 && index < size);
        data[index] = e;
        set(0,0,size - 1,index,e);
    }
    // 打印线段树
    void toString()
    {
        cout << "[";
        for(int i = 0 ; i < size * 4 ; i ++)
        {
            if ( i != size * 4 - 1)
                cout << tree[i] << ",";
            else cout << tree[i] << ']' << endl;
        }
    }
};



#endif //SEGMENT_TREE_SEGMENT_TREE_H
