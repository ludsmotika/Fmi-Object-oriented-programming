#pragma once
#include "StringPool.h"
#include <iostream>

class ImmutableString
{
public:
	ImmutableString(const char* str);

	ImmutableString(const ImmutableString& other);
	ImmutableString(ImmutableString&& other);
	ImmutableString& operator =(const ImmutableString& other) = delete;
	ImmutableString& operator =(ImmutableString&& other) = delete; 

	~ImmutableString();

	size_t length() const;
	char operator[](size_t index) const;
	const char* c_str() const;
private:
	const char* pointer;
	size_t length;

	static StringPool pool;

	void copyFrom(const ImmutableString& other);
	void moveFrom(ImmutableString&& other);
	void free();
};


std::ostream& operator<<(std::ostream& os, const ImmutableString& str);

bool operator <(const ImmutableString& lhs, const ImmutableString& rhs);
bool operator >(const ImmutableString& lhs, const ImmutableString& rhs);
bool operator <=(const ImmutableString& lhs, const ImmutableString& rhs);
bool operator >=(const ImmutableString& lhs, const ImmutableString& rhs);
bool operator ==(const ImmutableString& lhs, const ImmutableString& rhs);
bool operator !=(const ImmutableString& lhs, const ImmutableString& rhs);