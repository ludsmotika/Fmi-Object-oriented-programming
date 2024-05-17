#include "PC.h"
#include <iostream>

void PC::print() 
{
	std::cout << "PC";
}

const char* PC::devicesToConnect() 
{
	return "mouse, keyboard, microphone and headphones";
}