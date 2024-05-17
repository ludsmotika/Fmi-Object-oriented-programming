#pragma once
#include "StudentDB.h"

class SortedStudentDB : public StudentDB
{
public:
	void sortBy(bool (*isLess) (const Student& first, const Student& second));
};