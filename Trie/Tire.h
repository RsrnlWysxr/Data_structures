//
// Created by Administrator on 2018/8/10/010.
//

#ifndef TIRE_TIRE_H
#define TIRE_TIRE_H
#include <iostream>
#include <map>
#include <string>
using namespace std;
class Trie
{
private:
    class Node
    {
    public:
        bool isWord;        // 判断当前节点是否为单词的结束
        map<char,Node*> next;   // 由字母找到下一Node
        Node():isWord(false){}
    };
    Node* root;
    int size;

    // 向以node为根的trie中插入单词str[index...end]
    void add(Node* node, string& str , int index)
    {
        if(index == str.length())
        {
            if(!node->isWord)
            {
                node->isWord = true;
                size++;
            }
            return;
        }
        char c = str[index];
        if( node->next.find(c) == node->next.end() )
            node->next.insert(pair<char,Node*>(c,new Node()));
        add(node->next.find(c)->second,str,index + 1);
    }
    // 向以node为根的trie中查询单词str[index...end]是否存在
    bool contains(Node* node , string& str , int index)
    {
        if(index == str.length())
            return node->isWord;
        char c = str[index];
        if( node->next.find(c) == node->next.end() )
            return false;
        return contains(node->next.find(c)->second,str,index + 1);
    }
    // 向以node为根的trie中查询单词prefix[index...end]是否存在
    bool isPrefix(Node* node , string& prefix , int index)
    {
        if(index == prefix.length())
            return true;
        char c = prefix[index];
        if( node->next.find(c) == node->next.end() )
            return false;
        return isPrefix(node->next.find(c)->second,prefix,index + 1);
    }
    // 支持.的通配符查找
    // 向以node为根的tire中查询单词str[index...end]是否存在
    bool match(Node* node , string& str , int index)
    {
        if(index == str.length())
            return node->isWord;
        char c = str[index];
        if( c != '.')
        {
            if( node->next.find(c) == node->next.end() )
                return false;
            return match(node->next.find(c)->second , str , index + 1);
        }
        else // c == '.'
        {
            // 遍历整个map，即默认.匹配到所有字母
            for(auto it = node->next.begin() ; it != node->next.end() ; it++)
                if(match( it->second , str , index + 1 ))
                    return true;
            return false;
        }
    }

public:
    Trie()
    {
        root = new Node();
        size = 0;
    }
    ~Trie()
    {
        delete root;
    }
    // 获得Trie中存储的单词数量
    int getSize()
    {
        return size;
    }
    // 向Trie中添加一个新的单词word
    // 非递归实现
    void addNR(string str)
    {
        Node* cur = root;
        for(char c:str)
        {
            if( cur->next.find(c) == cur->next.end() )
                cur->next.insert(pair<char,Node*>(c,new Node()));
            cur = cur->next.find(c)->second;
        }
        if(!cur->isWord)
        {
            cur->isWord = true;
            size++;
        }
    }
    // 向Trie中添加一个新的单词word
    // 递归实现
    void add(string str)
    {
        add(root,str,0);
    }
    // 查询单词word是否在Trie中
    // 非递归实现
    bool containsNR(string str)
    {
        Node* cur = root;
        for(char c:str)
        {
            if( cur->next.find(c) == cur->next.end() )
                return false;
            cur = cur->next.find(c)->second;
        }
        return cur->isWord;
    }
    // 查询单词word是否在Trie中
    // 递归实现
    bool contains(string str)
    {
        contains(root,str,0);
    }
    // 查询是否在Trie中有单词以prefix为前缀
    // 非递归算法
    bool isPrefixNR(string prefix)
    {
        Node* cur = root;
        for(char c: prefix)
        {
            if(cur->next.find(c) == cur->next.end())
                return false;
            cur = cur->next.find(c)->second;
        }
        return true;
    }
    // 查询是否在Trie中有单词以prefix为前缀
    // 递归算法
    bool isPrefix(string prefix)
    {
        isPrefix(root,prefix,0);
    }
    // 支持.的通配符查找
    // 递归算法
    bool match(string str)
    {
        match(root,str,0);
    }
};
#endif //TIRE_TIRE_H
