#pragma once
#include "MyString.h"

class StringView 
{
public: 
	StringView(const char* begin, const char* end);
	StringView(const char* str);
	StringView(const MyString& string);

	size_t length() const;
	char operator[](size_t ind) const;

	StringView substr(size_t from, size_t length) const;
	friend std::ostream& operator<<(std::ostream&, const StringView& strView);
private:
	const char* _begin = nullptr;
	const char* _end = nullptr;
};