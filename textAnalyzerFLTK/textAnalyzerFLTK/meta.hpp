/*
 * meta.hpp
 * Bryan Beus
 * April 7, 2020
 * CS 202
 * Header file for MeTA class functionality
 */

#ifndef __META_HPP__
#define __META_HPP__

#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <iomanip>
#include <iostream>
#include <iterator>
#include <filesystem>

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

// Execute command on commandline
string exec(const char* cmd);

// Capture file content
string captureFileContent(ifstream& fin_import);

// Process any provided file
void processAnyFile(const string& filename);

// Import the list of filenames for the baseline files and add to a vector for later usage
void callBaselineFilenames(vector<string>& baselineFileNames);

// Import the data from the provided inputFilename file and process it into a prettier format that only contains recognizable words
void processFile(const string& inputFilename, vector< pair<string, int>>& data);

// Process the baseline files
void processBaselineFiles(vector< vector< pair< string, int>>>& baselineFileData, const vector<string>& baselineFileNames);

// Process the provided file by writing its data into an output file
void processOutputFile(const string& filename, const vector< pair< string, int>>& data);

// Process each baseline file
void processBaselineOutputFiles(const vector<string>& baselineFileNames, const vector< vector< pair< string, int>>>& baselineFileData);

// Capture the category names and files for future processing
void captureCategories(vector<string>& categoryNames, vector<string>& categoryFiles);

// Perform analsysi on the baseline files using MeTA software
void performAnalysisOnBaselineFiles(const vector<string>& categoryNames, const vector<string>& categoryFiles);
#endif

// Create the files for MeTA to analyze
void createAnalysisFiles(const vector<string>& categoryNames, const vector<string>& categoryFiles);

// Remove the temporary analysis directory
void removeTempAnalysisDir();
