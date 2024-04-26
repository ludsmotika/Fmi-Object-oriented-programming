#pragma once
#include "MyString.h"

class Order
{
private:
	char* restaurantName;
	unsigned productsCount;
	MyString* products;

	void calculateDeliveryTime();

	bool isDeliveryTimeCalculated = false;
	unsigned deliveryTime;

	void copyFrom(const Order& other);
	void moveFrom(Order&& other);
	void free();
public:

	Order();
	Order(const char* restaurantName, unsigned productsCount, MyString);
	Order(const Order& other);
	Order(Order&& other);
	~Order();
	Order& operator= (const Order& other);
	Order& operator= (Order&& other);

	void addProduct(const char* productName);

	unsigned getDeliveryTime();
	const char* getRestaurantName() const;
	unsigned getProductsCount() const;
	const MyString& getProducts() const;
};