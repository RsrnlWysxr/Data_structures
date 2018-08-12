#include <iostream>
#include <string>
#include "HashTable.h"
using namespace std;

int main()
{
    auto hashTable = new  HashTable<string,int>(1);
    hashTable->add("my",0);
    hashTable->add("name",1);
    hashTable->add("is",2);
    hashTable->add("lyh",3);
    std::cout << hashTable->isContains("lyh") << std::endl;
    std::cout << hashTable->getSize() << std::endl;
    std::cout << hashTable->getValue("is") << std::endl;
    hashTable->set("is",4);
    std::cout << hashTable->getValue("is") << std::endl;
    return 0;
}