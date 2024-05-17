#include "GamingConsole.h"
#include <iostream>

void GamingConsole::print()
{
	std::cout << "PC";
}

const char* GamingConsole::devicesToConnect()
{
	return "monitor and joystick";
}