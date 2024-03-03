#include <iostream>
#include <fstream>
#pragma warning (disable:4996)

const char FILE_NAME_FIRST[] = "result1.txt";
const char FILE_NAME_SECOND[] = "secondExercise.txt";

void writeInFile(std::ostream& stream, int sum, int difference)
{
	stream << sum << std::endl;
	stream << difference;
}

void readFromFile(std::istream& stream, int& a, int& b)
{
	int sum;
	int difference;
	stream >> sum;
	stream >> difference;

	a = (sum + difference) / 2;
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

		if (occurences > mostOccurences)
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

//04

void printFirstDifferentRow()
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
		secondInputFile.getline(secondBuffer, BUFFER_SIZE);

		if (strcmp(firstBuffer, secondBuffer))
		{
			std::cout << firstBuffer;
			return;
		}
	}

}

struct Pair
{
	unsigned int firstComponent;
	unsigned int secondComponent;
};

constexpr int MAX_PAIRS_IN_RELATION = 25;

struct Relation
{
	Pair pairs[MAX_PAIRS_IN_RELATION];
	unsigned countOfPairs = 0;
};


void addPairToRelation(Relation& relation, unsigned firstComp, unsigned secondComp)
{
	Pair pair{ firstComp,secondComp };

	if (relation.countOfPairs == MAX_PAIRS_IN_RELATION)
	{
		std::cerr << "Cannot add another pair!";
		return;
	}

	relation.pairs[relation.countOfPairs++] = pair;
}

void readRelationFromFile(Relation& rel, const char* fileName)
{
	std::ifstream file(fileName);

	if (!file.is_open())
	{
		std::cerr << "Problem occured while trying to open the file!";
		return;
	}

	while (!file.eof())
	{
		int first;
		int second;

		file >> first;
		file >> second;

		addPairToRelation(rel, first, second);
	}

	file.close();
}

void saveRelationInFile(const Relation& relation, const char* fileName)
{
	std::ofstream file(fileName);

	if (!file.is_open())
	{
		std::cerr << "Problem occured while trying to open the file!";
		return;
	}

	for (size_t i = 0; i < relation.countOfPairs; i++)
	{
		file << relation.pairs[i].firstComponent << std::endl;
		file << relation.pairs[i].secondComponent << std::endl;
	}

	file.close();
}


//06

constexpr int MAX_COUNT_CITY_NAME = 63;
constexpr int MAX_CITIES_COUNT = 20;

struct City
{
	char name[MAX_COUNT_CITY_NAME];
	unsigned int populationCount;
};


struct District
{
	City cities[MAX_CITIES_COUNT];
	int citiesCount = 0;
};


void readCity(std::ifstream& file, District& dis)
{
	char cityName[MAX_COUNT_CITY_NAME];
	int population;

	file.getline(cityName, MAX_COUNT_CITY_NAME);
	file >> population;
	file.ignore();

	City city;
	strcpy(city.name, cityName);
	city.populationCount = population;

	dis.cities[dis.citiesCount++] = city;
}

void sortCities(District& dis)
{
	for (size_t i = 0; i < dis.citiesCount; i++)
	{
		int smallestCityIndex = i;

		for (size_t j = i; j < dis.citiesCount; j++)
		{
			if (dis.cities[j].populationCount < dis.cities[smallestCityIndex].populationCount)
			{
				smallestCityIndex = j;
			}
		}

		if (smallestCityIndex != i)
		{
			std::swap(dis.cities[smallestCityIndex], dis.cities[i]);
		}
	}
}

void saveDistrictInFile(const District& dis, const char* fileName)
{
	std::ofstream file(fileName);

	if (!file.is_open())
	{
		std::cerr << "Problem occured while trying to open the file!";
		return;
	}

	for (size_t i = 0; i < dis.citiesCount; i++)
	{
		file << dis.cities[i].name << std::endl;
		file << dis.cities[i].populationCount << std::endl;
	}

	file.close();
}

void readAndSortDistrict(District& dis, const char* fileName)
{
	std::ifstream file(fileName);

	if (!file.is_open())
	{
		std::cerr << "Problem occured while trying to open the file!";
		return;
	}

	while (!file.eof())
	{
		readCity(file, dis);
	}

	file.close();

	sortCities(dis);
	saveDistrictInFile(dis, "savedDis.txt");
}

//07
//read info

constexpr int MAX_WORDS_IN_TEMPLATE = 100;
constexpr int MAX_WORD_LENGTH = 100;
constexpr int MAX_ROW_LENGTH = 200;
constexpr int MAX_ROWS_COUNT = 200;

char** readInfoForTemplate(const char* fileName, int& rowsCount)
{
	std::ifstream file(fileName);

	if (!file.is_open())
	{
		std::cerr << "Problem with opening file";
		return nullptr;
	}

	char** arr = new char* [MAX_ROWS_COUNT * 2];
	for (size_t i = 0; i < MAX_ROWS_COUNT * 2; i++)
	{
		arr[i] = new char[MAX_ROW_LENGTH];
	}

	int index = 0;

	while (!file.eof())
	{
		file.getline(arr[index++], MAX_ROW_LENGTH, ' ');
		file.getline(arr[index++], MAX_ROW_LENGTH);
	}

	rowsCount = index + 1;

	return arr;
}

int getIndexOfText(const char* text, char** arr, int rows)
{
	if (!text)
		return -1;

	if (!arr)
		return -1;

	for (size_t i = 0; i < rows; i++)
	{
		if (!arr[i])
			return -1;
	}

	for (size_t i = 0; i < rows; i += 2)
	{
		if (!strcmp(text, arr[i]))
		{
			return i + 1;
		}
	}
}

void fillTemplateWithInfo(const char* templateFileName, const char* infoFileName, const char* fileToCreate)
{
	int rowsCount = 0;
	char** info = readInfoForTemplate(infoFileName, rowsCount);

	std::ifstream fileToReadFrom(templateFileName);
	if (!fileToReadFrom.is_open())
	{
		std::cerr << "Problem occured while trying to open the file for reading!";
		return;
	}

	std::ofstream fileToWriteIn(fileToCreate);
	if (!fileToWriteIn.is_open())
	{
		std::cerr << "Problem occured while trying to open the file for writing!";
		return;
	}

	char firstBuffer[MAX_ROW_LENGTH];
	char secondBuffer[MAX_ROW_LENGTH];

	while (!fileToReadFrom.eof())
	{
		fileToReadFrom.getline(firstBuffer, MAX_ROW_LENGTH, '{');
		fileToWriteIn << firstBuffer;

		fileToReadFrom.getline(secondBuffer, MAX_ROW_LENGTH, '}');

		if (!strcmp(secondBuffer, ""))
			break;

		int indexOfRowForInfoToFillIn = getIndexOfText(secondBuffer, info, rowsCount);
		fileToWriteIn << info[indexOfRowForInfoToFillIn];
	}


	for (size_t i = 0; i < rowsCount; i++)
	{
		delete[] info[i];
	}
	
	delete[] info;

	fileToReadFrom.close();
	fileToWriteIn.close();
}

int main()
{
	fillTemplateWithInfo("template.txt", "infoForTemplate.txt", "filledTemplate.txt");

}


