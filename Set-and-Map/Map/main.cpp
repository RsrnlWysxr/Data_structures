#include <iostream>
#include "BSTMap-and-LinkedMap.h"
#include "FileOperation.h"
#include <string>
#include <algorithm>

template <typename T>
double testSet(T* map ,string filename)
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
                map->set(x,map->get(x)+1);
            else map->add(x,1);
        }
        std::cout << "Totally different: " << map->getSize() << " words in " << filename << std::endl;
        std::cout << "Frequency of PRIDE: " << map->get("pride") << std::endl;
        std::cout << "Frequency of PREJUDICE: " << map->get("prejudice") << std::endl;
    }
    clock_t time2 = clock();
    return (double)(time2 - time1) / CLOCKS_PER_SEC;
}

int main()
{
    BSTMap<string,int>* bst = new BSTMap<string,int>();
    string filename = "pride-and-prejudice.txt";
    double time1 = testSet(bst,filename);
    std::cout << "BSTMap time: " << time1 << " s" <<std::endl;
    //////////////////////////////////////////////////////////////
    LinkedMap<string,int>* list = new LinkedMap<string,int>();
    string filename2 = "pride-and-prejudice.txt";
    double time2 = testSet(list,filename);
    std::cout << "BSTMap time: " << time2 << " s" <<std::endl;
    delete bst;
    delete list;
}