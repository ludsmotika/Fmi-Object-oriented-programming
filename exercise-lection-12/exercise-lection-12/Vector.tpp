#include "Vector.h"
#include <iostream>

template<typename T>
Vector<T>::Vector()
{
	elements = new T[];
}

template<typename T>
Vector<T>::Vector(const Vector& other)
{
	copyFrom(other);
}

template<typename T>
Vector<T>::Vector(Vector&& other) noexcept
{
	moveFrom(std::move(other));
}

template<typename T>
void Vector<T>::moveFrom(Vector&& other)
{
	this->elements = other.elements;
	other.elements = nullptr;

	this->capacity = other.capacity;
	other.capacity = 0;

	this->elementsCount = other.elementsCount;
	other.elementsCount = 0;
}

template<typename T>
Vector<T>& Vector<T>::operator= (Vector&& other)
{
	if (this != &other)
	{
		free();
		moveFrom(std::move(other));
	}

	return *this;
}

template<typename T>
const Vector<T>& Vector<T>::operator= (const Vector& other)
{
	if (this != &other)
	{
		free();
		copyFrom(other);
	}
	return *this;
}

template<typename T>
Vector<T>::~Vector()
{
	free();
}

template<typename T>
void Vector<T>::free()
{
	delete[] elements;
}

template<typename T>
void Vector<T>::pop_back()
{
	if (!size())
		throw "Empty vector";

	erase(size() - 1);
}

template<typename T>
void Vector<T>::push_back(const T& string)
{
	insert(size(), string);
}

template<typename T>
void Vector<T>::push_back(T&& string)
{
	insert(size(), std::move(string));
}

template<typename T>
void Vector<T>::insert(unsigned index, T&& element)
{
	if (index<0 || index > size())
		throw "Invalid index!";

	elementsCount++;

	if (elementsCount >= capacity)
	{
		resize();
	}

	for (size_t i = size() - 1; i > index; i--)
	{
		elements[i] = std::move(elements[i - 1]);
	}

	elements[index] = std::move(element);
}

template<typename T>
void Vector<T>::insert(unsigned index, const T& element)
{
	if (index<0 || index > size())
		throw "Invalid index!";

	elementsCount++;

	if (elementsCount >= capacity)
	{
		resize();
	}

	for (size_t i = size() - 1; i > index; i--)
	{
		elements[i] = elements[i - 1];
	}

	elements[index] = element;
}


template<typename T>
void Vector<T>::copyFrom(const Vector& other)
{
	elements = new T[other.getCapacity()];

	for (size_t i = 0; i < other.size(); i++)
	{
		elements[i] = other.elements[i];
	}

	elementsCount = other.size();
	capacity = other.getCapacity();
}

template<typename T>
void Vector<T>::clear()
{
	free();
	elementsCount= 0;
	elements = new T[capacity];
}

template<typename T>
const T& Vector<T>::operator[] (int index) const
{
	return elements[index];
}

template<typename T>
T& Vector<T>::operator[] (int index)
{
	return elements[index];
}

template<typename T>
size_t Vector<T>::getCapacity() const
{
	return capacity;
}

template<typename T>
unsigned Vector<T>::erase(unsigned index)
{
	if (index < 0 || index >= size())
		throw "Invalid index!";


	for (size_t i = index; i < size(); i++)
	{
		elements[i] = elements[i + 1];
	}

	elementsCount--;

	return index;
}

template<typename T>
bool Vector<T>::empty() const
{
	if (!elementsCount)
	{
		return true;
	}

	return false;
}


template<typename T>
size_t Vector<T>::size() const
{
	return elementsCount;
}

template<typename T>
void Vector<T>::resize()
{
	capacity *= 2;
	T* newElements = new T[capacity];

	for (size_t i = 0; i < size(); i++)
	{
		newElements[i] = elements[i];
	}

	delete[] elements;

	elements= newElements;
}