#include "Cow.h"
#include "Animal.h"
#include <iostream>

Cow::Cow() : Animal(AnimalType::Cat)
{

}
Animal* Cow::clone() const
{
	return new(std::nothrow) Cow(*this);
}

void Cow::roar() const
{
	std::cout << "moo";
}