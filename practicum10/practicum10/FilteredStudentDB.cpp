#include "FilteredStudentDB.h"

void FilteredStudentDB::filter(bool toSave(const Student& student)) 
{
	for (size_t i = 0; i < this->getStudentsCount(); i++)
	{
		if (!toSave(this->students[i]))
			this->remove(i);
	}
}

void FilteredStudentDB::limit(unsigned n)
{
	if (n > this->getStudentsCount())
		return;

	for (size_t i = n; i < this->getStudentsCount(); i++)
		this->remove(i);
}