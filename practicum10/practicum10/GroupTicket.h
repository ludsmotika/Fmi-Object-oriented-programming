#pragma once
#include "Ticket.h"

class GroupTicket : public Ticket
{
public:
	GroupTicket(const MyString& name, double price);
};