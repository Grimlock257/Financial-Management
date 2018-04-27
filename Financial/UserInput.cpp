#include "UserInput.h"

using namespace std;

namespace UserInput {
	/* Get a menu input from the user */
	short int getMenuInput(string question, string options, short int amountOptions) {
		cout << question << endl << options << endl;

		string userInput;
		short int choice;

		while (true) {
			cout << "> ";
			getline(cin, userInput);

			stringstream ss(userInput);
			if (ss >> choice && (choice > 0 && choice <= amountOptions)) {
				break;
			}

			cout << "Invalid choice, please enter a valid option (1 - " << amountOptions << ")" << endl;
		}

		return choice;
	}

	/* Get an integer input from the user */
	short int getIntegerInput(string question) {
		cout << question << endl;

		string userInput;
		short int choice;

		while (true) {
			cout << "> ";
			getline(cin, userInput);

			stringstream ss(userInput);
			if (ss >> choice) {
				break;
			}

			cout << "Invalid choice, please enter a valid option" << endl;
		}

		return choice;
	}

	/* Get a double input from the user (@param allowNegative default is true) */
	double getDoubleInput(string question, bool allowNegative) {
		cout << question << endl;

		string userInput;
		double choice;

		while (true) {
			cout << "> ";
			getline(cin, userInput);

			stringstream ss(userInput);
			if (allowNegative) {
				if (ss >> choice) {
					break;
				}
			} else {
				if (ss >> choice && choice >= 0) {
					break;
				}
			}

			cout << "Invalid choice, please enter a valid option" << endl;
		}

		return choice;
	}

	/* Get a string input from the user */
	string getStringInput(string question) {
		cout << question << endl << "> ";

		string userInput;
		getline(cin, userInput);

		return userInput;
	}
}