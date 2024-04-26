#pragma once
#include "Ticket.h"

class StudentTicket : public Ticket 
{
public:
	StudentTicket(const MyString& name, double price);
};