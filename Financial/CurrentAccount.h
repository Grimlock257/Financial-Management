#pragma once

#include "Account.h"

class CurrentAccount : public Account {
public:
	CurrentAccount(int dummy);
	CurrentAccount(unsigned int cID);
	virtual ~CurrentAccount();

	bool deposit(double amount);
	bool withdraw(double amount);

	// Functions relating to overdraft calculations on a current account
	bool hasOverdraftFacility();
	double calcOverdraftRemainder();
	double calcOverdraftInterest();
private:
	bool hasOverdraft;
	double overdraftLimit;
	double overdraftInterestRate;
};