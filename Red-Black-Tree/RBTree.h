//
// Created by Administrator on 2018/8/11/011.
//

#ifndef RBTREE_TBTREE_H
#define RBTREE_TBTREE_H
#include <iostream>
#include <stack>
#include <queue>

template <typename T,typename V>
class RBTree
{
public:
    class Node
    {
    public:
        T e;
        V v;
        Node* left;
        Node* right;
        bool color;
        Node(T e,V v):e(e),v(v),left(nullptr),right(nullptr),color(RED){}                   // 默认新添加的节点为红色
        explicit Node(Node* node):e(node->e),v(node->v),left(node->left),right(node->right),color(node->color){}       // explicit 避免隐式转换
    };

private:
    Node* root;
    int size;
    static const bool RED = true;         // 默认RED为真
    static const bool BLACK =  false;

public:
    RBTree():root(nullptr),size(0){}
    ~RBTree()
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
    // 获取节点颜色，NULL节点根据红黑树性质，为黑色
    bool isRed(Node* node)
    {
        if(node == nullptr)
            return BLACK;
        return node->color;
    }

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
    // 向二分搜索树中添加新的元素e
    void add(T e,V v)
    {
        root = add(root,e,v);
        root->color = BLACK;    // 维护红黑树性质2 - 根节点为黑色
    }
private:
    // 辅助函数

    //   node                     x
    //  /   \     左旋转         /  \
    // T1   x   --------->   node   T3
    //     / \              /   \
    //    T2 T3            T1   T2
    // 左旋转 -- 向2节点插入一个大的元素后进行的操作
    Node* leftRotate(Node* node)
    {
        // 声明
        Node* x = node->right;
        // 左旋转
        node->right = x->left;
        x->left = node;
        // 维护color的语意
        x->color = node->color;
        node->color = RED;      // 相当于插入的是node(原先的根节点)
        return x;
    }

    //     node                   x
    //    /   \     右旋转       /  \
    //   x    T2   ------->   y   node
    //  / \                       /  \
    // y  T1                     T1  T2
    // 右旋转 -- 向3节点插入一个最小的元素后进行的操作
    Node* rightRotate(Node* node)
    {
        // 声明
        Node* x = node->left;
        // 右旋转
        node->left = x->right;
        x->right = node;
        // 维护color的语意
        x->color = node->color;
        node->color = RED;
        return x;
    }
    // 颜色反转
    // 维护红黑树性质4 -- 红节点的子树为黑节点
    void flipColor(Node* node)
    {
        node->color = RED;
        node->left->color = BLACK;
        node->right->color = BLACK;
    }
    // 向以node为根的二分搜索树中插入元素e，递归算法
    // 返回插入新节点后二分搜索树的根
    Node* add(Node* node,T e,V v)
    {
        if(node == nullptr)
        {
            ++size;
            Node* ret = new Node(e,v);  // 默认插入红色节点
            return ret;
        }
        if(e == node->e)        //更新
        {
            node->v = v;
            return node;
        }
        else if(e < node->e)
        {
            node->left = add(node->left,e,v);
        }
        else // e > node->e
        {
            node->right = add(node->right,e,v);
        }

        // 添加完后维护相关性质

        //    x （黑）
        //   /
        //  y （红）
        //   \
        //     z （红）
        // 以上模式 - 添加的z - 在原先3节点中间 - 进行左旋转操作
        if(isRed(node->right) && !isRed(node->left))
            node = leftRotate(node);

        //        x (黑)
        //      /
        //     y (红)
        //    /
        //   z （红）
        // 以上模式 - 添加的z - 在原先3节点最左 - 进行右旋转操作
        if(isRed(node->left) && isRed(node->left->left))
            node = rightRotate(node);

        //         x (黑)
        //       /   \
        //     y (红)  z（红）
        // 以上模式 - 添加的z - 在原先3节点最右 - 进行颜色反转
        if(isRed(node->left) && isRed(node->right))
            flipColor(node);
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
    V removeMax()
    {
        V ret = maximum();
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
                delete node;
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


#endif //RBTREE_TBTREE_H
