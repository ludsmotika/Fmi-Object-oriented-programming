#pragma once
#include "Shape.h"

class Circle : public Shape 
{
public:
	Circle(double radius,int x,int y);

	bool intersectsWith(const Shape* other) const override;

	bool intersectsWithTriangle(const Triangle* other) const;
	bool intersectsWithRect(const Rectangle* other) const;
	bool intersectsWithCircle(const Circle* other) const;

private:
	double radius;
};