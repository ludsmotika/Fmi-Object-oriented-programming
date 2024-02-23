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
	double averageGrage;
};

void initStudent(Student& student, unsigned facultatyNumber, Year year, double averageGrade)
{

	assert(facultatyNumber >= 10000 && facultatyNumber <= 99999);

	student.averageGrage = averageGrade;
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
	std::cout << student.averageGrage<< std::endl;
	std::cout << yearToString(student.year)<< std::endl;
}


int main()
{
	//01
	/*ComplexNumber a = { 0,-5 };
	ComplexNumber b = { 2,3 };
	printComplexNumber(AddComplexNumbers(a, b));
	printComplexNumber(MultiplyComplexNumbers(a, b));*/

}
