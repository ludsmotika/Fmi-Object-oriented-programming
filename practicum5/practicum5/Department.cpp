#include "Department.h"
#include <iostream>

Department::Department(const char* name) 
{
	std::strcpy(this->name, name);
}

ErrorCode Department::addEmployee(const Employee& employee) 
{
	this->employees[this->countOfEmployees] = employee;
	return ErrorCode::OK;
}

unsigned Department::getCountOfEmployees() const 
{
	return this->countOfEmployees;
}
const Employee* Department::getEmployees() const 
{
	return this->employees;
}


ErrorCode Department::removeEmployee(unsigned id) 
{
	int indexOfEmployee = -1;
	unsigned countOfEmployees = this->getCountOfEmployees();
	const Employee* employees = this->getEmployees();
	for (size_t i = 0; i < countOfEmployees; i++)
	{
		if (id == employees[i].getId())
		{
			indexOfEmployee = i;
		}
	}

	if (indexOfEmployee == -1)
	{
		return ErrorCode::NotFound;
	}
	
	for (size_t i = indexOfEmployee; i < countOfEmployees; i++)
	{
		std::swap(this->employees[i], this->employees[i+1]);
	}

	this->countOfEmployees--;
}

const char* Department::getName() const
{
	return this->name;
}
