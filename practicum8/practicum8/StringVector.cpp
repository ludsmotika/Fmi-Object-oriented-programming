#include "StringVector.h"

StringVector::StringVector()
{
	strings = new MyString[capacity];
}

StringVector::StringVector(const StringVector& other)
{
	copyFrom(other);
}

const StringVector& StringVector::operator= (const StringVector& other)
{
	if (this != &other)
	{
		free();
		copyFrom(other);
	}
	return *this;
}

StringVector::~StringVector()
{
	free();
}

void StringVector::free()
{
	delete[] strings;
}

void StringVector::pop_back()
{
	if (!size())
		throw "Empty vector";

	erase(size() - 1);
}

void StringVector::push_back(const MyString& string)
{
	insert(size(),string);
}

void StringVector::insert(unsigned index, const MyString& string)
{
	if (index<0 || index > size())
		throw "Invalid index!";

	stringsCount++;

	if (stringsCount >= capacity)
	{
		resize();
	}

	for (size_t i = size()-1; i >index; i--)
	{
		strings[i] = strings[i - 1];
	}

	strings[index] = string;
}


void StringVector::copyFrom(const StringVector& other)
{
	strings = new MyString[other.getCapacity()];

	for (size_t i = 0; i < other.size(); i++)
	{
		strings[i] = other.strings[i];
	}

	stringsCount = other.size();
	capacity = other.getCapacity();
}

void StringVector::clear()
{
	free();
	stringsCount = 0;
	strings = new MyString[capacity];
}

const MyString& StringVector::operator[] (int index) const
{
	return strings[index];
}

MyString& StringVector::operator[] (int index)
{
	return strings[index];
}

size_t StringVector::getCapacity() const
{
	return capacity;
}

unsigned StringVector::erase(unsigned index)
{
	if (index < 0 || index >= size())
		throw "Invalid index!";


	for (size_t i = index; i < size(); i++)
	{
		strings[i] = strings[i+1];
	}

	stringsCount--;

	return index;
}

bool StringVector::empty() const
{
	if (!stringsCount)
	{
		return true;
	}

	return false;
}


size_t StringVector::size() const
{
	return stringsCount;
}

void StringVector::resize()
{
	capacity *= 2;
	MyString* newStrings = new MyString[capacity];

	for (size_t i = 0; i < size(); i++)
	{
		newStrings[i] = strings[i];
	}

	delete[] strings;

	strings = newStrings;
}
