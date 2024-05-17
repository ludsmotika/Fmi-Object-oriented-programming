#include "SortedStudentDB.h"
#include <iostream>

void SortedStudentDB::sortBy(bool (*isLess) (const Student& first, const Student& second))
{
	for (size_t i = 0; i < this->getStudentsCount(); i++)
	{
		int currentMinIndex = i;

		for (size_t j = i + 1; j < this->getStudentsCount(); j++)
		{
			if (isLess(this->students[i], this->students[currentMinIndex]))
				currentMinIndex = i;
		}

		if (currentMinIndex != i) 
		{
			Student temp = this->students[i];
			this->students[i] = std::move(this->students[currentMinIndex]);
			this->students[currentMinIndex] = std::move(temp);
		}
	}
}