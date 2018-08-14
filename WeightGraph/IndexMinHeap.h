//
// Created by Administrator on 2018/8/13/013.
//

#ifndef INDEXMAXHEAP_INDEXMAXHEAP_H
#define INDEXMAXHEAP_INDEXMAXHEAP_H

#include <iostream>
#include <cassert>
#include <algorithm>
using namespace std;

// 最大索引堆
template <typename T>
class IndexMinHeap
{
private:            // 默认i为真实数组的索引，j为index的索引，即j为真实顺序
    T* data;        // 最小索引堆中的数据    根据i访问具体数据
    int* index;     // 最小索引堆中的索引    index[j] = i        // 也是真正的堆
    int* reverse;   // 最小索引堆中的反向索引  reverse[i] = j
    int size;       // 数据数量
    int capacity;   // 数组空间

    // 根据语意，始终保持如下
    // index[reverse[i]] = i;
    // reverse[index[j]] = j;

    // 计算j的父亲位置索引
    int parent(int j)
    {
        return (j - 1) / 2;
    }
    // 计算j的左孩子位置索引
    int leftChild(int j)
    {
        return j * 2 + 1;
    }
    // 计算j的右孩子位置索引
    int rightChild(int j )
    {
        return j * 2 + 2;
    }
    // 上浮
    void shiftUp(int j)
    {
        int jp = parent(j);     // 此位置的父亲位置索引
        int i = index[j];       // 由index语意，得此位置的数据索引
        int ip = index[jp];     // 此位置的父亲位置对应的数据索引
        while( j > 0 && data[i] < data[ip])  // 比较数据，交换的是位置对应的数据索引
        {
            // 交换操作
            index[j] = ip;
            index[jp] = i;
            // 维护reverse语意
            reverse[i] = jp;
            reverse[ip] = j;
            // 更新循环变量
            j = jp;         // 观察的位置换到已经交换的父亲位置索引
            jp = parent(j);
            i = index[j];
            ip = index[jp];
        }
    }
    // 下沉
    void shiftDown(int j)
    {
        int jk = compare(j);    // jk为要交换的位置索引
        while( jk )
        {
            int i = index[j];   // 待下沉位置对应的数据索引
            int ik = index[jk]; // 待交换位置对应的数据索引
            if( data[i] <= data[ik] )
                break;
            // 交换操作
            index[jk] = i;
            index[j] = ik;
            // 维护reverse语意
            reverse[i] = jk;
            reverse[ik] = j;
            // 更新循环变量
            j = jk;
            jk = compare(j);
        }
    }
    // 返回目前左右孩子中数据较小的位置索引，保证索引有效不越界
    int compare( int j )
    {
        int jl = leftChild(j);
        int jr = rightChild(j);
        if( jr < size) // 左右位置索引都有在界内
        {
            if( data[jl] <= data[jr])
                return jl;
            else
                return jr;
        }
        else if ( jl < size && jr >= size ) // 左孩子位置索引有效
            return jl;
        else    // 左右都越界
            return 0;
    }

public:
    // 构造函数, 构造一个空的索引堆, 可容纳capacity个元素
    explicit IndexMinHeap(int capacity):capacity(capacity)
    {
        size = 0;
        data = new T[capacity];
        index = new int[capacity];
        reverse = new int[capacity];
        for(int i = 0 ; i <= capacity ; i++)
        {
            reverse[i] = -1;    // 最初任何索引都无效
        }
    }
    ~IndexMinHeap()
    {
        delete[] data;
        delete[] index;
        delete[] reverse;
    }
    // 返回索引堆中的元素个数
    int getSize()
    {
        return size;
    }
    // 返回一个布尔值, 表示索引堆中是否为空
    bool isEmpty()
    {
        return size == 0;
    }
    // 看索引i所在的位置是否存在元素
    bool contain( int i )
    {
        assert( i <= capacity && i >= 0);   // 保证i的合法
        return reverse[i] != -1;
    }
    // 向最小索引堆中插入一个新的元素, 新元素的索引为i, 数据为e
    void add(int i , T e)
    {
        assert( !contain(i) );              // 确保i的位置是没有数据的
        assert( size <= capacity );     // 确保添加后不超出空间

        data[i] = e;
        int j = size;       // 新添加的元素在索引堆最后的位置
        index[j] = i;       // 创建index对应语意 -> 根据位置索引j 得 数据索引i
        reverse[i] = j;     // 创建reverse对应语意 -> 根据数据索引i 得 位置索引j

        shiftUp(size);      // 新添加的位置进行上浮
        size++;
    }
    // 从最小索引堆中取出堆顶元素的索引
    int extractMaxIndex()
    {
        assert( size > 0 );
        int ret = index[0];
        swap<T>( index[0] , index[size - 1] );
        reverse[index[size - 1]] = -1;
        size --;
        if( size )
        {
            reverse[index[0]] = 0;
            shiftDown(0);
        }
        return ret;
    }
    // 从最小索引堆中取出堆顶元素, 即索引堆中所存储的最小数据
    T extractMax()
    {
        assert( size > 0 );
        T ret = data[index[0]];
        swap<T>( index[0] , index[size - 1] );
        reverse[index[size - 1]] = -1;
        size --;
        if( size )
        {
            reverse[index[0]] = 0;
            shiftDown(0);
        }
        return ret;
    }
    // 获取最小索引堆中的堆顶元素
    T getMax()
    {
        assert(size > 0);
        return data[index[0]];
    }
    // 获取最小索引堆中的堆顶元素的索引
    int getIndex()
    {
        assert(size > 0);
        return index[0];
    }
    // 获取最小索引堆中索引为i的元素
    T getData(int i)
    {
        assert( contain(i) );
        return data[i];
    }
    // 将最小索引堆中索引为i的元素修改为e
    void change(int i , T e)
    {
        assert( contain(i) );
        data[i] = e;
        // 维护堆
        int j = reverse[i];     // 找到该数据索引在堆中的位置索引
        shiftUp(j);
        shiftDown(j);
    }
    void toSting()
    {
        cout << "index:";
        for(int i = 0 ; i < size ; i ++)
        {
            cout << index[i] << " ";
        }
        cout << endl;
        cout << "data:";
        for(int i = 0 ; i < size ; i ++)
        {
            cout << data[i] << " ";
        }
        cout << endl;
        cout << "reverse:";
        for(int i = 0 ; i < size ; i ++)
        {
            cout << reverse[i] << " ";
        }
    }
};
#endif //INDEXMAXHEAP_INDEXMAXHEAP_H
