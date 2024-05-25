#pragma once

template<typename T>
class Optional
{
public:
	Optional() = default;

	Optional(const Optional<T>& other);
	Optional<T>& operator = (const Optional<T>& other);

	Optional(Optional<T>&& other);
	Optional<T>& operator = (Optional<T>&& other);

	~Optional();

	const T& operator*() const
	{
		if (!data)
			throw "sfsd";
		return *data;
	}

	T& operator*()
	{
		if (!data)
			throw "sfsd";
		return *data;
	}

	void setValue(const T& value)
	{
		delete data;
		data = new T(value); //copy constr!
	}

	void setValue(T&& value)
	{
		delete data;
		data = new T(std::move(value)); //move constr!
	}
	void reset()
	{
		delete data;
		data = nullptr;
	}
	operator bool() const
	{
		return data != nullptr;
	}

private:
	T* data = nullptr;

	void moveFrom(Optional<T>&& other);
	void copyFrom(const Optional<T>& other);
	void free();
};


template<typename T>
void Optional<T>::moveFrom(Optional<T>&& other) 
{
	data = new T(std::move(other.data));
}

template<typename T>
void Optional<T>::copyFrom(const Optional<T>& other) 
{
	data = new T(other.data);
}

template<typename T>
void Optional<T>::free() 
{
	delete data;
}

template<typename T>
Optional<T>::Optional(const Optional<T>& other)
{
	copyFrom(other);
}

template<typename T>
Optional<T>& Optional<T>::operator = (const Optional<T>& other) 
{
	if (this != &other)
	{
		free();
		copyFrom(other);
	}

	return *this;
}

template<typename T>
Optional<T>::Optional(Optional<T>&& other) 
{
	moveFrom(std::move(other));
}

template<typename T>
Optional<T>& Optional<T>::operator = (Optional<T>&& other) 
{
	if (this != &other)
	{
		free();
		moveFrom(std::move(other));
	}

	return *this;
}

template<typename T>
Optional<T>::~Optional() 
{
	free();
}