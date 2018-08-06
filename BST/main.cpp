#include <iostream>
#include "BST.h"

int main()
{
	BST<int>* bst = new BST<int>();
	int a[] = {4,2,6,1,3,5,7};
	for(int x:a)
	{
		bst->add(x);
	}
//	bst->preOrder();
//	std::cout << "\n";
//	bst->preOrderNR();
//	std::cout << "\n";
//	bst->inOrder();
//	std::cout << "\n";
//	bst->inOrderNR();
//	std::cout << "\n";
//	bst->postOrder();
//	std::cout << "\n";
//	bst->postOrderNR();
//	std::cout << "\n";
//	bst->levelOrder();
//  std::cout << "\n";
	std::cout << bst->removeMin() << std::endl;
//	std::cout << bst->removeMax() << std::endl;
//  bst->inOrder();
//	std::cout << "\n";
	bst->add(7);
	bst->inOrder();
	std::cout << "\n";
	bst->remove(4);
	bst->inOrder();
	std::cout << "\n";
	std::cout << bst->getSize() << std::endl;
}