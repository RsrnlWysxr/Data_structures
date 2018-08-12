//
// Created by Administrator on 2018/8/12/012.
//

#ifndef HASHTABLE_HASHTABLE_H
#define HASHTABLE_HASHTABLE_H

#include <iostream>
#include <map>
using namespace std;
template <typename K,typename V>
class HashTable
{
private:
    int M;      // 空间大小，也是模的数
    int size;
    map<K,V>* *hashTable;
    static const int upperTol = 10;     // 最高忍耐每个地址10次冲突
    static const int lowerTol = 7;      // 最少每个地址7次冲突
    static const int initCapacity = 9;  // 初始容量为9
    int hash(K key)     // 哈希函数
    {
        return(hashCode(key) & 0x7fffffff) % M;   // &取消负数
    }
    int hashCode(K key)
    {
        std::hash<K> key_hash;      // 声明
        return key_hash(key);
    }
    // 动态扩缩容
    void resize(int newM)
    {
        int oldM = M;
        M = newM;
        map<K,V>* *newHashTable;
        newHashTable = new map<K, V>*[M];
        for (int i = 0; i < M; i++)
            newHashTable[i] = new map<K, V>();
        for(int i = 0; i < oldM; i++)
        {
            auto m = hashTable[i];
            for(auto it = m->begin() ; it != m->end() ; it++)
            {
//                newHashTable[hash(it->first)]->insert(pair<K,V>(it->first,it->second));
                (*newHashTable[hash(it->first)])[(it->first)] = it->second;
            }
        }
        for(int i = 0 ; i < oldM ; i++)
        {
            delete hashTable[i];
        }
        delete[] hashTable;
        hashTable = newHashTable;
    }
public:
    explicit HashTable(int M):M(M),size(0)
    {
        hashTable = new map<K,V>*[M];       // 开M个map指针的空间
        for(int i = 0 ; i < M ; i++)
            hashTable[i] = new map<K,V>();  // 每个指针指向的map开空间
    }
    HashTable():M(initCapacity),size(0)
    {
        hashTable = new map<K,V>*[M];
        for(int i = 0 ; i < M ; i++)
            hashTable[i] = new map<K,V>();
    }
    ~HashTable()
    {

        for(int i = 0 ; i < M ; i++)
        {
            delete hashTable[i];
        }
        delete[] hashTable;
    }
    int getSize()
    {
        return size;
    }
    void add(K key,V value)
    {
        map<K,V>* map = hashTable[hash(key)];   // 为避免多次计算hash，将当前key值所对应的map浅拷贝，用于后面的调用
        if(map->find(key) != map->end())
        {
//            auto it =map->find(key);
//            it->second = value;
            (*map)[key] = value;
        }
        else
        {
//            map->insert(pair<K,V>(key,value));
            (*map)[key] = value;
            size ++;
        }
        if(size >= upperTol * M)
            resize(2 * M);
    }
    void remove(K key)
    {
        map<K,V>* map = hashTable[hash(key)];
        if(map->find(key) != map->end())
        {
            map->erase(key);
            size -- ;
        }
        if(size < lowerTol * M && M / 2 >= initCapacity)
            resize( M / 2);
    }
    bool isContains(K key)
    {
        return hashTable[hash(key)]->find(key) != hashTable[hash(key)]->end();
    }
    V getValue(K key)
    {
        return (*hashTable[hash(key)])[key];
    }
    void set(K key,V value)
    {
        map<K,V>* map = hashTable[hash(key)];
        if(map->find(key) != map->end())
        {
            (*map)[key] = value;
        }
        else throw "no key";
    }
};
#endif //HASHTABLE_HASHTABLE_H
