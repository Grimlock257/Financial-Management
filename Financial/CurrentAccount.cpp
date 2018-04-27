#include "CurrentAccount.h"
#include "FileHandler.h"

CurrentAccount::CurrentAccount(int dummy) : Account(dummy) {
}

CurrentAccount::CurrentAccount(unsigned int cID) : Account(AccountType::CURRENT, cID) {
	hasOverdraft = true; // TODO: Parameter (another constructor)
	FileHandler::write<CurrentAccount>("current_accounts", *this);
}

CurrentAccount::~CurrentAccount() {
}

// Functions relating to withdrawing & depositing money
bool CurrentAccount::deposit(double amount) {
	balance += amount;
	return FileHandler::update<CurrentAccount>("current_accounts", *this, getID());
}

bool CurrentAccount::withdraw(double amount) {
	// TODO: Add check statement for balance, incorporate checking for overdraft
	if (balance - amount < 0) {
		// TODO: CurrentAccount::withdraw() - Implement exhausted overdraft limit
		cout << "Insufficent funds (your balance is \x9C" << balance << ", you are \x9C" << abs(balance - amount) << " too short" << (hasOverdraftFacility() ? "" : " and do not have an overdraft facility") << ")" << endl;
		return false;
	} else {
		balance -= amount;
		return FileHandler::update<CurrentAccount>("current_accounts", *this, getID());
	}
}

// Functions relating to overdraft calculations on a current account
bool CurrentAccount::hasOverdraftFacility() {
	return hasOverdraft;
}

double CurrentAccount::calcOverdraftRemainder() {
	// TODO: calcOverdraftRemainder
	return 10;
}

double CurrentAccount::calcOverdraftInterest() {
	// TODO: calcOverdraftInterest
	return 10;
}