#include "Computer.h"
#include <iostream>


void Computer::copyFrom(const Computer& other) 
{
	this->graphicCardModel = new char[std::strlen(other.graphicCardModel) + 1];
	std::strcpy(this->graphicCardModel, other.graphicCardModel);

	this->powerInput = other.powerInput;
	this->ram = other.ram;
	this->processorPower = other.processorPower;
}

void Computer::free() 
{
	delete[] this->graphicCardModel;
}

void Computer::moveFrom(Computer&& other) 
{
	this->graphicCardModel = other.graphicCardModel;
	other.graphicCardModel = nullptr;
}

Computer::Computer(const Computer& other) 
{
	copyFrom(other);
}

Computer& Computer::operator = (const Computer& other) 
{
	if (this != &other)
	{
		this->free();
		copyFrom(other);
	}

	return *this;
}

Computer::Computer(Computer&& other) noexcept
{
	moveFrom(std::move(other));
}

Computer& Computer::operator = (Computer&& other) noexcept
{
	if (this != &other)
	{
		this->free();
		moveFrom(std::move(other));
	}

	return *this;
}


Computer::~Computer()
{
	this->free();
}

void Computer::setProcessorPower(double newPP) 
{
	this->processorPower = newPP;
}

void Computer::setGraphicCardModel(const char* gcm) 
{
	delete[] this->graphicCardModel;
	this->graphicCardModel = new char[std::strlen(gcm)];
	std::strcpy(this->graphicCardModel, gcm);
}

void Computer::setPowerInput(int newPI) 
{
	this->powerInput = newPI;
}

void Computer::setRam(int newR) 
{
	this->ram = newR;
}

double Computer::getProcessorPower() const
{
	return this->processorPower;
}

const char* Computer::getGraphicCardModel() const 
{
	return this->graphicCardModel;
}

int Computer::getPowerInput() const 
{
	return this->powerInput;
}

int Computer::getRam() const
{
	return this->ram;
}