#include "Animal.h"
#include "Dog.h"
#include <iostream>

Dog::Dog() : Animal(AnimalType::Dog) {};

Animal* Dog::clone() const
{
	return new(std::nothrow) Dog(*this);
}

void Dog::roar() const
{
	std::cout << "bau";
}
