#include <iostream>
#include "StringVector.h"; 
int main()
{
	StringVector vector = StringVector();
	MyString st1 = MyString("radi");
	MyString st2 = MyString("qko");
	MyString st3 = MyString("gi");
	MyString st4 = MyString("kurti");
	vector.push_back(st1);
	vector.push_back(st2);
	vector.push_back(st3);
	vector.push_back(st4);
	vector.erase(1);
	//vector.erase(2);
	//vector.clear();
	for (size_t i = 0; i < vector.size(); i++)
	{
		std::cout << vector[i] << std::endl;
	}
}