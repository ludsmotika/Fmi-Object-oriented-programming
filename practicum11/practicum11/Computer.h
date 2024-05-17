#pragma once


class Computer 
{
private:
	double processorPower;
	char* graphicCardModel;
	int powerInput;
	int ram;

	void copyFrom(const Computer&);
	void free();
	void moveFrom(Computer&&) noexcept;
public:
	Computer() = default;
	Computer(const Computer&);
	Computer& operator = (const Computer&);
	Computer(Computer&&) noexcept;
	Computer& operator = (Computer&&) noexcept;

	virtual ~Computer() noexcept;

	void setProcessorPower(double);
	void setGraphicCardModel(const char*);
	void setPowerInput(int);
	void setRam(int);

	double getProcessorPower() const;
	const char* getGraphicCardModel() const;
	int getPowerInput() const;
	int getRam() const;

	virtual void print() = 0;
	virtual const char* devicesToConnect()=0;
};