#include "Client.h"

#include "FileHandler.h"

Client::Client() : clientID(getNextClientID()) {
	createClient();
}

Client::Client(int dummy) : clientID(0) {
}

Client::Client(std::string foreName, std::string surName) : clientID(getNextClientID()), foreName(foreName), surName(surName) {
}

Client::~Client() {
}

void Client::createClient() {
	foreName = UserInput::getStringInput("Enter forename: ");
	surName = UserInput::getStringInput("Enter surname: ");

	cout << "You account has been created with the following details:" << endl;
	print();
	cout << "Please note the Client ID number as you will use this to login." << endl;

	FileHandler::write<Client>("clients", *this);
}

void Client::print() const {
	cout << "Client ID: " << clientID << endl;
	cout << "Forename: " << foreName << endl;
	cout << "Surname: " << surName << endl;
}

unsigned int Client::getID() const {
	return clientID;
}

unsigned int Client::getNextClientID() {
	unsigned int newClientID = FileHandler::readConfig("nextClientID");

	FileHandler::updateConfig("nextClientID", newClientID + 1);

	return newClientID;
}

std::string Client::getForeName() {
	return foreName;
}

std::string Client::getSurName() {
	return surName;
}

bool Client::setForeName(std::string newForename) {
	foreName = newForename;
	return FileHandler::update<Client>("clients", *this, getID());
}

bool Client::setSurName(std::string newSurname) {
	surName = newSurname;
	return FileHandler::update<Client>("clients", *this, getID());
}

//std::vector<Account> getAccounts() {
//
//}
//
//std::vector<Account> getAccounts(AccountType type) {
//
//}
//
//std::vector<Mortgage> getMortgages() {
//
//}