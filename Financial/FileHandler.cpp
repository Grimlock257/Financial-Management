#include "FileHandler.h"

#define BASEPATH "data/"
#define CONFIGPATH (const char) 
#define CONFIGTEMPPATH BASEPATH + (const char)"configTemp.ini"

FileHandler::FileHandler() {
}


FileHandler::~FileHandler() {
}

//template<typename datatype>
//void FileHandler::write(string fileName, datatype data) {
//	ofstream outFile;
//
//	outFile.open(fileName + ".dat", ios::binary | ios::app);
//	outFile.write((char*)&data, sizeof(data));
//	outFile.close();
//}
//
//template<typename datatype>
//void FileHandler::read(string fileName, unsigned int id) {
//	ifstream inFile;
//	datatype data;
//
//	inFile.open(fileName + ".dat", ios::binary);
//	inFile.read((char*)&data, sizeof(data));
//	inFile.close();
//}

/* Append new @param data to the specified file, @param fileName */
template<typename T>
bool FileHandler::write(string fileName, T data) {
	bool writeSuccess = false;
	ofstream file;

	file.open(BASEPATH + fileName + ".dat", ios::binary | ios::app);
	if (file.write((char*)&data, sizeof(T))) {
		writeSuccess = true;
	}
	file.close();

	return writeSuccess;
}

/* Read a specific data item (identified by @param id) from the specified file, @param fileName */
template<typename T>
T* FileHandler::read(string fileName, unsigned int id) {
	bool itemExist = false;
	ifstream file;
	T* data(new T(0));

	file.open(BASEPATH + fileName + ".dat", ios::binary);
	while (file.read((char*)data, sizeof(T))) {
		if (data->getID() == id) {
			itemExist = true;
			break;
		}
	}
	file.close();

	if (itemExist) {
		return data;
	} else {
		return nullptr;
	}
}

/* Read a specific account (identified by @param cID and @param accNumber) from the specified file, @param fileName */
template<typename T>
T* FileHandler::readAccount(string fileName, unsigned int cID, unsigned int accNumber) {
	bool itemExist = false;
	ifstream file;
	T* data(new T(0));

	file.open(BASEPATH + fileName + ".dat", ios::binary);
	while (file.read((char*)data, sizeof(T))) {
		if (data->getClientID() == cID && data->getID() == accNumber) {
			itemExist = true;
			break;
		}
	}
	file.close();

	if (itemExist) {
		return data;
	} else {
		return nullptr;
	}
}

/* Return an std::vector of the accounts owned by a client (identified by @param cID and @param accType) from the specified file, @param fileName */
template<typename T>
std::vector<T> FileHandler::readAccounts(string fileName, unsigned int cID, AccountType accType) {
	ifstream file;
	T* data(new T(0));
	std::vector<T> dataVector;

	file.open(BASEPATH + fileName + ".dat", ios::binary);
	while (file.read((char*)data, sizeof(T))) {
		if (data->getClientID() == cID && data->getAccountType() == accType) {
			dataVector.push_back(*data);
		}
	}
	file.close();

	return dataVector;
}

/* Update the record with the specified @param id with @param newData in the specified file, @param fileName */
template<typename T>
bool FileHandler::update(string fileName, T newData, unsigned int id) {
	bool itemExist = false;
	fstream file;
	T* oldData(new T(0));

	file.open(BASEPATH + fileName + ".dat", ios::in | ios::out | ios::binary);
	while (file.read((char*)oldData, sizeof(T))) {
		if (oldData->getID() == id) {
			int pos = -(signed int)sizeof(T);
			file.seekp(pos, ios::cur);
			if (file.write((char*)&newData, sizeof(T))) {
				itemExist = true;
			}
			break;
		}
	}
	file.close();

	return itemExist;
}

/* Remove the specified with @param id from the specified file, @param fileName */
template<typename T>
void FileHandler::removeEntry(string fileName, unsigned int id) {
	// TODO: Remove
}

/* Read the value for the specified @param searchKey from the config.ini file */
unsigned int FileHandler::readConfig(string searchKey) {
	ifstream file;
	string key;
	unsigned int value = 0;

	file.open("config.ini");
	while (file >> key >> value) {
		if (key == searchKey) {
			break;
		}
	}
	file.close();

	return value;
}

/* Update the value with the @param newValue for the specified @param updateKey in te config.ini file */
void FileHandler::updateConfig(string updateKey, unsigned int newValue) {
	fstream file;
	ofstream outFile("configTemp.ini");

	string tempLine;
	string key;
	unsigned int value;

	file.open("config.ini");
	while (file >> key >> value) {
		if (key == updateKey) {
			tempLine = key + " " + to_string(newValue) + "\n";
		} else {
			tempLine = key + " " + to_string(value) + "\n";
		}

		outFile << tempLine;
	}
	file.close();
	outFile.close();

	remove("config.ini");
	rename("configTemp.ini", "config.ini");
}

// Templated functions to account for the different possible template parameters
template bool FileHandler::write<Client>(string fileName, Client data);
template bool FileHandler::write<CurrentAccount>(string fileNAme, CurrentAccount data);
template bool FileHandler::write<SavingsAccount>(string fileNAme, SavingsAccount data);
template bool FileHandler::write<CreditAccount>(string fileNAme, CreditAccount data);
template Client* FileHandler::read<Client>(string fileName, unsigned int id);
template CurrentAccount* FileHandler::read<CurrentAccount>(string fileName, unsigned int id);
template SavingsAccount* FileHandler::read<SavingsAccount>(string fileName, unsigned int id);
template CreditAccount* FileHandler::read<CreditAccount>(string fileName, unsigned int id);
template CurrentAccount* FileHandler::readAccount<CurrentAccount>(string fileName, unsigned int cID, unsigned int accNumber);
template SavingsAccount* FileHandler::readAccount<SavingsAccount>(string fileName, unsigned int cID, unsigned int accNumber);
template CreditAccount* FileHandler::readAccount<CreditAccount>(string fileName, unsigned int cID, unsigned int accNumber);
template std::vector<CurrentAccount> FileHandler::readAccounts<CurrentAccount>(string fileName, unsigned int cID, AccountType accType);
template std::vector<SavingsAccount> FileHandler::readAccounts<SavingsAccount>(string fileName, unsigned int cID, AccountType accType);
template std::vector<CreditAccount> FileHandler::readAccounts<CreditAccount>(string fileName, unsigned int cID, AccountType accType);
template bool FileHandler::update<Client>(string fileName, Client newData, unsigned int id);
template bool FileHandler::update<CurrentAccount>(string fileName, CurrentAccount newData, unsigned int id);
template bool FileHandler::update<SavingsAccount>(string fileName, SavingsAccount newData, unsigned int id);
template bool FileHandler::update<CreditAccount>(string fileName, CreditAccount newData, unsigned int id);