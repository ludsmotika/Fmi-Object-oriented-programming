#include <iostream>
#pragma once

template <typename T>
class Queue
{
public:
	Queue();

	Queue(const Queue<T>& other);
	const Queue<T>& operator = (const Queue<T>& other);

	Queue(Queue<T>&& other);
	const Queue<T>& operator = (Queue<T>&& other);

	~Queue();

	void push(const T& obj);
	void push(T&& obj);

	void pop();
	const T& peek() const;

	bool isEmpty() const;


private:
	T* data;
	size_t count;
	size_t capacity;

	size_t getIndex;
	size_t putIndex;

	void copyFrom(const Queue<T>& other);
	void moveFrom(Queue<T>&& other);
	void free();

	void resize();
};

template <typename T>
Queue<T>::Queue()
{
	capacity = 8;
	data = new T[capacity];
	count = 0;
	getIndex = 0;
	putIndex = 0;
}

template <typename T>
Queue<T>::Queue(const Queue<T>& other)
{
	copyFrom(other);
}


template <typename T>
const Queue<T>& Queue<T>::operator = (const Queue<T>& other)
{
	if (this != &other)
	{
		free();
		copyFrom(other);
	}

	return *this;
}

template <typename T>
Queue<T>::Queue(Queue<T>&& other)
{
	moveFrom(std::move(other));
}

template <typename T>
const Queue<T>& Queue<T>::operator = (Queue<T>&& other)
{
	if (this != &other)
	{
		free();
		moveFrom(std::move(other));
	}

	return *this;
}

template <typename T>
Queue<T>::~Queue()
{
	free();
}

template <typename T>
void Queue<T>::push(const T& obj)
{
	if (count == capacity)
		resize();

	data[putIndex++] = obj;
	putIndex %= capacity;
	count++;
}

template <typename T>
void Queue<T>::push(T&& obj)
{
	if (count == capacity)
		resize();

	data[putIndex++] = std::move(obj);
	putIndex %= capacity;
	count++;

}

template <typename T>
void Queue<T>::pop()
{
	if (isEmpty())
		throw std::logic_error("Queue is empty!");

	getIndex++;
	getIndex %= capacity;

	count--;
}

template <typename T>
const T& Queue<T>::peek() const
{
	if (isEmpty())
		throw std::logic_error("Queue is empty!");

	return data[getIndex];
}

template <typename T>
bool Queue<T>::isEmpty() const
{
	return count == 0;
}

template <typename T>
void Queue<T>::copyFrom(const Queue<T>& other)
{
	data = new T[other.capacity];

	for (size_t i = 0; i < other.capacity; i++)
		data[i] = other.data[i];

	getIndex = other.getIndex;
	putIndex = other.putIndex;

	capacity = other.capacity;
	count = other.count;
}

template <typename T>
void Queue<T>::moveFrom(Queue<T>&& other)
{
	data = other.data;
	other.data = nullptr;

	putIndex = other.putIndex;
	getIndex = other.getIndex;

	count = other.count;
	capacity = other.capacity;
}

template <typename T>
void Queue<T>::free()
{
	delete[] data;
}

template <typename T>
void Queue<T>::resize()
{
	T* newData = new T[capacity * 2];

	for (size_t i = 0; i < count; i++)
	{
		newData[i] = peek();
		pop();
	}

	capacity *= 2;
	getIndex = 0;
	putIndex = count;

	delete[] data;
	data = newData;
	
}