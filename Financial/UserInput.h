#pragma once

#include <iostream>
#include <string>
#include <sstream>

/* Functions regarding user input */
namespace UserInput {
	/* Get a menu input from the user */
	short int getMenuInput(std::string question, std::string options, short int amountOptions);

	/* Get an integer input from the user */
	short int getIntegerInput(std::string question);

	/* Get a double input from the user (@param allowNegative default is true) */
	double getDoubleInput(std::string question, bool allowNegative=true);

	/* Get a string input from the user */
	std::string getStringInput(std::string question);
}