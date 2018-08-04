#include <iostream>
#include "LinkedList.h"
int main()
{
	auto link = new LinkedList<int>;
	for(int i = 0 ; i < 10 ; ++i)
	{
		link->addFirst(i);
	}
	std::cout << link->getSize() << std::endl;
	link->toString2();
	link->add(1,111);
	link->addLast(999);
	link->toString2();
	std::cout << link->getData(1) << std::endl;
	std::cout << link->getFirst() << std::endl;
	std::cout << link->getLast() << std::endl;
	link->set(1,666);
	link->toString2();
	std::cout << link->contains(777) << std::endl;
	link->remove(0);
	std::cout << link->getSize() << std::endl;
	link->toString2();
	link->removeFirst();
	link->toString2();
	link->removeLast();
	link->toString2();
	link->removeElement(5);
	link->toString2();
	std::cout << link->getSize() << std::endl;
}
