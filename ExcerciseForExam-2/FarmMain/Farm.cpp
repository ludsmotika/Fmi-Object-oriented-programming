#include "Farm.h"
#include <iostream>

Farm::Farm()
{
	capacity = 8;
	animals = new Animal * [capacity];
	count = 0;
}

Farm::Farm(const Farm& other)
{
	copyFrom(other);
}

Farm& Farm::operator = (const Farm& other)
{
	if (this != &other)
	{
		free();
		copyFrom(other);
	}

	return *this;
}

Farm::Farm(Farm&& other) noexcept
{
	moveFrom(std::move(other));
}

Farm& Farm::operator = (Farm&& other) noexcept
{
	if (this != &other)
	{
		free();
		moveFrom(std::move(other));
	}

	return *this;
}

Farm::~Farm()
{
	free();
}


void Farm::addAnimal(AnimalType animalType)
{
	if (count >= capacity)
		resize();

	animals[count++] = animalFactory(animalType);
}

void Farm::addAnimal(const Animal& animal)
{
	if (count >= capacity)
		resize();

	animals[count++] = animal.clone();
}

void Farm::roarAll() const
{
	for (size_t i = 0; i < count; i++)
		animals[i]->roar();
}

AnimalType Farm::getTypeByIndex(unsigned index) const
{
	if (index > count)
		throw std::out_of_range("Invalid index");

	return animals[index]->getType();
}

void Farm::copyFrom(const Farm& other)
{
	animals = new Animal * [other.capacity];

	for (size_t i = 0; i < other.count; i++)
	{
		Animal* cloned = other.animals[i]->clone();
		if (cloned)
			animals[i] = cloned;
	}

	count = other.count;
	capacity = other.capacity;
}

void Farm::moveFrom(Farm&& other)
{
	animals = other.animals;
	other.animals = nullptr;

	count = other.count;
	capacity = other.capacity;
}

void Farm::free()
{
	for (size_t i = 0; i < count; i++)
		delete animals[i];
	
	delete[] animals;
}

void Farm::resize()
{
	Animal** newAnimals = new Animal * [capacity * 2];

	for (size_t i = 0; i < count; i++)
	{
		newAnimals[i] = animals[i];
	}

	delete[] animals;

	capacity *= 2;
	animals = newAnimals;
}