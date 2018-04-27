#include "SavingsAccount.h"
#include "FileHandler.h"

SavingsAccount::SavingsAccount(int dummy) : Account(dummy) {
}

SavingsAccount::SavingsAccount(unsigned int cID) : Account(AccountType::SAVINGS, cID) {
	FileHandler::write<SavingsAccount>("savings_accounts", *this);
}

SavingsAccount::~SavingsAccount() {
}

// Functions relating to withdrawing & depositing money
bool SavingsAccount::deposit(double amount) {
	balance += amount;
	return FileHandler::update<SavingsAccount>("savings_accounts", *this, getID());
}

bool SavingsAccount::withdraw(double amount) {
	if (balance - amount < 0) {
		cout << "Insufficent funds (your balance is \x9C" << balance << ", you are \x9C" << abs(balance - amount) << " too short)" << endl;
		return false;
	} else {
		balance -= amount;
		return FileHandler::update<SavingsAccount>("savings_accounts", *this, getID());
	}
}

// Functions relating to savings account calculations
/* Final amount after specified time */
double SavingsAccount::calcSavingsAmount(double principle, double rate, double years) {
	return principle * pow((1 + rate / COMPOUNDS_PER_YEAR), COMPOUNDS_PER_YEAR * years);
}

/* Earned interest after specified time */
double SavingsAccount::calcSavingsInterest(double principle, double rate, double years) {
	return principle * pow((1 + rate / COMPOUNDS_PER_YEAR), COMPOUNDS_PER_YEAR * years) - principle;
}

/* How long to earn amount of money given initial investment in years */
double SavingsAccount::calcSavingsTerm(double finalValue, double principle, double rate, double periods) {
	return (log(finalValue) - log(principle)) / (periods *(log(1 + (rate / periods))));
}