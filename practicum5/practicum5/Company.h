#pragma once

#include "Department.h";
#include "ErrorCode.h";

namespace 
{
	constexpr int DEPARTMENTS_MAX_COUNT_IN_COMPANY = 10;
}

class Company
{
private:
	Department departments[DEPARTMENTS_MAX_COUNT_IN_COMPANY];
	unsigned countOfDepartments = 0;
public:
	Company() = default;
	ErrorCode addDepartment(const char* name);
	ErrorCode removeDepartment(const char* name);
	ErrorCode addEmployeeToDepartment(const char* departmentName, const Employee& employee);
	ErrorCode removeEmployeeFromDepartment(const char* departmentName, unsigned id);
	unsigned getCountOfDepartments()const;
	const Department* getDepartments() const;
};