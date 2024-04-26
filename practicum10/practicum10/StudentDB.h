#pragma once
#include "Student.h"

class StudentDB 
{
private:
	Student* students;
	unsigned studentsCount;
	unsigned capacity;

	void free();
	void moveFrom(StudentDB&& other) noexcept;
	void copyFrom(const StudentDB& other);

	void resize();

	void swapTwoStudents(unsigned firstIndex, unsigned secondIndex);
public:

	StudentDB();
	StudentDB(unsigned maxStudentsCount);
	StudentDB(const StudentDB& other);
	StudentDB(StudentDB&& other) noexcept;
	~StudentDB() noexcept;

	StudentDB& operator= (const StudentDB& other);
	StudentDB& operator= (StudentDB&& other) noexcept;

	void add(const Student& student);
	void add(Student&& student);

	void remove(unsigned facultatyNumber);

	unsigned find(unsigned facultatyNumber) const;

	void display() const;

	unsigned getStudentsCount() const;
	unsigned getCapacity() const;
};