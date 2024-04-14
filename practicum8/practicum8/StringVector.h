#pragma once
#include "MyString.h";

class StringVector
{
public:
	StringVector(); //
	StringVector(const StringVector& other);//
	const StringVector& operator= (const StringVector& other);//
	~StringVector();//

	size_t size() const;//
	bool empty() const;//
	unsigned erase(unsigned index);//
	void clear();//
	size_t getCapacity() const;//

	void insert(unsigned index, const MyString& string);//
	void push_back(const MyString& string);//
	void pop_back();//

	const MyString& operator[] (int index) const;
	MyString& operator[] (int index);

private:
	void free();//
	void copyFrom(const StringVector& other);//
	void resize();//
	MyString* strings = nullptr;
	size_t stringsCount = 0;
	size_t capacity = 4;
};