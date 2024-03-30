#include "NumberSeries.h"
#include <iostream>

void NumberSeries::free()
{
	delete[] this->nums;
}

void NumberSeries::copyFrom(const NumberSeries& other)
{
	this->nums = new int[other.capacity];

	for (size_t i = 0; i < other.savedNumsCount; i++)
		this->nums[i] = other.nums[i];

	this->savedNumsCount = other.savedNumsCount;
	this->capacity = other.capacity;

	this->transitionFunction = other.transitionFunction;
}

NumberSeries::NumberSeries(int firstNum, int (*transitionFunction) (int))
{
	this->nums = new int[STARTING_CAPACITY] {0};
	this->nums[0] = firstNum;
	this->capacity = STARTING_CAPACITY;
	this->transitionFunction = transitionFunction;
	this->savedNumsCount = 1;
}

NumberSeries::NumberSeries(const NumberSeries& other)
{
	copyFrom(other);
}

NumberSeries& NumberSeries::operator= (const NumberSeries& other)
{
	if (this != &other)
	{
		free();
		copyFrom(other);
	}

	return *this;
}

NumberSeries::~NumberSeries()
{
	free();
}

void NumberSeries::setNewStartingValue(int num)
{
	delete[] nums;
	this->nums = new int[STARTING_CAPACITY] {0};
	this->nums[0] = num;
	this->savedNumsCount = 1;
	this->capacity = STARTING_CAPACITY;
}

void NumberSeries::setNewTransitionFunction(int (*newTransitionFunction) (int))
{
	int savedFirstNum = this->nums[0];
	delete[] nums;
	this->nums = new int[STARTING_CAPACITY] {0};
	this->nums[0] = savedFirstNum;
	this->transitionFunction = newTransitionFunction;
	this->savedNumsCount = 1;
	this->capacity = STARTING_CAPACITY;
}

bool NumberSeries::isNumberInTheSeries(int num)
{
	for (size_t i = 0; i < this->savedNumsCount; i++)
	{
		if (this->nums[i] == num)
			return true;
	}

	return false;
}

int NumberSeries::generateNumberByIndex(int index)
{
	index--;

	if (index < 0)
		return this->nums[0];

	if (index < this->savedNumsCount)
		return this->nums[index];

	if (index >= capacity)
	{
		int* newNums = new int[index * 2];

		for (size_t i = 0; i < this->savedNumsCount; i++)
			newNums[i] = this->nums[i];

		delete[] nums;
		this->nums = newNums;
		this->capacity = index * 2;
	}

	for (size_t i = this->savedNumsCount - 1; i < index; i++)
		this->nums[i + 1] = this->transitionFunction(this->nums[i]);

	this->savedNumsCount = index + 1;
	return this->nums[index];
}