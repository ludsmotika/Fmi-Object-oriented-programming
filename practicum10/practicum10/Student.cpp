#include "Student.h"

Student::Student(const MyString& name, unsigned facultatyNumber, unsigned course)
{
	this->name = name;
	this->facultatyNumber = facultatyNumber;
	this->course = course;
}

const MyString& Student::getName() const
{
	return this->name;
}

unsigned Student::getFacultatyNumber() const
{
	return this->facultatyNumber;
}

unsigned Student::getCourse() const
{
	return this->course;
}

void Student::display() const
{
	std::cout << "Student name: " << this->name << std::endl;
	std::cout << "Year: " << this->course << std::endl;
	std::cout << "Facultaty number:" << this->facultatyNumber << std::endl;
}
