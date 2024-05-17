#pragma once
#include "Vector.h";

template<typename T>
class Queue 
{
private:
	Vector<T> elements;
public:
	void push(const T& element);
	T& pop();
	T peek() const;
	bool isEmpty() const;
};

#include "Queue.h"
#include <iostream>

template<typename T>
void Queue<T>::push(const T& element)
{
	this->elements.push_back(element);
}

template<typename T>
T& Queue<T>::pop()
{
	if (this->isEmpty())
		throw std::logic_error("Queue is empty!");

	T& toPop = this->elements[0];
	this->elements.erase(0);

	return toPop;
}

template<typename T>
T Queue<T>::peek() const
{
	if (this->isEmpty())
		throw std::logic_error("Queue is empty!");

	return this->elements[0];
}

template<typename T>
bool Queue<T>::isEmpty() const
{
	return this->elements.empty();
}