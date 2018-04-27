#include "Mortgage.h"
#include "FileHandler.h"

Mortgage::Mortgage() {
}

Mortgage::~Mortgage() {
}

/* Get the next mortgage number from the config file */
unsigned int Mortgage::getNextMortgageNumber() {
	unsigned int mortgageNumber = FileHandler::readConfig("nextMortgageID");

	FileHandler::updateConfig("nextMortgageID", mortgageNumber + 1);

	return mortgageNumber;
}

// Functions relating to mortgage calculations (static)
/* Calculate the monthly repayments for mortgage with interest @param rate, loan amount @param principle for @param term months */
double Mortgage::calcMortgageMonthlyPayment(double rate, double principle, double term) {
	return (rate * principle * pow(1 + rate, term)) / (pow(1 + rate, term) - 1);
}

/* Calculate the total payable interest given the @param monthlyPayments, loan amount @param principle for @param term month */
double Mortgage::calcMortgageTotalInterest(double monthlyPayment, double principle, double term) {
	return (monthlyPayment * term) - principle;
}

/* Calculate the total repayment amount to the lender given the @param monthlyPayments for @param term months */
double Mortgage::calcMortgageTotalRepayment(double monthlyPayment, double term) {
	return monthlyPayment * term;
}

/* Calculate how many months a mortgage would last given interest @param rate, @param monthlyPayments and the loan amount @param principle */
double Mortgage::calcMortgageTerms(double rate, double monthlyPayment, double principle) {
	return log(-monthlyPayment / (rate * principle - monthlyPayment)) / log(1 + rate);
}