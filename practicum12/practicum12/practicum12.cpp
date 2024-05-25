#include <iostream>
#include "Vector.hpp"

int main()
{
	Vector<double> l;
	l.push_back(2.3);
	l.push_back(12);
	l.push_back(3);


	std::cout << l[0];
	std::cout << l[1];
	l.erase(1);
	std::cout << l[1];
}