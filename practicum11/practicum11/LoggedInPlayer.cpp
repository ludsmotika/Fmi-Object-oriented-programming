#include "LoggedInPlayer.h"
#include <iostream>

LoggedInPlayer::LoggedInPlayer(const char* password) : Player(1)
{
	setPassword(password);
}

void LoggedInPlayer::setPassword(const char* password)
{
	if (std::strlen(password) <= 8)
	{
		std::strcpy(this->password, password);
	}
	else 
	{
		throw std::logic_error("Invalid password");
	}
}