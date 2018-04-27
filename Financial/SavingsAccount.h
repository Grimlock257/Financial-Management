#pragma once

#include "Account.h"

#define COMPOUNDS_PER_YEAR 12

class SavingsAccount : public Account {
public:
	SavingsAccount(int dummy);
	SavingsAccount(unsigned int cID);
	virtual ~SavingsAccount();

	bool deposit(double amount); // Deposit specified amount
	bool withdraw(double amount); // Withdraw specified amount

	// Functions relating to savings account calculations
	static double calcSavingsAmount(double principle, double rate, double years); // Final amount after specified time
	static double calcSavingsInterest(double principle, double rate, double years); // Earned interest after specified time
	static double calcSavingsTerm(double finalValue, double principle, double rate, double periods); // How long to earn amount of money given initial investment
private:
	double interestRate;
};