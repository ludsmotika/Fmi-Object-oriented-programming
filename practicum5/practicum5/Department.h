#pragma once

#include "Employee.h";
#include "ErrorCode.h";

namespace 
{
	constexpr int NAME_MAX_LENGTH = 127;
	constexpr int MAX_EMPLOYEES_COUNT_IN_DEPARTMENT = 15;
}

class Department 
{
private:
	char name[NAME_MAX_LENGTH];
	Employee employees[MAX_EMPLOYEES_COUNT_IN_DEPARTMENT];
	unsigned countOfEmployees = 0;
public:
	Department() = default;
	explicit Department(const char* name);
	ErrorCode addEmployee(const Employee& employee);
	ErrorCode removeEmployee(unsigned id);
	unsigned getCountOfEmployees() const;
	const Employee* getEmployees() const;
	const char* getName() const;
};

//error code including
//empoloyees in constructor