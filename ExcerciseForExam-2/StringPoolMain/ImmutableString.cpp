#include "ImmutableString.h"

StringPool ImmutableString::pool;

ImmutableString::ImmutableString(const char* str) 
{
	pointer =pool.getAllocatedString(str);
	length = std::strlen(pointer);
}

void ImmutableString::copyFrom(const ImmutableString& other)
{
	pointer = pool.getAllocatedString(other.pointer);
	length = std::strlen(pointer);
}

void ImmutableString::moveFrom(ImmutableString&& other) 
{

}

void ImmutableString::free() 
{
	pool.releaseRecord(pointer);
	pointer = nullptr;
}

size_t ImmutableString::length() const
{
	return length;
}

char ImmutableString::operator[](size_t index) const 
{
	return pointer[index];
}

const char* ImmutableString::c_str() const
{
	return pointer;
}

std::ostream& operator<<(std::ostream& os, const ImmutableString& str) 
{
	return os << str.c_str();
}

