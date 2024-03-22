#pragma once

#include "ErrorCode.h";

namespace {
	constexpr int NAME_MAX_SIZE = 127;
	constexpr int POSITION_MAX_SIZE = 127;
}

class Employee
{
private:
	unsigned id = 0;
	char name[NAME_MAX_SIZE];
	char position[POSITION_MAX_SIZE];
	double salary = 0;
public:
	Employee() = default;
	Employee(unsigned id, const char* name, const char* position, double salary);
	double getSalary() const;
	unsigned getId() const;
	ErrorCode updateSalary(double amount);
};