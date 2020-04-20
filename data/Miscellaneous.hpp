/*
 * Miscellaneous.hpp
 * CS 201
 * December 7, 2019
 * Bryan Beus
 * Declaration file for miscellaneous content
 */

#ifndef MISC_HPP
#define MISC_HPP 

#include <iostream>
#include <iomanip>
#include <vector>
#include <string>

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
void clearConsole();

// Wait for user response
void waitForContinue();

// Capture the user input
void capture_user_input(int& userInput);

// Test whether the user's integer input is a valid response
bool testUserInput(string& user_input_temp, int& userInput);

#endif
