#include <iostream>
#include "Company.h"

ErrorCode Company::addDepartment(const char* name)
{
	Department d(name);
	this->departments[this->countOfDepartments++] = d;

	return ErrorCode::OK;
}

ErrorCode Company::removeDepartment(const char* name)
{
	int indexOfDepartment= -1;
	unsigned countOfDepartments = this->getCountOfDepartments();
	const Department* departments = this->getDepartments();

	for (size_t i = 0; i < countOfDepartments; i++)
	{
		if (!std::strcmp(departments[i].getName(), name))
		{
			indexOfDepartment = i;
		}
	}

	if (indexOfDepartment == -1)
	{
		return ErrorCode::NotFound;
	}

	for (size_t i = indexOfDepartment; i < countOfDepartments; i++)
	{
		std::swap(this->departments[i], this->departments[i + 1]);
	}

	this->countOfDepartments--;
}

ErrorCode Company::addEmployeeToDepartment(const char* departmentName, const Employee& employee)
{
	int indexOfDepartment = -1;
	unsigned countOfDepartments = this->getCountOfDepartments();
	const Department* departments = this->getDepartments();

	for (size_t i = 0; i < countOfDepartments; i++)
	{
		if (!std::strcmp(departments[i].getName(), departmentName))
		{
			indexOfDepartment = i;
		}
	}

	if (indexOfDepartment == -1)
	{
		return ErrorCode::NotFound;
	}

	this->departments[indexOfDepartment].addEmployee(employee);
	return ErrorCode::OK;
}

ErrorCode Company::removeEmployeeFromDepartment(const char* departmentName, unsigned id)
{
	int indexOfDepartment = -1;
	unsigned countOfDepartments = this->getCountOfDepartments();
	const Department* departments = this->getDepartments();

	for (size_t i = 0; i < countOfDepartments; i++)
	{
		if (!std::strcmp(departments[i].getName(), departmentName))
		{
			indexOfDepartment = i;
		}
	}

	if (indexOfDepartment == -1)
	{
		return ErrorCode::NotFound;
	}

	this->departments[indexOfDepartment].removeEmployee(id);
}

unsigned Company::getCountOfDepartments()const
{
	return this->countOfDepartments;
}

const Department* Company::getDepartments()const
{
	return this->departments;
}
