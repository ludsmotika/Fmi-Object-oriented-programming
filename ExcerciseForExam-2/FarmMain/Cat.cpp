#include "Cat.h"
#include "Animal.h"
#include <iostream>

Cat::Cat() : Animal(AnimalType::Cat)
{

}
Animal* Cat::clone() const 
{
	return new(std::nothrow) Cat(*this);
}

void Cat::roar() const 
{
	std::cout << "meow";
}