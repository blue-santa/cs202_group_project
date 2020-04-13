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

int main() {

    /********************************************************************
     * Process Category Names and Files
    ********************************************************************/
    vector<string> categoryNames;
    vector<string> categoryFiles; 
    captureCategories(categoryNames, categoryFiles);

    /********************************************************************
     * Process Baseline Files
    ********************************************************************/
    vector<string> baselineFileNames;
    callBaselineFilenames(baselineFileNames);

    vector< vector< pair< string, int>>> baselineFileData;
    processBaselineFiles(baselineFileData, baselineFileNames); 

    /********************************************************************
     * Process Main File
    ********************************************************************/
    vector< pair<string, int> > mainData; 
    string inputFilename = "doc.stops.stems.freq.1.txt";

    processFile(inputFilename, mainData);

    /********************************************************************
     * Process Output Files for Each Baseline File
    ********************************************************************/
    processBaselineOutputFiles(baselineFileNames, baselineFileData);

    /********************************************************************
     * Process main output file
    ********************************************************************/
    string mainOutputFile = "output.txt";
    processOutputFile(mainOutputFile, mainData);

    return 0;
}
