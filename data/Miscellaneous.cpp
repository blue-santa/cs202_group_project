/*
 * Miscellaneous.cpp
 * CS 201
 * December 7, 2019
 * Bryan Beus
 * Miscellaneous content definition file
 */

#include <iostream>
#include <iomanip>
#include <vector>
#include <string>

#include "Miscellaneous.hpp"

using std::vector;
using std::string;
using std::cout;
using std::cin;
using std::endl;
using std::getline;
using std::istringstream;
using std::setw;
using std::left;

// Clear the console
void clearConsole() {

    // Clear the console
    cout << "\033[2J\033[1;1H";
}

// Wait for user response
void waitForContinue() {
    cout << endl << "Press enter to continue...";
    getchar();
}

// Capture the user input
void capture_user_input(int& userInput) {

	// Assume user input is invalid until proven otherwise
	bool valid_input = false;

	// Initiate endless loop to wait for valid response
	while (!valid_input) {

		// Receive user input as a string
		string user_input_temp;
        cout << endl;
		cout << "Please indicate the desired temperature (celsius)." << endl;
        cout << " -- To stop the program, enter a value less than absolute zero (-274 or below))" << endl;

		getline(cin, user_input_temp);

		// Test if the user input is valid, and convert to an integer
		valid_input = testUserInput(user_input_temp, userInput);

		// If invalid, replay the while loop
		if (!valid_input) {
			cin.clear();
			cin.ignore(1000, '\n');
			cout << endl;
			cout << "Please try again" << endl;
		} 

		// Add formatting
		cout << endl;
	}
}

// Test whether the user's integer input is a valid response
bool testUserInput(string& user_input_temp, int& userInput) {

    // Assume user input is valid
    bool res = true;

    // Convert user input to an integer
    istringstream iss (user_input_temp);
    iss >> userInput;

    // If the string is not a valid reponse, return false
    if (iss.fail()) {
        res = false;
    }    

    // Return the result
    return res;
}

