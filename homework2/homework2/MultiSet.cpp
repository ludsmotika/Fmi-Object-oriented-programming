#include "MultiSet.h"
#include "GlobalFunctions.h"
#define MIN(a, b) ((a) < (b) ? (a) : (b))
#define MAX(a, b) ((a) > (b) ? (a) : (b))

MultiSet::MultiSet() :MultiSet(10, 1) {}

MultiSet::MultiSet(unsigned n, unsigned k)
{
	this->upperLimit = n;
	this->maxBitsPerNum = k;
	this->maxCountOfOccurrences = std::pow(2, maxBitsPerNum) - 1;
	setBuckets();
}


unsigned MultiSet::getUpperLimit() const
{
	return this->upperLimit;
}

unsigned MultiSet::getMaxBitsPerNum() const
{
	return this->maxBitsPerNum;
}

unsigned MultiSet::getBucketsCount() const
{
	return this->bucketsCount;
}

void MultiSet::setBuckets()
{
	this->bucketsCount = ((upperLimit + 1) * maxBitsPerNum) / BITS_COUNT_IN_BYTE;

	if (((upperLimit + 1) * maxBitsPerNum) % BITS_COUNT_IN_BYTE)
	{
		this->bucketsCount++;
	}

	this->data = new uint8_t[bucketsCount]{ 0 };
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

void MultiSet::free()
{
	delete[] this->data;
	this->data = nullptr;

	this->upperLimit = 0;
	this->maxBitsPerNum = 0;
	this->bucketsCount = 0;
	this->maxCountOfOccurrences = 0;
}

void MultiSet::copyFrom(const MultiSet& other)
{
	this->data = new uint8_t[other.bucketsCount];

	for (int i = 0; i < other.bucketsCount; i++)
	{
		this->data[i] = other.data[i];
	}

	this->bucketsCount = other.bucketsCount;
	this->maxBitsPerNum = other.maxBitsPerNum;
	this->upperLimit = other.upperLimit;
	this->maxCountOfOccurrences = other.maxCountOfOccurrences;
}

void MultiSet::addNumberByCount(unsigned num, unsigned count)
{
	uint8_t countOfOccurrences = this->countOfOccurrencesByNumber(num);

	if ((countOfOccurrences == this->maxCountOfOccurrences) || (num > this->upperLimit) || !count)
	{
		//TODO: throw error or just return
		return;
	}

	unsigned bucketIndex = (num * maxBitsPerNum) / 8;
	unsigned startingIndexInBucket = (num * maxBitsPerNum) % 8;

	countOfOccurrences += count;

	if (countOfOccurrences > this->maxCountOfOccurrences)
		countOfOccurrences = this->maxCountOfOccurrences;

	if (startingIndexInBucket + maxBitsPerNum <= BITS_COUNT_IN_BYTE)
	{
		//every bit for this number is in one bucket

		uint8_t clearMask = std::pow(2, maxBitsPerNum) - 1;
		clearMask <<= ((BITS_COUNT_IN_BYTE - maxBitsPerNum) - startingIndexInBucket);
		this->data[bucketIndex] &= (~clearMask);

		countOfOccurrences <<= ((BITS_COUNT_IN_BYTE - maxBitsPerNum) - startingIndexInBucket);
		this->data[bucketIndex] |= countOfOccurrences;
	}
	else
	{
		int countOfBitsInFirstPart = BITS_COUNT_IN_BYTE - startingIndexInBucket;
		uint8_t firstClearMask = std::pow(2, countOfBitsInFirstPart) - 1;
		this->data[bucketIndex] &= (~firstClearMask);

		int countOfBitsInSecondPart = this->maxBitsPerNum - (BITS_COUNT_IN_BYTE - startingIndexInBucket);
		uint8_t secondClearMask = std::pow(2, countOfBitsInSecondPart) - 1;
		secondClearMask <<= (BITS_COUNT_IN_BYTE - countOfBitsInSecondPart);
		this->data[bucketIndex + 1] &= (~secondClearMask);

		uint8_t firstPart = (countOfOccurrences >> countOfBitsInSecondPart);
		uint8_t secondPart = (countOfOccurrences << (BITS_COUNT_IN_BYTE - countOfBitsInSecondPart));
		this->data[bucketIndex] |= firstPart;
		this->data[bucketIndex + 1] |= secondPart;
	}
}


void MultiSet::addNumber(unsigned num)
{
	addNumberByCount(num, 1);
}


uint8_t MultiSet::countOfOccurrencesByNumber(unsigned num) const
{
	if (num > this->upperLimit)
	{
		return 0;
	}

	unsigned bucketIndex = (num * maxBitsPerNum) / 8;
	unsigned startingIndexInBucket = (num * maxBitsPerNum) % 8;

	if (startingIndexInBucket + maxBitsPerNum <= BITS_COUNT_IN_BYTE)
	{
		uint8_t mask = this->maxCountOfOccurrences;
		mask <<= ((BITS_COUNT_IN_BYTE - maxBitsPerNum) - startingIndexInBucket);

		uint8_t result = (this->data[bucketIndex] & mask);
		return (result >> ((BITS_COUNT_IN_BYTE - maxBitsPerNum) - startingIndexInBucket));
	}
	else
	{
		uint8_t result;

		int countOfBitsInFirstPart = BITS_COUNT_IN_BYTE - startingIndexInBucket;
		uint8_t firstMask = std::pow(2, countOfBitsInFirstPart) - 1;
		result = (this->data[bucketIndex] & firstMask);

		int countOfBitsInSecondPart = this->maxBitsPerNum - (BITS_COUNT_IN_BYTE - startingIndexInBucket);
		result <<= countOfBitsInSecondPart;
		uint8_t secondMask = std::pow(2, countOfBitsInSecondPart) - 1;
		secondMask <<= (BITS_COUNT_IN_BYTE - countOfBitsInSecondPart);
		result |= ((this->data[bucketIndex + 1] & secondMask) >> (BITS_COUNT_IN_BYTE - countOfBitsInSecondPart));

		return result;
	}
}

void MultiSet::print() const
{
	for (size_t i = 0; i <= this->upperLimit; i++)
	{
		int countOfOccurrences = this->countOfOccurrencesByNumber(i);
		if (countOfOccurrences > 0)
		{
			std::cout << "The number: " << i << " occurred, " << countOfOccurrences << " times!" << std::endl;
		}
	}
}

void MultiSet::printBits() const
{
	for (size_t i = 0; i < this->bucketsCount; i++)
	{
		printBitsOfByte(this->data[i]);
		std::cout << " ";
	}

	std::cout << std::endl;
}

MultiSet operator^(const MultiSet& first, const MultiSet& second)
{
	unsigned itersectionSetMaxNum = MIN(first.upperLimit, second.upperLimit);
	unsigned itersectionSetBitsPerNum = MIN(first.maxBitsPerNum, second.maxBitsPerNum);

	MultiSet itersection(itersectionSetMaxNum, itersectionSetBitsPerNum);

	for (size_t i = 0; i <= itersectionSetMaxNum; i++)
	{
		unsigned occurrencesInFirst = first.countOfOccurrencesByNumber(i);
		unsigned occurrencesInSecond = second.countOfOccurrencesByNumber(i);

		if (occurrencesInFirst > 0 && occurrencesInSecond > 0)
			itersection.addNumberByCount(i, MIN(occurrencesInFirst, occurrencesInSecond));
	}

	return itersection;

}

MultiSet operator/(const MultiSet& first, const MultiSet& second)
{
	unsigned differenceSetMaxNum = first.upperLimit;
	unsigned differenceSetBitsPerNum = first.maxBitsPerNum;

	MultiSet differenceSet(differenceSetMaxNum, differenceSetBitsPerNum);

	for (size_t i = 0; i <= differenceSetMaxNum; i++)
	{
		unsigned occurrencesInFirst = first.countOfOccurrencesByNumber(i);
		unsigned occurrencesInSecond = second.countOfOccurrencesByNumber(i);

		if (occurrencesInFirst > occurrencesInSecond)
			differenceSet.addNumberByCount(i, occurrencesInFirst - occurrencesInSecond);
	}

	return differenceSet;
}

MultiSet operator!(const MultiSet& set)
{
	MultiSet complementSet(set.upperLimit, set.maxBitsPerNum);

	for (size_t i = 0; i < set.bucketsCount; i++)
		complementSet.data[i] = ~(set.data[i]);

	return complementSet;
}


// TODO - think about the default constructor
// TODO - think if the serialize is a print with cout stream with predefined operator << >> 
// TODO - do i have to write my own std::pow function