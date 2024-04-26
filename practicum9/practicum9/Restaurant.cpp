#include "Restaurant.h"

Restaurant::Restaurant() : Restaurant(" ", 5)
{

}

Restaurant::Restaurant(const char* restaurantName, unsigned maxProductsCount)
{
	this->maxProductsCount = maxProductsCount;
	this->products = new MyString[this->maxProductsCount];
	this->productsCount = 0;
	setName(restaurantName);
}

Restaurant::Restaurant(const Restaurant& other)
{
	copyFrom(other);
}

Restaurant::Restaurant(Restaurant&& other)
{
	moveFrom(std::move(other));
}

Restaurant::~Restaurant()
{
	this->free();
}

void Restaurant::setName(const char* name)
{
	if (std::strlen(name) >= 25)
		throw std::logic_error("Restaurant cannot have name this long!");

	std::strcpy(this->name, name);
}

void  Restaurant::free()
{
	delete[] products;
}

void  Restaurant::copyFrom(const Restaurant& other)
{
	std::strcpy(this->name, other.name);
	this->products = new MyString(other.maxProductsCount);

	for (size_t i = 0; i < other.productsCount; i++)
		this->products[i] = other.products[i];

	this->productsCount = other.productsCount;
	this->maxProductsCount = other.maxProductsCount;
}

void  Restaurant::moveFrom(Restaurant&& other)
{
	this->products = other.products;
	other.products = nullptr;

	this->name = other.name;
	other.name = nullptr;

	this->maxProductsCount = other.maxProductsCount;
	this->productsCount = other.productsCount;
}