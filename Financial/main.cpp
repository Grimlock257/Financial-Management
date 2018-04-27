#include <iostream>
#include <iomanip>
#include <string>
#include <conio.h>

#include "Client.h"
#include "CurrentAccount.h"
#include "SavingsAccount.h"
#include "CreditAccount.h"
#include "Mortgage.h"
#include "UserInput.h"

#include "FileHandler.h"

#define CLEAR system("CLS");
#define POUND (char) 156

using namespace std;

void launchMenu();
void mainMenu();
void openAccountMenu();
template<typename T> void displayAccounts(string fileName, string typeName, AccountType accType);
template<typename T> void deposit(string fileName, string typeName);
template<typename T> void withdraw(string fileName, string typeName);
void mortgageCalculator();
void savingsCalculator();

// The currently logged in user
Client* user = nullptr;

int main() {
	// Make all numbers display with a fixed 2 decimal places
	cout << setprecision(2) << fixed;

	while (true) {
		// If the user is not logged in then display launchMenu, else display the mainMenu
		if (user == nullptr) {
			launchMenu();
		} else {
			mainMenu();
		}
	}
}

/* Display the launch menu where the user can access the calculators, login or register a client account */
void launchMenu() {
	CLEAR;

	cout << "Welcome to the Banking Application" << endl << endl;
	short int choice = UserInput::getMenuInput("What do you want to do?", "1) Existing Client Login\n2) Create a New Client Account\n3) Mortgage Calculator\n4) Savings Calculator", 4);

	CLEAR;

	// Handle input
	if (choice == 1) {
		unsigned int userID = UserInput::getIntegerInput("Please enter your client ID number:");

		user = FileHandler::read<Client>("clients", userID);
		if (user == nullptr) {
			cout << "Sorry, no client found with the ID of: " << userID << ". Please try again or register." << endl;
		}
	} else if (choice == 2) {
		Client newClient;
		cout << "Press any key to continue to the main menu..." << endl;
		_getch();
	} else if (choice == 3) {
		mortgageCalculator();
	} else if (choice == 4) {
		savingsCalculator();
	}
}

/* Display the main menu where the client can manage their accounts, as well as access the calculators */
void mainMenu() {
	CLEAR;

	cout << "Welcome to the Banking Application " << user->getForeName() << "!" << endl;
	short int choice = UserInput::getMenuInput("What do you want to do?", "1) My Current Accounts\n2) My Savings Accounts\n3) My Credit Accounts\n4) Deposit\n5) Withdraw\n6) Edit Personal Details\n7) Open New Account\n8) Mortgage Calculator\n9) Savings Calculator\n10) Logout", 10);

	CLEAR;

	// Handle input
	if (choice == 1) {
		// View Current Accounts
		displayAccounts<CurrentAccount>("current_accounts", "current", AccountType::CURRENT);
	} else if (choice == 2) {
		// View Savings Accounts
		displayAccounts<SavingsAccount>("savings_accounts", "savings", AccountType::SAVINGS);
	} else if (choice == 3) {
		// View Credit Accounts
		displayAccounts<CreditAccount>("credit_accounts", "credit", AccountType::CREDIT);
	} else if (choice == 4) {
		// Deposit
		short int choice = UserInput::getMenuInput("What type of account do you want to deposit to?", "1) Current Account\n2) Savings Account\n3) Credit Account\n4) Return to Main Menu", 4);

		CLEAR;

		if (choice == 1) {
			deposit<CurrentAccount>("current_accounts", "current");
		} else if (choice == 2) {
			deposit<SavingsAccount>("savings_accounts", "savings");
		} else if (choice == 3) {
			deposit<CreditAccount>("credit_accounts", "credit");
		} else if (choice == 4) {
			return;
		}
	} else if (choice == 5) {
		// Widthdraw
		short int choice = UserInput::getMenuInput("What type of account do you want to withdraw from?", "1) Current Account\n2) Savings Account\n3) Credit Account\n4) Return to Main Menu", 4);

		CLEAR;
		if (choice == 1) {
			withdraw<CurrentAccount>("current_accounts", "current");
		} else if (choice == 2) {
			withdraw<SavingsAccount>("savings_accounts", "savings");
		} else if (choice == 3) {
			withdraw<CreditAccount>("credit_accounts", "credit");
		} else if (choice == 4) {
			return;
		}
	} else if (choice == 6) {
		// Edit Personal Details
		cout << "Your current details:" << endl;
		user->print();
		cout << endl;

		short int choice = UserInput::getMenuInput("What information do you want to change?", "1) Forename\n2) Surname\n3) Forename & Surname\n4) Return to Main Menu", 4);

		if (choice == 1) {
			string newForename = UserInput::getStringInput("Enter your new forename:");

			if (user->setForeName(newForename)) {
				cout << "Your forename has been updated to " << newForename << endl;
			} else {
				cout << "Your forename could not be updated" << endl;
			}

			cout << "Press any key to return to the Main Menu..." << endl;
			_getch();
		} else if (choice == 2) {
			string newSurname = UserInput::getStringInput("Enter your new surname:");

			if (user->setSurName(newSurname)) {
				cout << "Your surname has been updated to " << newSurname << endl;
			} else {
				cout << "Your surname could not be updated" << endl;
			}

			cout << "Press any key to return to the Main Menu..." << endl;
			_getch();
		} else if (choice == 3) {
			string newForename = UserInput::getStringInput("Enter your new forename:");
			string newSurname = UserInput::getStringInput("Enter your new surname:");

			if (user->setForeName(newForename)) {
				cout << "Your forename has been updated to " << newForename << endl;
			} else {
				cout << "Your forename could not be updated" << endl;
			}

			if (user->setSurName(newSurname)) {
				cout << "Your surname has been updated to " << newSurname << endl;
			} else {
				cout << "Your surname could not be updated" << endl;
			}

			cout << "Press any key to return to the Main Menu..." << endl;
			_getch();
		} else if (choice == 4) {
			return;
		}

		_getch();
	} else if (choice == 7) {
		// Open New Account
		openAccountMenu();
	} else if (choice == 8) {
		// Mortgage Calculator
		mortgageCalculator();
	} else if (choice == 9) {
		// Savings Calculator
		savingsCalculator();
	} else if (choice == 10) {
		// Logout
		cout << "Thank you for using our Banking Application." << endl << "Press any key to return to the Main Menu..." << endl;
		user = nullptr;
		_getch();
	}
}

void openAccountMenu() {
	CLEAR;

	short int choice = UserInput::getMenuInput("What kind of account do you want to open?", "1) Current Account\n2) Savings Account\n3) Credit Account\n4) Return to Main Menu", 4);

	CLEAR;

	if (choice == 1) {
		// TODO: Want overdraft? Overdraft interest?
		cout << "-- Open your Current Account --" << endl;
		CurrentAccount newCurrentAccount(user->getID());
		newCurrentAccount.print();
		cout << "Press any key to continue to the main menu..." << endl;
		_getch();
	} else if (choice == 2) {
		// TODO: Types of savings account
		cout << "-- Open your Savings Account --" << endl;
		SavingsAccount newSavingsAccount(user->getID());
		newSavingsAccount.print();
		cout << "Press any key to continue to the main menu..." << endl;
		_getch();
	} else if (choice == 3) {
		// TODO: Credit Limit? Credit Interest?
		cout << "-- Open your Credit Account --" << endl;
		CreditAccount newCreditAccount(user->getID());
		newCreditAccount.print();
		cout << "Press any key to continue to the main menu..." << endl;
		_getch();
	} else if (choice == 4) {
		return;
	}
}

template<typename T>
void displayAccounts(string fileName, string typeName, AccountType accType) {
	cout << "-- Your " << typeName << " accounts --" << endl << endl;
	std::vector<T> accounts = FileHandler::readAccounts<T>(fileName, user->getID(), accType);

	if (accounts.size() > 0) {
		for (unsigned i = 0; i < accounts.size(); i++) {
			accounts[i].print();
		}
		cout << endl << "Press any key to return to the main menu..." << endl;
		_getch();
	} else {
		cout << endl << "You have no " << typeName << " accounts. You will need to open a " << typeName << " account." << endl << endl << "Press any key to return to the main menu..." << endl;
		_getch();
	}
}

template<typename T>
void deposit(string fileName, string typeName) {
	short int accNumber = UserInput::getIntegerInput("What is the account number of the account you would like to deposit to?");
	T* account(new T(0));
	account = FileHandler::readAccount<T>(fileName, user->getID(), (unsigned int)accNumber);

	if (account == nullptr) {
		cout << "There was no " << typeName << " account with account number: " << accNumber << " associated with your client account." << endl;
		cout << "Did you enter the correct account number?" << endl << "Press any key to return to the menu..." << endl;
		_getch();
	} else {
		double depositAmount = UserInput::getDoubleInput("How much do you want to deposit (\x9C)?", false);
		bool success = account->deposit(depositAmount);

		if (success) {
			cout << "\x9C" << depositAmount << " has been deposited to your " << typeName << " account (account number: " << accNumber << ")" << endl;
		} else {
			cout << "\x9C" << depositAmount << " could not be deposited to your " << typeName << " account (account number: " << accNumber << ")" << endl;
		}
		cout << "Press any key to return to the menu..." << endl;
		_getch();
	}
}

template<typename T>
void withdraw(string fileName, string typeName) {
	short int accNumber = UserInput::getIntegerInput("What is the account number of the account you would like to withdraw from?");
	T* account(new T(0));
	account = FileHandler::readAccount<T>(fileName, user->getID(), (unsigned int)accNumber);

	if (account == nullptr) {
		cout << "There was no " << typeName << " account with account number: " << accNumber << " associated with your client account." << endl;
		cout << "Did you enter the correct account number?" << endl << "Press any key to return to the menu..." << endl;
		_getch();
	} else {
		double withdrawAmount = UserInput::getDoubleInput("How much do you want to withdraw (\x9C)?", false);
		bool success = account->withdraw(withdrawAmount);

		if (success) {
			cout << "\x9C" << withdrawAmount << " has been withdrawn from your " << typeName << " account (account number: " << accNumber << ")" << endl;
		} else {
			cout << "\x9C" << withdrawAmount << " could not be withdrawn from your " << typeName << " account (account number: " << accNumber << ")" << endl;
		}
		cout << "Press any key to return to the Main Menu..." << endl;
		_getch();
	}
}

void mortgageCalculator() {
	// Add what they want to calculate (monthly payment or terms)
	short int choice = UserInput::getMenuInput("What do you want to calculate?", "1) Monthly repayments\n2) Amount of terms\n3) Return to Main Menu", 3);

	CLEAR;
	// Ask them for the appropiate information and then display the calculated information
	if (choice == 1) {
		double ratePercent = (UserInput::getDoubleInput("What is the rate (0 - 100%)?"));
		double rateDecimalPerMonth = ratePercent / 100.0 / COMPOUNDS_PER_YEAR;
		double principle = UserInput::getDoubleInput("What is the loan amount (\x9C)?");
		double term = UserInput::getDoubleInput("How many terms (in months) is the loan for?");

		CLEAR;
		cout << "Taking out a loan of \x9C" << principle << " for " << term << " months at a rate of " << ratePercent << "%:" << endl << endl;

		double monthlyPayment = Mortgage::calcMortgageMonthlyPayment(rateDecimalPerMonth, principle, term);

		cout << "Mortgage Monthly Repayment: \x9C" << monthlyPayment << endl;
		cout << "Mortgage Total Interest: \x9C" << Mortgage::calcMortgageTotalInterest(monthlyPayment, principle, term) << endl;
		cout << "Mortgage Total Repayment: \x9C" << Mortgage::calcMortgageTotalRepayment(monthlyPayment, term) << endl << endl;

		// Display the information has a tablar form for monthly repayments
		double beginningBalance = principle;
		double interestPayment = beginningBalance * rateDecimalPerMonth;
		double principlePayment = monthlyPayment - interestPayment;
		double endingBalance = beginningBalance - principlePayment;
		cout << "Month | Beginning Balance | Interest Payment | Principle Payment | Ending Balance" << endl;
		for (unsigned short int i = 0; i < term; i++) {
			cout << right << setw(5) << i + 1 << " | " << setw(17) << beginningBalance << " | " << setw(16) << interestPayment << " | " << setw(17) << principlePayment << " | " << setw(14) << endingBalance << endl;

			beginningBalance = endingBalance;
			interestPayment = beginningBalance * rateDecimalPerMonth;
			principlePayment = monthlyPayment - interestPayment;
			endingBalance = (beginningBalance - principlePayment < 0) ? 0 : beginningBalance - principlePayment;
		}
	} else if (choice == 2) {
		double ratePercent = (UserInput::getDoubleInput("What is the rate (0 - 100%)?"));
		double rateDecimalPerMonth = ratePercent / 100.0 / COMPOUNDS_PER_YEAR;
		double principle = UserInput::getDoubleInput("What is the loan amount (\x9C)?");
		double monthlyPayment = UserInput::getDoubleInput("What are the monthly payments you can make (\x9C)?");

		CLEAR;
		cout << "Taking out a loan of \x9C" << principle << " at a rate of " << ratePercent << "% with monthly payments of \x9C" << monthlyPayment << ":" << endl << endl;

		double term = Mortgage::calcMortgageTerms(rateDecimalPerMonth, monthlyPayment, principle);
		cout << "Mortgage Terms: " << Mortgage::calcMortgageTerms(rateDecimalPerMonth, monthlyPayment, principle) << endl;
		cout << "Mortgage Total Interest: \x9C" << Mortgage::calcMortgageTotalInterest(monthlyPayment, principle, term) << endl;
		cout << "Mortgage Total Repayment: \x9C" << Mortgage::calcMortgageTotalRepayment(monthlyPayment, term) << endl << endl;

		// Display the information has a tablar form for monthly repayments
		double beginningBalance = principle;
		double interestPayment = beginningBalance * rateDecimalPerMonth;
		double principlePayment = monthlyPayment - interestPayment;
		double endingBalance = beginningBalance - principlePayment;
		cout << "Month | Beginning Balance | Interest Payment | Principle Payment | Ending Balance" << endl;
		for (unsigned short int i = 0; i < term; i++) {
			cout << right << setw(5) << i + 1 << " | " << setw(17) << beginningBalance << " | " << setw(16) << interestPayment << " | " << setw(17) << principlePayment << " | " << setw(14) << endingBalance << endl;

			beginningBalance = endingBalance;
			interestPayment = beginningBalance * rateDecimalPerMonth;
			principlePayment = monthlyPayment - interestPayment;
			endingBalance = (beginningBalance - principlePayment < 0) ? 0 : beginningBalance - principlePayment;
		}
	} else if (choice == 3) {
		return;
	}

	cout << endl << "Press any key to return to Main Menu..." << endl;
	_getch();
}

void savingsCalculator() {
	// Add what they want to calculate (amount of months or balance after time)
	short int choice = UserInput::getMenuInput("What do you want to calculate?", "1) Investment value after time\n2) Time to earn x amount\n3) Return to Main Menu", 3);

	CLEAR;
	// Ask them for the appropiate information and then display the calculated information
	if (choice == 1) {
		double ratePercent = (UserInput::getDoubleInput("What is the rate (0 - 100%)?"));
		double rateDecimalPerMonth = ratePercent / 100.0 / COMPOUNDS_PER_YEAR;
		double rateDecimalPerYear = ratePercent / 100.0;
		double principle = UserInput::getDoubleInput("What is the initial investment amount (\x9C)?");
		double months = UserInput::getDoubleInput("After how many months?");

		CLEAR;
		cout << "Investing an initial amount of \x9C" << principle << " for " << months << " months at a rate of " << ratePercent << "%:" << endl << endl;

		cout << "Total value: \x9C" << SavingsAccount::calcSavingsAmount(principle, rateDecimalPerYear, months / COMPOUNDS_PER_YEAR) << endl;
		cout << "Earned Interest: \x9C" << SavingsAccount::calcSavingsInterest(principle, rateDecimalPerYear, months / COMPOUNDS_PER_YEAR) << endl << endl;

		// Display the information has a tablar form for monthly repayments
		double beginningBalance = principle;
		double monthEarnedInterest = beginningBalance * rateDecimalPerMonth;
		double endingBalance = beginningBalance + monthEarnedInterest;
		cout << "Month | Beginning Balance | Earned Interest | Ending Balance" << endl;
		for (unsigned short int i = 0; i < months; i++) {
			cout << right << setw(5) << i + 1 << " | " << setw(17) << beginningBalance << " | " << setw(15) << monthEarnedInterest << " | " << setw(14) << endingBalance << endl;

			beginningBalance = endingBalance;
			monthEarnedInterest = beginningBalance * rateDecimalPerMonth;
			endingBalance = beginningBalance + monthEarnedInterest;
		}
	} else if (choice == 2) {
		double ratePercent = (UserInput::getDoubleInput("What is the rate (0 - 100%)?"));
		double rateDecimalPerYear = ratePercent / 100.0;
		double rateDecimalPerMonth = ratePercent / 100.0 / COMPOUNDS_PER_YEAR;
		double principle = UserInput::getDoubleInput("What is the initial investment amount (\x9C)?");
		double earned = UserInput::getDoubleInput("How much do you want to earn (\x9C)?");
		double finalValue = earned + principle;
		double periods = UserInput::getIntegerInput("How many periods per year?");

		CLEAR;
		cout << "Investing an initial amount of \x9C" << principle << " at a rate of " << ratePercent << "% to earn " << finalValue << ":" << endl << endl;

		double years = SavingsAccount::calcSavingsTerm(finalValue, principle, rateDecimalPerYear, periods);
		double months = years * COMPOUNDS_PER_YEAR;

		cout << "Months to earn: " << months << endl;
		cout << "Total value: \x9C" << SavingsAccount::calcSavingsAmount(principle, rateDecimalPerYear, years) << endl;
		cout << "Earned Interest: \x9C" << SavingsAccount::calcSavingsInterest(principle, rateDecimalPerYear, years) << endl << endl;

		// Display the information has a tablar form for monthly repayments
		double beginningBalance = principle;
		double monthEarnedInterest = beginningBalance * rateDecimalPerMonth;
		double endingBalance = beginningBalance + monthEarnedInterest;
		cout << "Month | Beginning Balance | Earned Interest | Ending Balance" << endl;
		for (unsigned short int i = 0; i < months; i++) {
			cout << right << setw(5) << i + 1 << " | " << setw(17) << beginningBalance << " | " << setw(15) << monthEarnedInterest << " | " << setw(14) << endingBalance << endl;

			beginningBalance = endingBalance;
			monthEarnedInterest = beginningBalance * rateDecimalPerMonth;
			endingBalance = beginningBalance + monthEarnedInterest;
		}
	} else if (choice == 3) {
		return;
	}

	cout << endl << "Press any key to return to Main Menu..." << endl;
	_getch();
}