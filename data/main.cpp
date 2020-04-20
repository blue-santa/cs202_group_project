/*
 * main.cpp
 * CS 202
 * Bryan Beus
 * April 12, 2020
 * Main file for the data processing aspect of the CS 202 Group Project for Sarah and Bryan
 */

#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <iomanip>
#include <iostream>
#include <iterator>
#include <filesystem>

#include "meta.hpp"
#include "Miscellaneous.hpp"

using std::cin;
using std::cout;
using std::endl;
using std::vector;
using std::string;
using std::ofstream;
using std::ifstream;
using std::istringstream;
using std::pair;
using std::make_pair;
using std::setw;
using std::right;
using std::left;

namespace fs = std::filesystem;

int main() {

    clearConsole();

    cout << endl;
    cout << string(40, '-') << endl;
    cout << "Initiating" << endl;
    cout << string(40, '-') << endl; 
    cout << endl;

    /********************************************************************
     * Capture Category Names and Files
    ********************************************************************/
    vector<string> categoryNames;
    vector<string> categoryFiles; 
    captureCategories(categoryNames, categoryFiles);

    /********************************************************************
     * Create Baseline Analysis Files
    ********************************************************************/
    createAnalysisFiles(categoryNames, categoryFiles);

    /********************************************************************
     * Perform MeTA Analysis on Baseline Analysis Files
    ********************************************************************/
    performAnalysisOnBaselineFiles(categoryNames, categoryFiles);


    /********************************************************************
     * Process Baseline Files
    ********************************************************************/
    // vector<string> baselineFileNames;
    // callBaselineFilenames(baselineFileNames);

    // vector< vector< pair< string, int>>> baselineFileData;
    // processBaselineFiles(baselineFileData, baselineFileNames); 

    /********************************************************************
     * Process Main File
    ********************************************************************/
    // vector< pair<string, int> > mainData; 
    // string inputFilename = "doc.stops.stems.freq.1.txt";

    // processFile(inputFilename, mainData);

    /********************************************************************
     * Process Output Files for Each Baseline File
    ********************************************************************/
    // processBaselineOutputFiles(baselineFileNames, baselineFileData);

    /********************************************************************
     * Process main output file
    ********************************************************************/
    // string mainOutputFile = "output.txt";
    // processOutputFile(mainOutputFile, mainData);

    /********************************************************************
     * Remove Analysis Dir
    ********************************************************************/

    removeTempAnalysisDir();
    cout << endl;
    cout << string(40, '-') << endl;
    cout << "Closing" << endl;
    cout << string(40, '-') << endl; 
    cout << endl;

    return 0;
}
