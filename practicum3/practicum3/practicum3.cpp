#include <iostream>
#include <fstream>
#include <sstream>

constexpr int MAX_ROW_LENGTH = 100;

bool saveMatrixInFile(const char* filename, int** matrix, int rowsCount, int colsCount)
{
	std::ofstream outStream(filename);

	if (!outStream.is_open())
	{
		return false;
	}

	for (size_t i = 0; i < rowsCount; i++)
	{
		for (size_t j = 0; j < colsCount; j++)
		{
			outStream << matrix[i][j];
			if (j != colsCount - 1)
				outStream << ',';
		}

		if (i != rowsCount - 1) 
			outStream << '|';
	}

	return true;
}

void getMatrixInfo(const char* fileWithMatrix, int& rowsCount, int& colsCount)
{
	std::stringstream strstream(fileWithMatrix);

	rowsCount = 0;
	colsCount = 0;
	bool passedRow = false;
	while (!strstream.eof())
	{
		char ch;
		ch = strstream.get();

		if (ch == ',' && !passedRow)
		{
			colsCount++;
		}

		if (ch == '|')
		{
			passedRow = true;
			rowsCount++;
		}
	}

	rowsCount++;
	colsCount++;
}

int** readMatrix(const char* filename, int& rowsCount, int& colsCount)
{
	std::ifstream toRead(filename);

	if (!toRead.is_open())
	{
		return nullptr;
	}

	char wholeRow[MAX_ROW_LENGTH];
	toRead.getline(wholeRow, MAX_ROW_LENGTH);

	std::stringstream wholeRowStream(wholeRow);

	getMatrixInfo(wholeRow, rowsCount, colsCount);

	int** matrix = new int* [rowsCount];
	for (size_t i = 0; i < rowsCount; i++)
	{
		matrix[i] = new int[colsCount];
	}

	int rowIndex = 0;
	int colIndex = 0;

	while (!wholeRowStream.eof())
	{
		char ch = wholeRowStream.peek();

		if (ch == ',')
		{
			wholeRowStream.ignore();
		}

		if (ch == '|')
		{
			wholeRowStream.ignore();
			colIndex = 0;
			rowIndex++;
			continue;
		}

		wholeRowStream >> matrix[rowIndex][colIndex++];
	}

	return matrix;
}

int** multiplyMatrices(int** matrix1, int** matrix2, size_t rows1, size_t cols1, size_t rows2, size_t cols2)
{
	int** answer = new int* [rows1];

	for (size_t i = 0; i < rows1; i++)
	{
		answer[i] = new int[cols2];
	}

	for (size_t i = 0; i < rows1; i++)
	{
		for (size_t j = 0; j < cols2; j++)
		{
			int sum = 0;
			for (size_t p = 0; p < rows2; p++)
			{
				sum += matrix1[i][p] * matrix2[p][j];
			}
			answer[i][j] = sum;
		}
	}

	return answer;
}
void freeMatrix(int** matrix, int rowsCount) 
{
	for (size_t i = 0; i < rowsCount; i++)
	{
		delete[] matrix[i];
	}

	delete[] matrix;
}

int main()
{
	int firstMatrixRows;
	int firstMatrixCols;
	int secondMatrixRows;
	int secondMatrixCols;
	int** matrix1 = readMatrix("firstMatrix.txt", firstMatrixRows, firstMatrixCols);
	int** matrix2 = readMatrix("secondMatrix.txt", secondMatrixRows, secondMatrixCols);

	int answerMatrixRows = firstMatrixRows;
	int answerMatrixCols = secondMatrixCols;

	int** answerMatrix = multiplyMatrices(matrix1, matrix2, firstMatrixRows, firstMatrixCols, secondMatrixRows, secondMatrixCols);

	saveMatrixInFile("answerMatrix.txt", answerMatrix, answerMatrixRows, answerMatrixCols);


	freeMatrix(matrix1,firstMatrixRows);
	freeMatrix(matrix2,secondMatrixRows);
	freeMatrix(answerMatrix,answerMatrixRows);
}
