#pragma once
#include <iostream>

template<typename T, const unsigned S>
class MyStack
{
private:
	T data[S];
	size_t size = 0;
public:

	void push(const T& element)
	{
		if (size >= S)
			throw std::logic_error("The stack is full!");

		data[size++] = element; // operator =
	}

	void push(T&& element)
	{
		if (size >= S)
			throw std::logic_error("The stack is full!");

		data[size++] = std::move(element); // move operator =
	}

	void pop() 
	{
		if (isEmpty())
			throw std::logic_error("The stack is empty!");

		size--;
	}

	const T& peek() 
	{
		if (isEmpty())
			throw std::logic_error("The stack is empty!");

		return data[size-1];
	}

	bool isEmpty() 
	{
		return size == 0;
	}
};