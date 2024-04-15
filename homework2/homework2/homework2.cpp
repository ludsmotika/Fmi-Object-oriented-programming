#include <iostream>
#include "MultiSet.h"

int main()
{

	MultiSet m(10, 3);

	m.addNumber(1);
	m.addNumber(1);
	m.addNumber(1);
	m.addNumber(1);
	m.addNumber(1);
	m.addNumber(2);
	m.addNumber(2);
	m.addNumber(2);
	m.addNumber(2);
	m.addNumber(2);
	m.addNumber(2);
	m.addNumber(2);
	m.addNumber(3);
	m.addNumber(3);
	m.addNumber(4);
	m.addNumber(5);
	m.addNumber(5);
	m.addNumber(5);
	m.addNumber(10);
	m.addNumber(10);
	m.addNumber(10);
	m.addNumber(9);
	m.print();
	m.printBits();

	MultiSet m2(5, 4);

	m2.addNumber(1);
	m2.addNumber(1);
	m2.addNumber(1);
	m2.addNumber(1);
	m2.addNumber(1);
	m2.addNumber(1);
	m2.addNumber(1);
	m2.addNumber(1);
	m2.addNumber(1);
	m2.addNumber(2);
	m2.addNumber(2);
	m2.addNumber(3);
	m2.addNumber(3);
	m2.addNumber(4);
	m2.addNumber(5);
	m2.addNumber(5);
	m2.addNumber(10);
	m2.addNumber(10);
	m2.addNumber(10);
	m2.addNumber(9);

	m2.print();
	m2.printBits();

	/*MultiSet intersection = m ^ m2;
	intersection.print();
	intersection.printBits();
	
	MultiSet diff = m/ m2;
	diff.print();
	diff.printBits();*/

	MultiSet complement = !m2;
	complement.print();
	complement.printBits();

}