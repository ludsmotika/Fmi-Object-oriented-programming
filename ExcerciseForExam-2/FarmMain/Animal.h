#pragma once

enum class AnimalType
{
	Dog,
	Cat,
	Cow
};

class Animal 
{
public:
	Animal(AnimalType type) : type(type) {};

	virtual Animal* clone() const =0;
	virtual void roar() const = 0; 
	virtual ~Animal() = default;

	AnimalType getType() const
	{
		return type;
	}
private:
	AnimalType type;
};