#pragma once

#include <iostream>
#include <string>
#include <vector>

#include "Account.h"
#include "Mortgage.h"
#include "UserInput.h"

class Client {
public:
	Client();
	Client(int dummy); // Dummy constructor to avoid calling the initialisation list while loading data
	Client(std::string foreName, std::string surName);
	~Client();

	void createClient();
	void print() const;
	unsigned int getID() const;
	unsigned int getNextClientID();

	std::string getForeName();
	std::string getSurName();
	bool setForeName(std::string newForename);
	bool setSurName(std::string newSurname);
private:
	const unsigned int clientID;
	std::string foreName;
	std::string surName;
};