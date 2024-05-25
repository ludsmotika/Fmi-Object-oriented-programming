#pragma once
#include <iostream>

template<typename T, const unsigned N>
class Stack
{
public:
	void push(const T& el);
	void push(T&& el);
	void pop();
	const T& peek() const;

	bool isEmpty();

private:
	T arr[N];
	size_t count = 0;
};

template<typename T, const unsigned N>
void Stack<T,N>::push(const T& el)
{
	if (count == N)
		throw std::logic_error("Stack is full!");

	arr[count++] = el;
}

template<typename T, const unsigned N>
void Stack<T, N>::push(T&& el)
{
	if (count == N)
		throw std::logic_error("Stack is full!");

	arr[count++] = std::move(el);
}

template<typename T, const unsigned N>
void Stack<T, N>::pop()
{
	if (isEmpty())
		throw std::logic_error("Stack is empty!");

	count--;
}

template<typename T, const unsigned N>
const T& Stack<T, N>::peek() const
{
	if (isEmpty())
		throw std::logic_error("Stack is empty!");

	return arr[count - 1];
}

template<typename T, const unsigned N>
bool Stack<T, N>::isEmpty()
{
	return count == 0;
}