#include "Ticket.h"

Ticket::Ticket(const MyString& name, double price)
{
	this->name = name;
	this->price = price;
}

double Ticket::getPrice() const
{
	return this->price;
}

const MyString& Ticket::getEventName() const
{
	return this->name;
}