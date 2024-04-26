#include <iostream>
#include "StudentDB.h"

int main()
{
	MyString name1("gosho1");
	MyString name2("gosho2");
	MyString name3("gosho3");
	Student s1(name1, 123, 1);
	Student s2(name2, 124, 2);
	Student s3(name3,125,2);
	StudentDB db(3);
	db.add(s1);
	db.add(s2);
	db.add(s3);
	db.remove(123);
	db.display();
}