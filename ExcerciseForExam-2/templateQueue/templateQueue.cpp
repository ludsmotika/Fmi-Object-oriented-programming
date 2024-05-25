#include <iostream>
#include "Stack.hpp"
#include "Queue.hpp"

int main()
{

	MyStack<Queue<int>, 5> intStack;
	Queue<int> a;
	a.push(1);

	intStack.push(a);

	std::cout << intStack.peek().peek();	
	intStack.pop();

}
