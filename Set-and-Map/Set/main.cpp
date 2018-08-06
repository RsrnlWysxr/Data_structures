#include <iostream>
#include <algorithm>
#include "BSTSet-and-LinkedSet.h"
#include "BST.h"
#include "FileOperation.h"

template <typename T>
double testSet(T* set ,string filename)
{
    clock_t time1 = clock();
    vector<string> words;
    if(FileOps::readFile(filename,words))
    {
        std::cout << "There are totally:" << words.size() << " words in " << filename;
        std::cout << std::endl;
//        sort(words.begin(),words.end());      //顺序情况下，BSTSet慢，因为左孩子消耗了性能
        for(string x:words)
        {
            set->add(x);
        }
        std::cout << "Totally different: " << set->getSize() << " words in " << filename << std::endl;
    }
    clock_t time2 = clock();
    return (double)(time2 - time1) / CLOCKS_PER_SEC;
}

int main() {
    string filename = "pride-and-prejudice.txt";
    BSTSet<string>* bst = new BSTSet<string>();
    double time1 = testSet(bst,filename);
    std::cout << "BSTSet time :" << time1 << " s" << std::endl;
    LinkedSet<string>* list = new LinkedSet<string>();
    double time2 = testSet(list,filename);
    std::cout << "BSTSet time :" << time2 << " s" << std::endl;
    delete bst;
    delete list;
}
