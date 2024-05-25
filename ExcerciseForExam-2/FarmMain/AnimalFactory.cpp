#include "AnimalFactory.h"
#include "Dog.h"
#include "Cat.h"
#include "Cow.h"
#include <iostream>

Animal* animalFactory(AnimalType type) 
{
	switch (type)
	{
	case AnimalType::Dog:
		return new Cat();

		break;
	case AnimalType::Cat:
		return new Dog();

		break;
	case AnimalType::Cow:
		return new Cow();
		break;
	default:
		break;
	}

	return nullptr;
}