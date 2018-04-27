#include "Account.h"
#include "FileHandler.h"

// Constructor and deconstructor
Account::Account(int dummy) : accountNumber(0), accountType(AccountType::CURRENT), clientID(0) {
}

Account::Account(AccountType accType, unsigned int cID) : accountNumber(getNextAccountNumber()), accountType(accType), clientID(cID) {
}

Account::~Account() {
}

double Account::getBalance() const {
	return balance;
}

/* Output the account */
void Account::print() const {
	cout << left << setw(15) << "Account No: " << accountNumber << setw(15) << " | Balance: \x9C" << balance << endl;
}

/* Return the associated clientID */
unsigned int Account::getClientID() const {
	return clientID;
}

/* Return the ID/number of the account */
unsigned int Account::getID() const {
	return accountNumber;
}

/* Return the type of the account */
AccountType Account::getAccountType() const {
	return accountType;
}

/* Get the next available account number */
unsigned int Account::getNextAccountNumber() {
	unsigned int accountNumber = FileHandler::readConfig("nextAccountID");

	FileHandler::updateConfig("nextAccountID", accountNumber + 1);

	return accountNumber;
}