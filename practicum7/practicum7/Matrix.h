#pragma once

class Matrix
{
private:
	int** data;
	int rows;
	int cols;

	void setRows(int rows);
	void setCols(int cols);
	void setData();

	void free();
	void copyFrom(const Matrix& other);

public:

	int getRows() const;
	int getCols() const;

	Matrix() : Matrix(2, 2) {}
    Matrix(int rows,int cols);
	Matrix(const Matrix& other);
	const Matrix& operator= (const Matrix& other);
	~Matrix();

	Matrix& operator+= (const Matrix& other);
	Matrix& operator-= (const Matrix& other);

	const Matrix& operator*= (const Matrix& other);
	const Matrix& operator*= (int scalar);

	const Matrix& operator== (const Matrix& other);
	const Matrix& operator!= (const Matrix& other);

	const int* operator[] (int index) const;
	int* operator[] (int index);

	void print();
};

Matrix operator+ (const Matrix& lhs, const Matrix& rhs);
Matrix operator- (const Matrix& lhs, const Matrix& rhs);
Matrix operator* (const Matrix& lhs, const Matrix& rhs);
Matrix operator* (const Matrix& lhs, int scalar);
