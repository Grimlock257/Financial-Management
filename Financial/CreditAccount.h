#pragma once

#include "Account.h"

class CreditAccount : public Account {
public:
	CreditAccount(int dummy);
	CreditAccount(unsigned int cID);
	virtual ~CreditAccount();

	virtual void print() const;

	bool deposit(double amount);
	bool withdraw(double amount);

	void calcRemainingCredit();
	double getRemainingCredit() const;
private:
	double creditInterest;
	unsigned int creditLimit;
	double remainingCredit;
};