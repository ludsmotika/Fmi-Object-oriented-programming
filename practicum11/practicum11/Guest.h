#pragma once
#include "Player.h"

class Guest : public Player 
{
private:
	unsigned minutesToPlay;
public:
	Guest();

	bool levelUp() override;
};