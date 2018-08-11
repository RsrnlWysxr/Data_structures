//
// Created by Administrator on 2018/8/11/011.
//

#ifndef AVLTREE_AVLTREE_H
#define AVLTREE_AVLTREE_H

#include <iostream>
#include <stack>
#include <queue>
#include <vector>
#include <cmath>

template <typename T,typename V>
class AVLTree
{
public:
    class Node
    {
    public:
        T e;
        V v;
        int height;
        Node* left;
        Node* right;
        Node(T e,V v):e(e),v(v),height(1),left(nullptr),right(nullptr){}
        Node(Node* node):e(node->e),v(node->v),left(node->left),right(node->right),height(node->height){}
    };

private:
    Node* root;
    int size;
public:
    AVLTree():root(nullptr),size(0){}
    ~AVLTree()
    {
        destroy(root);
    }

private:
    void destroy(Node* node)
    {
        if(node)
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
    // 获取当前节点高度
    int getHeight(Node* node)
    {
        if(node == nullptr)
            return 0;
        return node->height;
    }
    // 计算当前节点平衡因子（左 - 右）
    int getBalanceFactor(Node* node)
    {
        if(node == nullptr)
            return 0;
        return getHeight(node->left) - getHeight(node->right);
    }
    // 判断是否为BST
    bool isBST()
    {
        std::vector<T> arr;
        inOrder(root,arr);
        for(int i = 1 ; i < arr.size() ; i ++)
        {
            if( arr[i - 1] > arr[i])
                return false;
        }
        return true;
    }
    // 判断是否为平衡树
    bool isBalanced()
    {
        return isBalanced(root);
    }

private:
    // 对以node为根的BST中序遍历，将遍历结果放入数组arr中
    void inOrder(Node* node,std::vector<T>& arr)
    {
        if(node == nullptr)
            return;
        inOrder(node->left,arr);
        arr.push_back(node->e);
        inOrder(node->right,arr);
    }
    // 判断以node为根的BST是否平衡
    bool isBalanced(Node* node)
    {
        if(node == nullptr)
            return true;

        int balanceFactor = abs(getBalanceFactor(node));
        if( balanceFactor > 1)
            return false;
        return isBalanced(node->left) && isBalanced(node->right);
    }

public:
    // 获取元素e的值value
    V getValue(T e)
    {
        Node* node = getValue(root,e);
        if(node)
            return node->v;
        return -1;
    }

private:
    // 返回以node为根节点的二分搜索树中，e所在的节点
    Node* getValue(Node* node,T e)
    {
        if(node == nullptr )
            return node;
        if(e == node->e)
            return node;
        if(e < node->e)
            return getValue(node->left,e);
        if(e > node->e)
            return getValue(node->right,e);
    }

public:
    //设置节点的value
    void set(T e,V v)
    {
        Node* node = getValue(root,e);
        if(node)
            node->v = v;
    }

public:
    // 向二分搜索树中添加新的元素e
    void add(T e,V v)
    {
        root = add(root,e,v);
    }
private:
    // 对节点y进行向右旋转操作，返回旋转后新的根节点x
    //        y                              x
    //       / \                           /   \
    //      x   T4     向右旋转 (y)        z     y
    //     / \       - - - - - - - ->    / \   / \
    //    z   T3                       T1  T2 T3 T4
    //   / \
    // T1   T2
    Node* rightRotate(Node* y)
    {
        // 声明
        Node* x = y->left;
        Node* T3 = x->right;
        // 旋转
        x->right = y;
        y->left = T3;
        // 维护height语意
        y->height = max( getHeight(y->right) , getHeight(y->left) ) + 1;
        x->height = max( getHeight(x->right) , getHeight(x->left) ) + 1;
        return x;
    }
    // 对节点y进行向左旋转操作，返回旋转后新的根节点x
    //    y                             x
    //  /  \                          /   \
    // T1   x      向左旋转 (y)       y     z
    //     / \   - - - - - - - ->   / \   / \
    //   T2  z                     T1 T2 T3 T4
    //      / \
    //     T3 T4
    Node* leftRotate(Node* y)
    {
        // 声明
        Node* x = y->right;
        Node* T2 = x->left;
        // 旋转
        x->left = y;
        y->right = T2;
        //维护height
        y->height = max( getHeight(y->right) , getHeight(y->left) ) + 1;
        x->height = max( getHeight(x->right) , getHeight(x->left) ) + 1;
        return x;
    }
    // 向以node为根的二分搜索树中插入元素e，递归算法
    // 返回插入新节点后二分搜索树的根
    Node* add(Node* node,T e,V v)
    {
        if(node == nullptr)
        {
            ++size;
            Node* ret = new Node(e,v);
            return ret;
        }
        if(e == node->e)        //更新
        {
            node->v = v;
            return node;
        }
        if(e < node->e)
        {
            node->left = add(node->left,e,v);
        }
        if(e > node->e)
        {
            node->right = add(node->right,e,v);
        }
        // 维护height语意
        node->height = max(getHeight(node->right),getHeight(node->left)) + 1;

        // 维护平衡
        int balanceFactor = getBalanceFactor(node);

        // LL -> 右旋转
        if(balanceFactor > 1 && getBalanceFactor(node->left) >= 0)
            return rightRotate(node);

        // RR -> 左旋转
        if(balanceFactor < -1 && getBalanceFactor(node->right) <= 0)
            return leftRotate(node);

        // LR -> 左旋转-右旋转
        if(balanceFactor > 1 && getBalanceFactor(node->left) < 0)
        {
            node->left = leftRotate(node->left);
            return rightRotate(node);
        }

        // RL -> 右旋转-左旋转
        if(balanceFactor < -1 && getBalanceFactor(node->right) > 0)
        {
            node->right = rightRotate(node->right);
            return leftRotate(node);
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
    V minimum()
    {
        if(size == 0)
            throw "This BST is null";
        return minimum(root)->v;
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
    V maximum()
    {
        if(size == 0)
            throw "This BST is null";
        return maximum(root)->v;
    }

private:
    // 返回以node为根的二分搜索树的最大值所在的节点
    Node* maximum(Node* node)
    {
        if (node->right == nullptr)
            return node;
        return maximum(node->right);
    }

public:
    // 从二分搜索树中删除最小值所在节点, 返回最小值
    V removeMin()
    {
        V ret = minimum();
        root = remove(root,minimum());
        return ret;
    }
    // 从二分搜索树中删除最大值所在节点, 返回最大值
    V removeMax()
    {
        V ret = maximum();
        root = remove(root,maximum());
        return ret;
    }
public:
    // 从二分搜索树中删除元素为e的节点
    V remove(T e)
    {
        V ret = getValue(e);
        root = remove(root,e);
        return ret;
    }

private:
    // 删除掉以node为根的二分搜索树中值为e的节点, 递归算法
    // 返回删除节点后新的二分搜索树的根
    Node* remove(Node* node,T e)
    {
        if(node == nullptr)
            return nullptr;
        Node* ret = nullptr;
        if(node->e == e)
        {
            // 待删除节点左子树为空的情况
            if(node->left == nullptr)
            {
                ret = node->right;
                delete node;
                --size;
            }
            // 待删除节点右子树为空的情况
            else if(node->right == nullptr)
            {
                ret = node->left;
                delete node;
                size --;
            }
            // 待删除节点左右子树均不为空的情况
            // 找到比待删除节点大的最小节点, 即待删除节点右子树的最小节点
            // 用这个节点顶替待删除节点的位置
            else
            {
                Node *successor = new Node(minimum(node->right));   // 节点拷贝
                ++size;
                // 此处更改为使用递归remove删除最小元素
                successor->right = remove(node->right,successor->e);
                successor->left = node->left;
                delete node;
                size--;
                ret = successor;
            }
        }
        else if(e < node->e)
        {
            node->left = remove(node->left,e);
            ret = node;
        }
        else // e > node->e
        {
            node->right = remove(node->right,e);
            ret = node;
        }

        if(ret == nullptr)
            return ret;

        // 维护height语意
        ret->height = max(getHeight(ret->left) , getHeight(ret->right)) + 1;

        // 维护平衡
        int balanceFactor = getBalanceFactor(ret);

        // LL
        if(balanceFactor > 1 && getBalanceFactor(ret->left) >= 0)
            return rightRotate(ret);
        // RR
        if(balanceFactor < -1 && getBalanceFactor(ret->right) <= 0)
            return leftRotate(ret);
        // LR
        if(balanceFactor > 1 && getBalanceFactor(ret->left) < 0)
        {
            ret->left = leftRotate(ret->left);
            return rightRotate(ret);
        }
        // RL
        if(balanceFactor < -1 && getBalanceFactor(ret->right) > 0)
        {
            ret->right = rightRotate(ret->right);
            return leftRotate(ret);
        }
        return ret;
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
        std::cout << node->e << ",v:" << node->v;
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
#endif //AVLTREE_AVLTREE_H
