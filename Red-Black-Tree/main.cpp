#include <iostream>
#include "FileOperation.h"
#include <string>
#include <algorithm>
#include "RBTree.h"

double testSet(RBTree<std::string,int>* map ,string filename)
{
    clock_t time1 = clock();
    vector<string> words;
    if(FileOps::readFile(filename,words))
    {
        std::cout << "There are totally:" << words.size() << " words in " << filename;
        std::cout << std::endl;
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
    RBTree<std::string,int>* bst = new RBTree<std::string,int>();
    std::string filename = "pride-and-prejudice.txt";
    double time1 = testSet(bst,filename);
    std::cout << "RBTree time: " << time1 << " s" <<std::endl;
    delete bst;
}