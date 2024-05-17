#pragma once
#include "Computer.h";

class PC : public Computer
{
	void print() override;
	const char* devicesToConnect() override;
};