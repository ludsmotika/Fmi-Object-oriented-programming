#pragma once
#include <iostream>

class MultiSet
{
private:
	uint8_t* data;
	unsigned N;
	unsigned elementsCountInBucket = 4;
	unsigned bucketsCount = 0;

	void free();
	void copyFrom(const MultiSet& other);
public:
	explicit MultiSet(unsigned N);
	MultiSet(const MultiSet& other);

	MultiSet& operator= (const MultiSet& other);
	~MultiSet();
	void remove(int toRemove);
	int countOfOccurences(int num) const;
	void add(int toAdd);
	void print() const;
	friend MultiSet intersection(const MultiSet& first, const MultiSet& second);
	friend MultiSet unionOfMultisets(const MultiSet& first, const MultiSet& second);
};