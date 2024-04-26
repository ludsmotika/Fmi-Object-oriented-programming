#include "StudentDB.h"

void StudentDB::free()
{
	delete[] this->students;

	this->capacity = 0;
	this->studentsCount = 0;
}

void StudentDB::moveFrom(StudentDB&& other) noexcept
{
	this->students = other.students;
	other.students = nullptr;

	this->capacity = other.capacity;
	this->studentsCount = other.studentsCount;
}

void StudentDB::copyFrom(const StudentDB& other)
{
	this->students = new Student[other.capacity];

	for (size_t i = 0; i < other.studentsCount; i++)
		this->students[i] = other.students[i];

	this->studentsCount = other.studentsCount;
	this->capacity = other.capacity;
}


StudentDB::StudentDB() : StudentDB(8)
{

}

StudentDB::StudentDB(unsigned maxStudentsCount)
{
	this->students = new Student[maxStudentsCount];
	this->studentsCount = 0;
	this->capacity = maxStudentsCount;
}

StudentDB::StudentDB(const StudentDB& other)
{
	copyFrom(other);
}

StudentDB::StudentDB(StudentDB&& other) noexcept
{
	moveFrom(std::move(other));
}

StudentDB::~StudentDB()
{
	this->free();
}


StudentDB& StudentDB::operator= (const StudentDB& other)
{
	if (this != &other)
	{
		this->free();
		this->copyFrom(other);
	}

	return *this;
}

StudentDB& StudentDB::operator= (StudentDB&& other) noexcept
{
	if (this != &other)
	{
		this->free();
		this->moveFrom(std::move(other));
	}

	return *this;
}

unsigned StudentDB::getStudentsCount() const
{
	return this->studentsCount;
}

unsigned StudentDB::getCapacity() const
{
	return this->capacity;
}

void StudentDB::resize()
{
	Student* newArray = new Student[this->capacity * 2];

	for (size_t i = 0; i < this->getStudentsCount(); i++)
	{
		newArray[i] = this->students[i];
	}

	delete[] this->students;

	this->students = newArray;
	this->capacity *= 2;
}

void StudentDB::add(const Student& student)
{
	if (this->getStudentsCount() == this->getCapacity())
		this->resize();

	this->students[this->studentsCount++] = student;
}

void StudentDB::add(Student&& student)
{
	if (this->getStudentsCount() == this->getCapacity())
		this->resize();

	this->students[this->getStudentsCount()] = std::move(student);
}

void StudentDB::remove(unsigned facultatyNumber)
{
	unsigned index = this->find(facultatyNumber);

	this->swapTwoStudents(index, this->getStudentsCount() - 1);
	this->studentsCount--;
}

void StudentDB::swapTwoStudents(unsigned firstIndex, unsigned secondIndex)
{
	Student temp = this->students[firstIndex];

	this->students[firstIndex] = this->students[secondIndex];
	this->students[secondIndex] = temp;
}

unsigned StudentDB::find(unsigned facultatyNumber) const
{
	for (size_t i = 0; i < this->getStudentsCount(); i++)
	{
		if (this->students[i].getFacultatyNumber() == facultatyNumber)
			return i;
	}

	throw std::logic_error("Student with this facultaty number doesn`t exist!");
}

void StudentDB::display() const
{
	for (size_t i = 0; i < this->getStudentsCount(); i++)
	{
		this->students[i].display();
		std::cout << std::endl;
	}
}