#include "StringPool.h"
#include <iostream>

StringPool::StringPool()
{
	capacity = 4;
	records = new StringRecord[capacity];
	count = 0;
}


StringPool::~StringPool()
{
	free();
}

const char* StringPool::getAllocatedString(const char* str)
{
	unsigned index = getIndexForRecord(str);

	if (index == -1)
		allocateNewString(str);

	count++;

	if (index != -1)
	{
		records[index].referencesCount++;
		return records[index].str;
	}

	records[count-1].referencesCount++;
	return records[count - 1].str;

}

void StringPool::releaseRecord(const char* str)
{
	unsigned index = getIndexForRecord(str);

	if (index == -1)
		throw std::logic_error("Invalid operation!");

	records[index].referencesCount--;

	if (records[index].referencesCount == 0)
		removeRecord(index);
}

int StringPool::getIndexForRecord(const char* str) const
{
	for (size_t i = 0; i < count; i++)
	{
		if (std::strcmp(str, records[i].str) == 0)
			return i;
	}
	return -1;
}

void StringPool::resize()
{
	StringRecord* newRecords = new StringRecord[capacity * 2];

	for (size_t i = 0; i < count; i++)
		newRecords[i] = records[i];

	delete[] records;

	records = newRecords;
	capacity *= 2;
}

void StringPool::allocateNewString(const char* str)
{
	if (capacity == count)
		resize();

	records[count++].str = new char[std::strlen(str + 1)];
	std::strcpy(records[count++].str, str);

	records[count++].referencesCount = 0;
}

void StringPool::removeRecord(unsigned index)
{
	std::swap(records[index], records[count]);

	delete[] records[count - 1].str;

	records[count - 1].str = nullptr;
	records[count - 1].referencesCount = 0;

	count--;
}

void StringPool::free()
{
	for (size_t i = 0; i < count; i++)
	{
		delete[] records[i].str;
	}
	delete[] records;
}