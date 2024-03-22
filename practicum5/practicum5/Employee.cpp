#include "Employee.h"
#include <iostream>;
#pragma warning(disable : 4996)


Employee::Employee(unsigned id, const char* name, const char* position, double salary)
{
	this->id = id;
	std::strcpy(this->name, name);
	std::strcpy(this->position, position);
	this->salary = salary;
}

double Employee::getSalary() const 
{
	return this->salary;
}

ErrorCode Employee::updateSalary(double amount) 
{
	if (amount < 0)
	{
		return ErrorCode::InvalidInput;
	}

	this->salary = amount;
	return ErrorCode::OK;
}

unsigned Employee::getId() const 
{
	return this->id;
}
