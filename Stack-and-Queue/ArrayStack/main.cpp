#include "ArrayStack.h"

int main()
{
	ArrayStack<int>* stack = new ArrayStack<int>();
	for(int i = 0 ; i < 10 ; ++i) 
	{
		stack->push(i);
	}
	stack->toString();
	cout << "top:" << stack->peek() <<endl;
	for(int i = 0 ; i < 5 ; ++i)
	{
		stack->pop();
	}
	stack->toString();
	cout << "top:" << stack->peek() <<endl;
	return 0;
}
