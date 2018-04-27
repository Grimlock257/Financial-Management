#pragma once

#include <cmath>

class Mortgage {
public:
	Mortgage();
	~Mortgage();

	/* Get the next mortgage number from the config file */
	unsigned int getNextMortgageNumber();

	// Functions relating to mortgage calculations (static)
	/* Calculate the monthly repayments for mortgage with interest @param rate, loan amount @param principle for @param term months */
	static double calcMortgageMonthlyPayment(double rate, double principle, double term);

	/* Calculate the total payable interest given the @param monthlyPayments, loan amount @param principle for @param term month */
	static double calcMortgageTotalInterest(double monthlyPayment, double principle, double term);

	/* Calculate the total repayment amount to the lender given the @param monthlyPayments for @param term months */
	static double calcMortgageTotalRepayment(double monthlyPayment, double term);

	/* Calculate how many months a mortgage would last given interest @param rate, @param monthlyPayments and the loan amount @param principle */
	static double calcMortgageTerms(double rate, double monthlyPayment, double principle);
};