#pragma once
#include "MyString.h"
#include "Order.h"

class Restaurant
{
public:
	Restaurant();
	Restaurant(const char* restaurantName, unsigned  maxProductsCount);
	Restaurant(const Restaurant& other);
	Restaurant(Restaurant&& other);
	~Restaurant();

	Restaurant& operator=(const Restaurant& other);
	Restaurant& operator=(Restaurant&& other);

	void addProduct(const char* productName);
	void receiveOrder(const Order& order);

	const char* getName() const;
	int getProductsCount() const;

private:
	char name[RESTAURANT_NAME_MAXLEN];
	MyString* products;
	unsigned  productsCount;
	unsigned  maxProductsCount;

	void free();
	void copyFrom(const Restaurant& other);
	void moveFrom(Restaurant&& other);

	void setName(const char* name);
};

namespace
{
	constexpr int RESTAURANT_NAME_MAXLEN = 25;
}