#include "Circle.h"

Circle::Circle(double radius, int x, int y) : Shape(1), radius(radius) 
{
	setPoint(0, x, y);
}

bool Circle::intersectsWith(const Shape* other) const 
{
	return other->intersectsWithCircle(this);
}

bool Circle::intersectsWithTriangle(const Triangle* other) const 
{
	return true;
}

bool Circle::intersectsWithRect(const Rectangle* other) const 
{
	return true;
}

bool Circle::intersectsWithCircle(const Circle* other) const 
{
	return true;
}