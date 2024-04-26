#pragma once
#include "Restaurant.h"
class FoodPanda 
{
private:
	Restaurant* restaurants;
	unsigned restaurantsCount;

	void free();
	void copyFrom(const FoodPanda& other);
	void moveFrom(FoodPanda&& other);
public:

	FoodPanda();
	FoodPanda(unsigned restaurantsCount);
	FoodPanda(const FoodPanda& other);
	FoodPanda(FoodPanda&& other);
	~FoodPanda();

	FoodPanda& operator=(const FoodPanda& other);
	FoodPanda& operator=(FoodPanda&& other);

	void addProductToRestaurant(const char* restaurantName, const char* productName);
	void addRestaurant(const char* restaurantName);
	void delivery(const Order& order, const char* restaurantName);
};