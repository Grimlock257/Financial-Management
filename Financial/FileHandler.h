#pragma once

#include <fstream>
#include <string>

#include "Client.h"
#include "Account.h"
#include "CurrentAccount.h"
#include "SavingsAccount.h"
#include "CreditAccount.h"

using namespace std;

class FileHandler {
public:
	FileHandler();
	~FileHandler();

	/* Append new @param data to the specified file, @param fileName */
	template<typename T> static bool write(string fileName, T data);

	/* Read a specific data item (identified by @param id) from the specified file, @param fileName */
	template<typename T> static T* read(string fileName, unsigned int id);

	/* Read a specific account (identified by @param cID and @param accNumber) from the specified file, @param fileName */
	template<typename T> static T* readAccount(string fileName, unsigned int cID, unsigned int accNumber);

	/* Return an std::vector of the accounts owned by a client (identified by @param cID and @param accType) from the specified file, @param fileName */
	template<typename T> static std::vector<T> readAccounts(string fileName, unsigned int cID, AccountType accType);

	/* Update the record with the specified @param id with @param newData in the specified file, @param fileName */
	template<typename T> static bool update(string fileName, T newData, unsigned int id);

	/* Remove the specified with @param id from the specified file, @param fileName */
	template<typename T> static void removeEntry(string fileName, unsigned int id);

	// Config related file I/O functions
	/* Read the value for the specified @param searchKey from the config.ini file */
	static unsigned int readConfig(string searchKey);

	/* Update the value with the @param newValue for the specified @param updateKey in te config.ini file */
	static void updateConfig(string key, unsigned int value);
};