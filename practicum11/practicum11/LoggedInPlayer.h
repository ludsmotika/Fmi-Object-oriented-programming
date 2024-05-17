#pragma once
#include "Player.h"
class LoggedInPlayer : public Player
{
private:
	char password[8];
	void setPassword(const char*);
public:
	LoggedInPlayer(const char*);
};