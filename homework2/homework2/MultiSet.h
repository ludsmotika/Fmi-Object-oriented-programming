#pragma once
#include <iostream>;

class MultiSet 
{
public:
	MultiSet();
	MultiSet(unsigned n, unsigned k);//
	MultiSet(const MultiSet& other);//
	MultiSet& operator= (const MultiSet& other);//
	~MultiSet();//

	unsigned getUpperLimit() const;//
	unsigned getMaxBitsPerNum() const;//
	unsigned getBucketsCount() const;//

	void addNumber(unsigned num);//
	void addNumberByCount(unsigned num,unsigned count);//
	uint8_t countOfOccurrencesByNumber(unsigned num) const;//

	void print() const;//
	void printBits() const;//

	friend MultiSet operator^(const MultiSet& first, const MultiSet& second);
	friend MultiSet operator/(const MultiSet& first, const MultiSet& second);
	friend MultiSet operator!(const MultiSet& set);
private:
	unsigned upperLimit = 0;
	unsigned maxBitsPerNum = 0;
	uint8_t* data = nullptr;
	unsigned bucketsCount=0;
	unsigned maxCountOfOccurrences = 0;
 
	void free();//
	void copyFrom(const MultiSet& other);//

	void setBuckets();//
};

namespace 
{
	constexpr unsigned BITS_COUNT_IN_BYTE = 8;
}