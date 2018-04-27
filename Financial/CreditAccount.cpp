#include "CreditAccount.h"
#include "FileHandler.h"

CreditAccount::CreditAccount(int dummy) : Account(dummy) {
}

CreditAccount::CreditAccount(unsigned int cID) : Account(AccountType::CREDIT, cID) {
	creditLimit = 100;
	remainingCredit = creditLimit;
	FileHandler::write<CreditAccount>("credit_accounts", *this);
}

CreditAccount::~CreditAccount() {
}

/* Output the account */
void CreditAccount::print() const {
	cout << left << setw(15) << "Account No: " << getID() << setw(15) << " | Balance: \x9C" << balance<< setw(24) << " | Remaining Credit: \x9C" << getRemainingCredit() << endl;
}

// Functions relating to withdrawing & depositing money
/* Deposit @param amount */
bool CreditAccount::deposit(double amount) {
	balance -= amount;
	calcRemainingCredit();
	return FileHandler::update<CreditAccount>("credit_accounts", *this, getID());
}

/* Withdraw @param amount */
bool CreditAccount::withdraw(double amount) {
	// TODO: Add check statement for credit limit
	if (balance + amount > creditLimit) {
		cout << "Your credit limit does not allow you to make this withdrawl (your balance is \x9C" << balance << ", you would end up \x9C" << abs((balance + amount) - creditLimit) << " over your limit)" << endl;
		return false;
	} else {
		balance += amount;
		calcRemainingCredit();
		return FileHandler::update<CreditAccount>("credit_accounts", *this, getID());
	}
}

void CreditAccount::calcRemainingCredit() {
	remainingCredit = creditLimit - balance;
}

double CreditAccount::getRemainingCredit() const {
	return remainingCredit;
}