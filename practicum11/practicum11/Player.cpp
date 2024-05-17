#include "Player.h"

Player::Player(int id)
{
	this->id = id;
	this->stars = Stars::One;
	this->points = 1;
}

void Player::completeNextMission()
{
	this->points *= 2;
}

bool Player::levelUp()
{
	int currentStars = (int)this->stars;
	int pointsNeededToLevelUp = 0;
	switch (currentStars)
	{
	case 1:
		pointsNeededToLevelUp = 256;
		break;
	case 2:
		pointsNeededToLevelUp = 512;
		break;
	case 3:
		pointsNeededToLevelUp = 1024;
		break;
	case 4:
		pointsNeededToLevelUp = 2048;
		break;
	default:
		break;
	}

	if (pointsNeededToLevelUp == 0)
		return false;

	if (this->points >=pointsNeededToLevelUp)
	{
		this->stars = (Stars)++currentStars;
		this->points -= pointsNeededToLevelUp;
		return true;
	}

	return false;
}

Player::~Player()
{

}

int Player::getId() const 
{
	return this->id;
}

unsigned Player::getPoints() const 
{
	return this->points;
}

Stars Player::getStars() const 
{
	return this->stars;
}