#include <iostream>
#include "FileOperation.h"
#include "AVLTree.h"
#include <string>
#include <algorithm>

double testSet(AVLTree<std::string,int>* map ,string filename)
{
    clock_t time1 = clock();
    vector<string> words;
    if(FileOps::readFile(filename,words))
    {
        std::cout << "There are totally:" << words.size() << " words in " << filename;
        std::cout << std::endl;
//        sort(words.begin(),words.end());      //顺序情况下，BSTMap慢，因为左孩子消耗了性能
        for(string x:words)
        {
            if(map->contains(x))
                map->set(x,map->getValue(x)+1);
            else map->add(x,1);
        }
        std::cout << "Totally different: " << map->getSize() << " words in " << filename << std::endl;
        std::cout << "Frequency of PRIDE: " << map->getValue("pride") << std::endl;
        std::cout << "Frequency of PREJUDICE: " << map->getValue("prejudice") << std::endl;
    }
    clock_t time2 = clock();
    return (double)(time2 - time1) / CLOCKS_PER_SEC;
}

int main()
{
    AVLTree<std::string,int>* bst = new AVLTree<std::string,int>();
    std::string filename = "pride-and-prejudice.txt";
    double time1 = testSet(bst,filename);
    std::cout << "AVLTree time: " << time1 << " s" <<std::endl;
    std::cout << "isBST:" << bst->isBST() << std::endl;
    std::cout << "isBalanced:" << bst->isBalanced() << std::endl;
    std::cout << "/////////////////////////////////////////////////////////" << std::endl;
    bst->remove("pride");
    bst->remove("prejudice");
    std::cout << "isBST:" << bst->isBST() << std::endl;
    std::cout << "isBalanced:" << bst->isBalanced() << std::endl;
    delete bst;
}