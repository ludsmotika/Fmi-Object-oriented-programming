#include "MultiSet.h"

void MultiSet::free()
{
	delete[] data;
}

void MultiSet::copyFrom(const MultiSet& other)
{
	this->data = new uint8_t[other.bucketsCount];

	for (size_t i = 0; i < other.bucketsCount; i++)
		this->data[i] = other.data[i];

	this->N = other.N;
	this->elementsCountInBucket = other.elementsCountInBucket;
	this->bucketsCount = other.bucketsCount;
}

MultiSet::MultiSet(unsigned N)
{
	this->N = N-1;
	this->bucketsCount = (N / elementsCountInBucket) + 1;
	this->data = new uint8_t[bucketsCount]{0};
}

MultiSet::MultiSet(const MultiSet& other)
{
	copyFrom(other);
}

MultiSet& MultiSet::operator= (const MultiSet& other)
{
	if (this != &other)
	{
		free();
		copyFrom(other);
	}

	return *this;
}

MultiSet::~MultiSet()
{
	free();
}

void MultiSet::remove(int toRemove)
{
	uint8_t count = countOfOccurences(toRemove);

	if (toRemove > this->N || toRemove < 0 || count <=0 )
		return;

	int bucketIndex = (toRemove / this->elementsCountInBucket);
	int numFirstIndex = (toRemove % this->elementsCountInBucket) * 2;

	uint8_t mask = count - 1;
	mask <<= numFirstIndex;

	uint8_t maskForRemoving = 3;
	maskForRemoving <<= numFirstIndex;

	data[bucketIndex] &= (~maskForRemoving);
	data[bucketIndex] |= mask;
}

int MultiSet::countOfOccurences(int num) const
{
	if (num > this->N || num < 0)
	{
		return 0;
	}

	int bucketIndex = (num / this->elementsCountInBucket);
	int numFirstIndex = (num % this->elementsCountInBucket) * 2;

	uint8_t mask = 3;
	mask <<= numFirstIndex;

	int count = mask & this->data[bucketIndex];
	count >>= numFirstIndex;

	return count;
}

void MultiSet::add(int toAdd)
{
	uint8_t count = countOfOccurences(toAdd);

	if (toAdd > this->N || toAdd < 0 || count >= 3)
		return;

	int bucketIndex = (toAdd / this->elementsCountInBucket);
	int numFirstIndex = (toAdd % this->elementsCountInBucket) * 2;

	uint8_t mask = count + 1;

	mask <<= numFirstIndex;

	uint8_t maskForRemoving = 3;
	maskForRemoving <<= numFirstIndex;

	data[bucketIndex] &= (~maskForRemoving);
	data[bucketIndex] |= mask;
}

void MultiSet::print() const
{
	std::cout << "{" << std::endl;
	for (size_t i = 0; i < this->N; i++)
	{
		int count = countOfOccurences(i);
		if (count != 0)
		{
			std::cout << "The number: " << i << " occured: " << count << "times, " << std::endl;
		}
	}
	std::cout << "}" << std::endl;
}

MultiSet intersection(const MultiSet& first, const MultiSet& second)
{
	MultiSet result(std::min(first.N, second.N));

	const MultiSet& smallerSet = (first.N < second.N ? first : second);
	for (size_t i = 0; i < smallerSet.N; i++)
	{
		uint8_t count = std::min(first.countOfOccurences(i) , second.countOfOccurences(i));

		if (count == 0)
		{
			continue;
		}

		int bucketIndex = (i / first.elementsCountInBucket);
		int numFirstIndex = (i % first.elementsCountInBucket) * 2;

		count <<= numFirstIndex;

		result.data[bucketIndex] |= count;
	}

	return result;
}

MultiSet unionOfMultisets(const MultiSet& first, const MultiSet& second)
{
	MultiSet result(std::max(first.N, second.N));

	const MultiSet& smallerSet = (first.N < second.N ? first : second);
	for (size_t i = 0; i < smallerSet.N; i++)
	{
		uint8_t count = first.countOfOccurences(i) + second.countOfOccurences(i);

		if (count == 0)
			continue;

		if (count > 3)
			count = 3;

		int bucketIndex = (i / first.elementsCountInBucket);
		int numFirstIndex = (i % first.elementsCountInBucket) * 2;

		count <<= numFirstIndex;

		result.data[bucketIndex] |= count;
	}

	const MultiSet& biggerSet = (first.N < second.N ? second : first);

	for (size_t i = smallerSet.N; i < biggerSet.N; i++)
	{
		uint8_t count = biggerSet.countOfOccurences(i);
		if (count ==0)
		{
			continue;
		}

		int bucketIndex = (i / first.elementsCountInBucket);
		int numFirstIndex = (i % first.elementsCountInBucket) * 2;

		count <<= numFirstIndex;

		result.data[bucketIndex] |= count;
	}

	return result;
}