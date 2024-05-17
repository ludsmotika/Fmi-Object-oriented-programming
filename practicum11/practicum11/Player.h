#pragma once
#include "Stars.h"

class Player 
{
private:
	int id;
	unsigned points;
	Stars stars;
public:

	Player(int);
	virtual ~Player();

	virtual bool levelUp();
	void completeNextMission();

	int getId() const;
	unsigned getPoints() const;
	Stars getStars() const;
};