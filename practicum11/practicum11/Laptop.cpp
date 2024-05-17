#include "Laptop.h"
#include <iostream>

void Laptop::print()
{
	std::cout << "Laptop";
}

const char* Laptop::devicesToConnect()
{
	return "mousepad, keyboard and monitor";
}