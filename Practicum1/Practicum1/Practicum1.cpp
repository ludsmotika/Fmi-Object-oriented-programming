#include <iostream>
#include <assert.h>
#pragma warning (disable:4996)

//01
struct ComplexNumber
{
	double realPart;
	double imaginaryPart;
};

ComplexNumber AddComplexNumbers(const ComplexNumber& first, const  ComplexNumber& second)
{
	ComplexNumber result;
	result.realPart = first.realPart + second.realPart;
	result.imaginaryPart = first.imaginaryPart + second.imaginaryPart;
	return result;
}

ComplexNumber MultiplyComplexNumbers(const ComplexNumber& first, const ComplexNumber& second)
{
	ComplexNumber result;
	result.realPart = (first.realPart * second.realPart) - (first.imaginaryPart * second.imaginaryPart);
	result.imaginaryPart = (first.realPart * second.imaginaryPart) + (first.imaginaryPart * second.realPart);
	return result;
}

void printComplexNumber(const ComplexNumber& num)
{
	std::cout << num.realPart << (num.imaginaryPart > 0 ? "+" : "") << num.imaginaryPart << "*i" << std::endl;
}


//02

constexpr unsigned TITLE_MAX_LENGTH = 50;
constexpr unsigned AUTHOR_MAX_LENGTH = 50;
constexpr unsigned MAX_BOOKS_IN_LIBRARY = 50;


enum class Genre
{
	Novel,
	Historical,
	Poetry,
	Other
};

struct Book
{
	char title[TITLE_MAX_LENGTH];
	char author[AUTHOR_MAX_LENGTH];
	bool availability;
	Genre genre;
};

struct Library
{
	Book books[MAX_BOOKS_IN_LIBRARY];
	int currentCountOfBooks;
};

void initBook(Book& book, const char* title, const char* author, bool availability, Genre genre)
{
	std::strcpy(book.author, author);
	std::strcpy(book.title, title);
	book.genre = genre;
	book.availability = availability;
}

void addBookToLibrary(Library& library, const Book& book)
{
	assert(library.currentCountOfBooks < MAX_BOOKS_IN_LIBRARY);

	library.books[library.currentCountOfBooks++] = book;
}

void changeAvailability(Book& book)
{
	book.availability = !book.availability;
}

const Book& getBookByTitle(Library& library, const char* title)
{
	for (size_t i = 0; i < library.currentCountOfBooks; i++)
	{
		if (std::strcmp(library.books[i].title, title))
		{
			assert(library.books[i].availability);
			changeAvailability(library.books[i]);
			return library.books[i];
		}
	}
}

void returnBookByTitle(Library& library, const char* title)
{
	for (size_t i = 0; i < library.currentCountOfBooks; i++)
	{
		if (std::strcmp(library.books[i].title, title))
		{
			assert(!library.books[i].availability);
			changeAvailability(library.books[i]);
		}
	}

}

const char* genreToString(Genre genre)
{
	switch (genre)
	{
	case Genre::Novel:
		return "Novel";
	case Genre::Historical:
		return "Historical";
	case Genre::Poetry:
		return "Poetry";
	case Genre::Other:
		return "Other";
	default:
		break;
	}
}

void printBook(const Book& book)
{
	std::cout << "Title: " << book.title << "   ";
	std::cout << "Author: " << book.author << "   ";
	std::cout << "Availability: " << book.availability << "   " << std::endl;
	std::cout << "Genre: " << genreToString(book.genre) << "   " << std::endl;
}

void reportForLibrary(const Library& library)
{
	for (size_t i = 0; i < library.currentCountOfBooks; i++)
	{
		printBook(library.books[i]);
	}
}


//03

enum class Year
{
	First,
	Second,
	Third,
	Fourth
};

struct Student
{
	unsigned facultatyNumber;
	Year year;
	double averageGrade;
};

void initStudent(Student& student, unsigned facultatyNumber, Year year, double averageGrade)
{

	assert(facultatyNumber >= 10000 && facultatyNumber <= 99999);

	student.averageGrade = averageGrade;
	student.year = year;
	student.facultatyNumber = facultatyNumber;
}

const char* yearToString(Year year)
{
	switch (year)
	{
	case Year::First:
		return "First";
	case Year::Second:
		return "Second";
	case Year::Third:
		return "Third";
	case Year::Fourth:
		return "Fourth";
	default:
		break;
	}
}


void printStudent(const Student& student)
{
	std::cout << student.facultatyNumber << std::endl;
	std::cout << student.averageGrade << std::endl;
	std::cout << yearToString(student.year) << std::endl;
}


//04

constexpr unsigned MAX_COUNT_STUDENTS_IN_GROUP = 3;

struct Group
{
	Student students[MAX_COUNT_STUDENTS_IN_GROUP];
	unsigned studentsCount = 0;
	double averageGrade;
};


Year getYearFromNum(unsigned year)
{
	switch (year)
	{
	case 1:
		return Year::First;
	case 2:
		return Year::Second;
	case 3:
		return Year::Third;
	case 4:
		return Year::Fourth;
	default:
		break;
	}
}

Group initGroup(int countOfStudents)
{
	Group group;

	double gradeSum = 0;

	while (group.studentsCount < MAX_COUNT_STUDENTS_IN_GROUP)
	{
		Student current;
		int yearAsANum;
		std::cin >> yearAsANum;
		int fn;
		std::cin >> fn;
		double averageGrade;
		std::cin >> averageGrade;

		Year year = getYearFromNum(yearAsANum);

		initStudent(current, fn, year, averageGrade);

		group.students[group.studentsCount++] = current;

		gradeSum += current.averageGrade;
	}

	group.averageGrade = gradeSum / group.studentsCount;

	return group;
}

int countOfStudentsWithBetterGrade(const Group& group, double minGrade)
{
	int count = 0;

	for (size_t i = 0; i < group.studentsCount; i++)
	{
		if (group.students[i].averageGrade >= minGrade)
			count++;
	}

	return count;
}

//05
bool isBoolArrayHaveOnlyTrueValues(bool* arr, int length)
{
	for (size_t i = 0; i < length; i++)
	{
		if (!arr[i])
			return false;
	}

	return true;
}

Student getBestStudentFromGroup(const Group& group, bool* alreadyChosenStudents)
{
	assert(group.studentsCount != 0);
	assert(!isBoolArrayHaveOnlyTrueValues(alreadyChosenStudents, group.studentsCount));

	int currentBestStudentIndex = 0;
	for (size_t i = 0; i < group.studentsCount; i++)
	{
		if (group.students[i].averageGrade > group.students[currentBestStudentIndex].averageGrade && !alreadyChosenStudents[i])
			currentBestStudentIndex = i;
	}

	alreadyChosenStudents[currentBestStudentIndex] = true;
	return group.students[currentBestStudentIndex];
}

Student* getBestNStudentsFromAGroupByGrade(const Group& group, int n)
{
	Student* scholarships = new Student[n];

	bool* alreadyChosenStudents = new bool[group.studentsCount] {0};

	for (size_t i = 0; i < n; i++)
	{
		scholarships[i] = getBestStudentFromGroup(group, alreadyChosenStudents);
	}

	delete[] alreadyChosenStudents;

	return scholarships;
}

void printStudentsWithScholarship(const Group& group, double minGrade)
{
	int countOfScholarships = countOfStudentsWithBetterGrade(group, minGrade);

	Student* students = getBestNStudentsFromAGroupByGrade(group, countOfScholarships);

	for (size_t i = 0; i < countOfScholarships; i++)
	{
		std::cout << students[i].facultatyNumber << "  ";
		std::cout << students[i].averageGrade << std::endl;
	}

	delete[] students;
}

//06

constexpr unsigned MAX_QUESTIONS_COUNT_FOR_TEST = 4;
constexpr unsigned MAX_SYMBOLS_COUNT_IN_QUESTION = 50;
constexpr unsigned MAX_SYMBOLS_COUNT_IN_ANSWER = 50;
constexpr unsigned COUNT_OF_POSSIBLE_ANSWERS_FOR_QUESTION = 4;

struct Answer
{
	char text[MAX_SYMBOLS_COUNT_IN_ANSWER];
	bool IsRight;
};

struct Question
{
	char questionText[MAX_SYMBOLS_COUNT_IN_QUESTION];
	Answer answers[COUNT_OF_POSSIBLE_ANSWERS_FOR_QUESTION];
	int points;
};

struct Test
{
	Question questions[MAX_QUESTIONS_COUNT_FOR_TEST];
	int questionsCount;
};

void doTest(const Test& test)
{
	int totalPoints = 0;

	for (size_t i = 0; i < test.questionsCount; i++)
	{
		std::cout << test.questions[i].questionText << std::endl;

		for (size_t j = 0; j < COUNT_OF_POSSIBLE_ANSWERS_FOR_QUESTION; j++)
			std::cout << j + 1 << ". " << test.questions[i].answers[j].text << std::endl;

		int chosenAnswerIndex;
		std::cin >> chosenAnswerIndex;

		assert(chosenAnswerIndex >= 1 && chosenAnswerIndex <= COUNT_OF_POSSIBLE_ANSWERS_FOR_QUESTION);

		if (test.questions[i].answers[chosenAnswerIndex - 1].IsRight)
		{
			std::cout << "This was the right answer!" << std::endl;
			totalPoints += test.questions[i].points;
		}
		else
		{
			std::cout << "Wroooong!" << std::endl;
		}
	}

	std::cout << "You have: " << totalPoints << "points";
}
int main()
{
	//01
	/*ComplexNumber a = { 0,-5 };
	ComplexNumber b = { 2,3 };
	printComplexNumber(AddComplexNumbers(a, b));
	printComplexNumber(MultiplyComplexNumbers(a, b));*/


	//03 04 05

	/*Group group = initGroup(3);
	printStudentsWithScholarship(group, 5.50);*/

	//06
	Answer answer1 = { "blue",0 };
	Answer answer2 = { "red",0 };
	Answer answer3 = { "yellow",1 };
	Answer answer4 = { "green",0 };
	Question firstQuestion = { "what is the color of the sun?",{answer1,answer2,answer3,answer4},3 };


	Answer answer21 = { "blue",0 };
	Answer answer22 = { "red",0 };
	Answer answer23 = { "yellow",0 };
	Answer answer24 = { "green",1 };
	Question secondQuestion = { "what is the color of the apple?",{answer21,answer22,answer23,answer24} ,5 };


	Answer answer31 = { "blue",0 };
	Answer answer32 = { "red",1 };
	Answer answer33 = { "yellow",0 };
	Answer answer34 = { "green",0 };
	Question thirdQuestion = { "what is the color of hell?",{answer31,answer32,answer33,answer34} ,10 };


	Answer answer41 = { "blue",0 };
	Answer answer42 = { "red",0 };
	Answer answer43 = { "copper",1 };
	Answer answer44 = { "green",0 };
	Question fourthQuestion = { "what is the color tates buggati?",{answer41,answer42,answer43,answer44} ,15 };

	Test test = { {firstQuestion,secondQuestion,thirdQuestion,fourthQuestion},4 };

	doTest(test);
}
