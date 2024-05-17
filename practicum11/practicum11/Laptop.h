#pragma once
#include "Computer.h";

class Laptop : public Computer
{
	void print() override;
	const char* devicesToConnect() override;
};