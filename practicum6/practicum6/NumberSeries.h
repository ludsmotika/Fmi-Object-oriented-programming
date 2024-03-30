#pragma once

namespace
{
	constexpr int STARTING_CAPACITY = 8;
}

class NumberSeries
{
private:
	int* nums;
	unsigned savedNumsCount = 0;
	unsigned capacity = 0;
	int (*transitionFunction) (int);

	void free();
	void copyFrom(const NumberSeries& other);
public:
	NumberSeries(int firstNum, int (*tr) (int));
	NumberSeries(const NumberSeries& other);
	NumberSeries& operator= (const NumberSeries& other);
	~NumberSeries();

	bool isNumberInTheSeries(int num);
	void setNewStartingValue(int num);
	void setNewTransitionFunction(int (*newTransitionFunction) (int));

	int generateNumberByIndex(int index);
};