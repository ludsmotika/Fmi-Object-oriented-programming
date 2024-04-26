#pragma once
#include "MyString.h"

class Ticket
{
private:
	MyString name;
	double price = 0;
public:
	double getPrice() const;
	const MyString& getEventName() const;
	Ticket(const MyString& name, double price);
};