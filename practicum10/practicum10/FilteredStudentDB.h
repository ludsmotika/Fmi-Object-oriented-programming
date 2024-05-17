#pragma once
#include "StudentDB.h" 

class FilteredStudentDB : public StudentDB
{
public:
	void filter(bool toSave(const Student& student));
	void limit(unsigned n);
};