#include <iostream>
#include <fstream>

const char FILE_NAME_FIRST[] = "result1.txt";
const char FILE_NAME_SECOND[] = "secondExercise.txt";

void writeInFile(std::ostream& stream, int sum, int difference) 
{
	stream << sum << std::endl;
	stream << difference;
}

void readFromFile(std::istream& stream, int& a,int& b) 
{
	int sum;
	int difference;
	stream >> sum;
	stream >> difference;

	a = (sum + difference )/ 2;
	b = sum - a;
}

void firstExercise() 
{
	std::ifstream inputStream(FILE_NAME_FIRST);

	std::ofstream outputStream(FILE_NAME_FIRST);

	if (!inputStream.is_open())
	{
		std::cerr << "Cannot open file for reading!";
		return;
	}

	if (!outputStream.is_open())
	{
		std::cerr << "Cannot open file for writing!";
		return;
	}

	int first;
	int second;

	std::cin >> first;
	std::cin >> second;

	writeInFile(outputStream, first + second, first - second);

	outputStream.close();

	int a;
	int b;

	readFromFile(inputStream, a, b);

	std::cout << a << std::endl;
	std::cout << b;

	inputStream.close();
}

int mostCommonInArray(const int* arr, int size)
{
	if (!arr)
		return -1;

	int mostCommonElement = arr[0];
	int mostOccurences = 0;

	for (size_t i = 0; i < size; i++)
	{
		int currentElement = arr[i];
		int occurences = 0;

		for (size_t j = 0; j < size; j++)
		{
			if (arr[j] == currentElement)
			{
				occurences++;
			}
		}

		if (occurences> mostOccurences)
		{
			mostCommonElement = arr[i];
			mostOccurences = occurences;
		}
	}

	return mostCommonElement;
}

void secondExercise() 
{
	std::ifstream inputStream(FILE_NAME_SECOND);

	if (!inputStream.is_open())
	{
		return;
	}

	int countOfRows;
	inputStream >> countOfRows;
	
	int* arr = new int[countOfRows];

	int index = 0;
	while (index < countOfRows)
	{
		 inputStream >> arr[index++];
	}

	std::cout << mostCommonInArray(arr, countOfRows);
	delete[] arr;
}



const char FILE_NAME_THIRD[] = "Practicum2.cpp";
const int BUFFER_SIZE = 1024;

void printCodeOfFile() 
{
	std::ifstream file(FILE_NAME_THIRD);

	if (!file.is_open())
	{
		std::cout << "something went wrong";
		return;
	}

	char result[BUFFER_SIZE];

	while (file.good())
	{
		file.getline(result, BUFFER_SIZE);
		std::cout << result << std::endl;
	}

	file.close();
}


const char FILE_NAME_FOURTH1[] = "fourth1.txt";
const char FILE_NAME_FOURTH2[] = "fourth2.txt";

void fourthExercise()
{
	std::ifstream firstInputFile(FILE_NAME_FOURTH1);
	
	if (!firstInputFile.is_open())
	{
		std::cerr << "cannot open first input file";
		return;
	}

	std::ifstream secondInputFile(FILE_NAME_FOURTH2);


	if (!secondInputFile.is_open())
	{
		std::cerr << "cannot open second input file";
		return;
	}

	char firstBuffer[BUFFER_SIZE];
	char secondBuffer[BUFFER_SIZE];

	while (!firstInputFile.eof() && !secondInputFile.eof())
	{
		firstInputFile.getline(firstBuffer, BUFFER_SIZE);
		secondInputFile.getline(secondBuffer,BUFFER_SIZE);

		if (strcmp(firstBuffer, secondBuffer))
		{
			std::cout << firstBuffer;
			return;
		}
	}

}

int main()
{
	fourthExercise();
}


