#include <iostream>

template<typename T>
class Optional 
{
private:
	T* data = nullptr;

	void copyFrom(const Optional<T>& other)
	{
		if (other.data)
		{
			data = new T(*other.data);
		}
		else 
		{
			data = nullptr;
		}
	}

	void free()
	{
		delete data;
	}
public:


	Optional()
	setValue(const T& newValue);
	setValue(T&& newValue);

	operator bool();
};