#pragma once

#include <iomanip>
#include <cmath>

#include "AccountType.h"

/* Account base class. Defines properties all bank accounts must have */
class Account {
public:
	// Constructor and deconstructor
	Account(int dummy);
	Account(AccountType accType, unsigned int cID);
	~Account();

	// Functions relating to withdrawing & depositing money
	double getBalance() const;

	virtual void print() const;

	unsigned int getClientID() const; // Return the associated clientID
	unsigned int getID() const; // Return the ID/number of the account
	AccountType getAccountType() const; // Return the type of the account
	unsigned int getNextAccountNumber(); // Get the next available account number
private:
	// General account information
	const unsigned int clientID;
	const unsigned int accountNumber;
	const AccountType accountType;
protected:
	double balance;
};