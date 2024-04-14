#include "Matrix.h"
#include <iostream>

void Matrix::setRows(int rows) 
{
	this->rows = rows;
}

void Matrix::setCols(int cols)
{
	this->cols = cols;
}

void Matrix::setData()
{
	this->data = new int*[this->rows];

	for (size_t i = 0; i < this->rows; i++)
		data[i] = new int[this->cols];
}

int Matrix::getRows() const
{
	return this->rows;
}

int Matrix::getCols() const
{
	return this->cols;
}

Matrix::Matrix() : Matrix(2, 2) {}

Matrix::Matrix(int rows, int cols) 
{
	setRows(rows);
	setCols(cols);
	setData();
}

Matrix::Matrix(const Matrix& other) 
{
	copyFrom(other);
}

const Matrix& Matrix::operator= (const Matrix& other) 
{
	if (this != &other)
	{
		free();
		copyFrom(other);
	}

	return *this;
}

Matrix::~Matrix() 
{
	free();
}

void Matrix::free() 
{
	for (size_t i = 0; i < this->rows; i++)
	{
		delete[] data[i];
	}

	delete[] data;

	this->rows = 0;
	this->cols = 0;
}

void Matrix::copyFrom(const Matrix& other) 
{
	this->rows = other.rows;
	this->cols = other.cols;
	setData();

	for (size_t i = 0; i < this->rows; i++)
	{
		for (size_t j = 0; j < this->cols; j++)
			this->data[i][j] = other.data[i][j];
	}
}

Matrix& Matrix::operator+= (const Matrix& other)
{
	if (this->getRows() != other.getRows() || this->getCols() != other.getCols())
	{
		throw ("Invalid operation");
	}

	for (size_t i = 0; i < this->getRows(); i++)
	{
		for (size_t j = 0; j < this->getCols(); j++)
		{
			*this[i][j] += other[i][j];
		}
	}
}

Matrix operator+ (const Matrix& lhs, const Matrix& rhs)
{
	Matrix result(lhs);
	result += rhs;

	return result;
}

Matrix& Matrix::operator-= (const Matrix& other)
{
	if (this->getRows() != other.getRows() || this->getCols() != other.getCols())
	{
		throw ("Invalid operation");
	}

	for (size_t i = 0; i < this->getRows(); i++)
	{
		for (size_t j = 0; j < this->getCols(); j++)
		{
			*this[i][j] -= other[i][j];
		}
	}
}

Matrix operator- (const Matrix& lhs, const Matrix& rhs) 
{
	Matrix result(lhs);
	result -= rhs;

	return result;
}

const int* Matrix::operator[] (int index) const
{
	return this->data[index];
}

int* Matrix::operator[] (int index)
{
	return this->data[index];
}

void Matrix::print() 
{
	for (size_t i = 0; i < getRows(); i++)
	{
		for (size_t j = 0; j < getCols(); j++)
		{
			std::cout << this->data[i][j];
		}
		std::cout << std::endl;
	}
}

const Matrix& Matrix::operator*= (const Matrix& other)
{
	if (this->getCols() != other.getRows())
	{
		throw ("Invalid operation");
	}

	Matrix* resultMatrix = new Matrix(this->getRows(), other.getCols());

	for (size_t i = 0; i < this->getRows(); i++)
	{
		for (size_t j = 0; j < length; j++)
		{

		}
	}
}

const Matrix& Matrix::operator*= (int scalar) 
{

}
