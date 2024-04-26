#pragma once
#include "MyString.h"

class Student
{
private:
	MyString name;
	unsigned facultatyNumber = 0;
	unsigned course = 0;
public:
	const MyString& getName() const;
	unsigned getFacultatyNumber() const;
	unsigned getCourse() const;

	void display() const;

	Student() = default;
	Student(const MyString& name, unsigned facultatyNumber, unsigned course);
};