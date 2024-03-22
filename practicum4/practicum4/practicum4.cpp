#include <iostream>
#include <fstream>
#pragma warning (disable:4996)

//01

namespace GlobalConstants
{
	constexpr int TASK_MAX_LENGTH = 200;
	constexpr int PASSWORD_MAX_LENGTH = 200;
}

struct User
{
	char name[25]{};
};

struct Message
{
	User from;
	char* text;
};

void writeToFile(const char* filename, const Message* messages, int messagesCount)
{
	std::ofstream ofs(filename);

	for (size_t i = 0; i < messagesCount; i++)
	{
		ofs.write((const char*)messages[i].from.name, 25);

		int currentMessageLength = std::strlen(messages[i].text);
		ofs.write((const char*)&currentMessageLength, sizeof(int));

		ofs.write((const char*)messages[i].text, currentMessageLength);
	}
}

void printChat(const char* filename)
{
	std::ifstream ifs(filename, std::ios::binary);

	if (!ifs.is_open())
	{
		std::cerr << "Error while trying to open the file!";
		return;
	}

	while (!ifs.fail())
	{
		char currentUsername[25];
		ifs.read(currentUsername, 25);

		int lengthOfMessage = 0;
		ifs.read((char*)&lengthOfMessage, sizeof(int));

		char* currentMessage = new char[lengthOfMessage + 1];
		currentMessage[lengthOfMessage] = '\0';
		ifs.read(currentMessage, lengthOfMessage);

		std::cout << currentUsername << ": " << currentMessage << std::endl;

	}


}

//02

class Secret
{
private:
	char task[GlobalConstants::TASK_MAX_LENGTH + 1];
	char password[GlobalConstants::PASSWORD_MAX_LENGTH + 1];
	mutable int countOfLoginFails = 0;
public:
	Secret();
	Secret(const char* pass, const char* task);
	const char* getTask(const char* pwd) const;
	void setPassword(const char* newPassword, const char* oldPassword);
	void setTask(const char* newTask, const char* passwd);
	int getLoginFails() const;
	void incrementCountOfLoginFails() const;
};

Secret::Secret()
{
	this->password[GlobalConstants::PASSWORD_MAX_LENGTH] = '\0';
	this->task[GlobalConstants::TASK_MAX_LENGTH] = '\0';
}

Secret::Secret(const char* pass, const char* task) : Secret()
{
	std::strcpy(this->password, pass);
	std::strcpy(this->task, task);
}

void Secret::incrementCountOfLoginFails() const
{
	this->countOfLoginFails++;
}

const char* Secret::getTask(const char* pwd) const
{
	if (!std::strcmp(password, pwd))
	{
		return this->task;
	}

	this->incrementCountOfLoginFails();
	return "";
}

void Secret::setPassword(const char* newPassword, const char* oldPassword)
{
	if (std::strcmp(oldPassword, this->password))
		this->incrementCountOfLoginFails();

	std::strcpy(this->password, newPassword);
}

void Secret::setTask(const char* newTask, const char* passwd)
{
	if (std::strcmp(passwd, this->password))
		this->incrementCountOfLoginFails();

	std::strcpy(this->task, newTask);
}

int Secret::getLoginFails() const
{
	return this->countOfLoginFails;
}

//03



int main()
{
	User user1;
	std::strcpy(user1.name, "Daniel");
	User user2;
	std::strcpy(user2.name, "Radin");

	Message messages[4] = { {user1,(char*)"Sho staa radka"},{user2,(char*)"pa te nisho"},{user2,(char*)"Are na lostove"},{user1,(char*)"ako ae"} };

	//writeToFile("savedMessages.txt", messages, 4);
	printChat("savedMessages.txt");
}

