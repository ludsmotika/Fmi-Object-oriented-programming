#pragma once
#include "Computer.h";

class GamingConsole : public Computer
{
	void print() override;
	const char* devicesToConnect() override;
};