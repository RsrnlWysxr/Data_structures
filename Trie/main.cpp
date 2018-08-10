#include <iostream>
#include "Tire.h"

using namespace std;

int main() {
    Trie* trie = new Trie();
    trie->add("cool");
//    cout << trie->getSize() << endl;
//    cout << trie->contains("cool") << endl;
//    trie->add("panda");
//    cout << trie->isPrefix("co") << endl;
    cout << trie->match("c.l") << endl;
    return 0;
}