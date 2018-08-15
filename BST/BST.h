//
// Created by Administrator on 2018/8/4/004.
//

#ifndef BST_BST_H
#define BST_BST_H
#include <iostream>
#include <stack>
#include <queue>

template <typename T>
class BST
{
public:
    class Node
    {
    public:
        T e;
        Node* left;
        Node* right;
        Node(T e):e(e),left(nullptr),right(nullptr){}
        Node(Node* node):e(node->e),left(node->left),right(node->right){}
    };

private:
    Node* root;
    int size;
public:
    BST():root(nullptr),size(0){}
    ~BST()
    {
        destroy(root);
    }

private:
    void destroy(Node* node)
    {
        if(!node)
        {
            destroy(node->left);
            destroy(node->right);
            delete node;
            --size;
        }
    }

public:
    int getSize()
    {
        return size;
    }
    bool isEmpty()
    {
        return (size == 0);
    }
    // 向二分搜索树中添加新的元素e
    void add(T e)
    {
        root = add(root,e);
    }
private:
    // 向以node为根的二分搜索树中插入元素e，递归算法
    // 返回插入新节点后二分搜索树的根
    Node* add(Node* node,T e)
    {
        if(node == nullptr)
        {
            ++size;
            Node* ret = new Node(e);
            return ret;
        }
        if(e < node->e)
        {
            node->left = add(node->left,e);
        }
        if(e > node->e)
        {
            node->right = add(node->right,e);
        }
        return node;
    }
public:
    // 看二分搜索树中是否包含元素e
    bool contains(T e)
    {
        return contains(root,e);
    }
private:
    // 看以node为根的二分搜索树中是否包含元素e, 递归算法
    bool contains(Node* node, T e)
    {
        if(node == nullptr)
            return false;
        if(e == node->e)
            return true;
        else if(e < node->e)
            return contains(node->left,e);
        else //e > node->e
            return contains(node->right,e);
    }
public:
    // 二分搜索树的前序遍历
    void preOrder()
    {
        preOrder(root);
    }
private:
    // 前序遍历以node为根的二分搜索树, 递归算法
    void preOrder(Node* node)
    {
        if(node == nullptr)
            return;
        std::cout << node->e;
        preOrder(node->left);
        preOrder(node->right);
    }
public:
    // 二分搜索树的非递归前序遍历
    void preOrderNR()
    {
        /*
        //使用栈的特性完成遍历
        std::stack<Node*> s;
        Node* cur = root;
        while(cur || !s.empty())
        {
            while(cur)
            {
                s.push(cur);
                std::cout << cur->e;
                cur = cur->left;
            }
            //循环结束表示，以cur为根的树，根与每个左子树的根均已被打印
            Node* top = s.top();
            s.pop();
            cur = top->right;
        }
         */
        /////////////////////////////////////////////////////////
        //使用栈完成前序遍历
        std::stack<Node*> s;
        s.push(root);
        while(!s.empty())
        {
            Node* cur = s.top();
            std::cout << cur->e;
            s.pop();
            if(cur->right)  s.push(cur->right);
            if(cur->left)   s.push(cur->left);
        }
    }
    // 二分搜索树的中序遍历
    void inOrder()
    {
        inOrder(root);
    }

private:
    // 中序遍历以node为根的二分搜索树, 递归算法
    void inOrder(Node* node)
    {
        if (node == nullptr)
            return;
        inOrder(node->left);
        std::cout << node->e;
        inOrder(node->right);
    }

public:
    // 二分搜索树的非递归中序遍历
    void inOrderNR()
    {
        //使用栈的特性完成遍历
        std::stack<Node*> s;
        Node* cur = root;
        while(cur || !s.empty())
        {
            while(cur)
            {
                s.push(cur);
                cur = cur->left;
            }
            //循环结束表示，以cur为根节点的树，根与每个左子树的根全部已经入栈,
            Node* top = s.top();    //取到最左节点
            std::cout << top->e;
            s.pop();
            cur = top->right;
        }
    }
    // 二分搜索树的后序遍历
    void postOrder()
    {
        postOrder(root);
    }

private:
    void postOrder(Node* node)
    {
        if(node == nullptr)
            return;
        postOrder(node->left);
        postOrder(node->right);
        std::cout << node->e;
    }

public:
    void postOrderNR()
    {
        /*
        //使用栈的特性完成遍历
        std::stack<Node*> s;
        Node* cur = root;
        Node* temp = nullptr;   //记录已经打印的右子树
        while(cur || !s.empty())
        {
            while(cur)
            {
                s.push(cur);
                cur = cur->left;
            }
            //循环结束表示，以cur为根节点的树，根与每个左子树的根全部已经入栈,
            Node* top = s.top();
            if(top->right == nullptr || top->right == temp)
            {
                std::cout << top->e;
                s.pop();        //打印后出栈
                temp = top;     //更新temp为已打印的过的节点
            }
            else cur = top->right;  //右子树不为空或者未被访问，更新cur，进入上述while循环，右子树为空
        }
         */
        ///////////////////////////////////////////////////////////////////////////
        //使用两个栈实现后序遍历
        std::stack<Node*> stack;
        std::stack<int> out;        //简略起见，不适用模板
        stack.push(root);
        while(!stack.empty())
        {
            Node* cur = stack.top();
            stack.pop();
            out.push(cur->e);
            if(cur->left)   stack.push(cur->left);
            if(cur->right)  stack.push(cur->right);
        }
        while (!out.empty())
        {
            std::cout << out.top();
            out.pop();
        }
    }

    // 二分搜索树的层序遍历
    void levelOrder()
    {
        std::queue<Node*> q;
        q.push(root);
        while(!q.empty())
        {
            Node* cur = q.front();
            std::cout << cur->e;
            q.pop();
            if(cur->left)   q.push(cur->left);
            if(cur->right)  q.push(cur->right);
        }
    }
    // 寻找二分搜索树的最小元素
    T minimum()
    {
        if(size == 0)
            throw "This BST is null";
        return minimum(root)->e;
    }
private:
    // 返回以node为根的二分搜索树的最小值所在的节点
    Node* minimum(Node* node)
    {
        if(node->left == nullptr)
            return node;
        return minimum(node->left);
    }

public:
    // 寻找二分搜索树的最大元素
    T maximum()
    {
        if(size == 0)
            throw "This BST is null";
        return maximum(root)->e;
    }

private:
    // 返回以node为根的二分搜索树的最大值所在的节点
    Node* maximum(Node* node)
    {
        if (node->right == nullptr)
            return node;
        return maximum(node->right);;
    }

public:
    // 从二分搜索树中删除最小值所在节点, 返回最小值
    T removeMin()
    {
        T ret = minimum();
        root = removeMin(root);
        return ret;
    }

private:
    // 删除掉以node为根的二分搜索树中的最小节点
    // 返回删除节点后新的二分搜索树的根
    Node* removeMin(Node* node)
    {
        if(node->left == nullptr)
        {
            Node* ret = node->right;
            --size;
            delete node;
            return ret;
        }
        node->left = removeMin(node->left);
        return node;
    }
public:
    // 从二分搜索树中删除最小值所在节点, 返回最小值
    T removeMax()
    {
        T ret = maximum();
        root = removeMax(root);
        return ret;
    }

private:
    Node* removeMax(Node* node)
    {
        if(node->right == nullptr)
        {
            Node* ret = node->left;
            --size;
            delete node;
            return ret;
        }
        node->right = removeMax(node->right);
        return node;
    }

public:
    // 从二分搜索树中删除元素为e的节点
    void remove(T e)
    {
        root = remove(root,e);
    }

private:
    // 删除掉以node为根的二分搜索树中值为e的节点, 递归算法
    // 返回删除节点后新的二分搜索树的根
    Node* remove(Node* node,T e)
    {
        if(node == nullptr)
            return nullptr;
        if(node->e == e)
        {
            // 待删除节点左子树为空的情况
            if(node->left == nullptr)
            {
                Node* ret = node->right;
                --size;
                delete node;
                return ret;
            }
            // 待删除节点右子树为空的情况
            if(node->right == nullptr)
            {
                Node* ret = node->left;
                size --;
                return ret;
            }
            // 待删除节点左右子树均不为空的情况
            // 找到比待删除节点大的最小节点, 即待删除节点右子树的最小节点
            // 用这个节点顶替待删除节点的位置
            Node* successor = new Node(minimum(node->right));
            ++size;
            successor->right = removeMin(node->right);
            successor->left = node->left;
            size--;
            delete node;
            return  successor;
        }
        if(e < node->e)
        {
            node->left = remove(node->left,e);
            return node;
        }
        if(e > node->e)
        {
            node->right = remove(node->right,e);
            return node;
        }
    }

public:
    void toString()
    {
        toString(root,1);
    }

private:
    void toString(Node* node,int depth)
    {
        if(node == nullptr)
        {
            helpToString(depth);
            std::cout << "NULL\n";
            return;
        }
        std::cout << node->e;
        toString(node->left,depth+1);
        toString(node->right,depth+1);
    }
    void helpToString(int depth)
    {
        for(int i = 0 ; i < depth; i++)
        {
            std::cout << " - ";
        }
    }

    };
#endif //BST_BST_H
