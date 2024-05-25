#pragma once

template<typename T>
class UniquePointer 
{
public:
	UniquePointer(T* ptr);

	UniquePointer(const UniquePointer&) = delete;
	UniquePointer& operator=(const UniquePointer&) = delete;

	UniquePointer(UniquePointer&&) noexcept;
	UniquePointer& operator=(UniquePointer&&) noexcept;

	T& operator*();
	const T& operator*() const;

	~UniquePointer();
private:
	T* ptr;
};

template<typename T>
UniquePointer<T>::UniquePointer(T* ptr) :ptr(ptr) {}

template<typename T>
UniquePointer<T>::UniquePointer(UniquePointer&& other) 
{
	ptr = other;
	other = nullptr;
}

template<typename T>
UniquePointer<T>& UniquePointer<T>::operator=(UniquePointer&& other)
{
	if (this != &other)
	{
		delete ptr;
		ptr = other.ptr;
		other.ptr = nullptr;
	}

	return *this;
}

template<typename T>
T& UniquePointer<T>::operator*()
{
	return *ptr;
}

template<typename T>
const T& UniquePointer<T>::operator*() const 
{
	return *ptr;
}

template<typename T>
UniquePointer<T>::~UniquePointer() 
{
	delete ptr;
}