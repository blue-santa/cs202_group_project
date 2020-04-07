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

// Import the list of filenames for the baseline files and add to a vector for later usage
void callBaselineFilenames(vector<string>& baselineFileNames) {
    string listFile = "../baseline-docs/list.txt";
    ifstream fin(listFile);

    if (!fin) {
        cout << "Error loading baseline file list" << endl;
        exit(0);
    }

    while (true) {

        string line; 
        getline(fin, line); 

        if (line == "") {
            break;
        }

        baselineFileNames.push_back(line); 

        if (fin.eof()) {
            break;
        }
    }
}

// Import the data from the provided inputFilename file and process it into a prettier format that only contains recognizable words
void processFile(const string& inputFilename, vector< pair<string, int>>& data) {

    ifstream fin(inputFilename);

    if (!fin) {
        cout << "Error opening file" << endl;
        exit(0);
    }

    string alphabet = "abcdefghijklmnopqrstuvwxyz"; 
    while (true) {
        string line;

        getline(fin, line);
        
        if (line == "") {
            break;
        }

        istringstream iss(line);
        string word;

        iss >> word;

        if (!iss) {
            cout << "Error reading word" << endl;
            exit(0);
        }

        // Make sure the word under observation is a readable and alphabetical word
        bool found = false;

        for (auto c: word) {
            if (alphabet.find(c) == std::string::npos) {
                cout << "skipping " << word << endl;
                found = true;
            }
        }

        if (found) {
            continue;
        }

        int intCount;
        iss >> intCount;

        if (!iss) {
            cout << "Error reading integer" << endl;
            exit(0);
        }

        data.push_back(make_pair(word, intCount)); 

        if (fin.eof()) {
            break;
        }
    }

}

// Process the baseline files 
void processBaselineFiles(vector< vector< pair< string, int>>>& baselineFileData, const vector<string>& baselineFileNames) {

    for (size_t i = 0; i < baselineFileNames.size(); i++) { 
        vector< pair< string, int>> data;
        string currentFilename = "../baseline-docs/" + baselineFileNames.at(i);

        processFile(currentFilename, data);
        baselineFileData.push_back(data);

    }
}

// Process the provided file by writing its data into an output file
void processOutputFile(const string& filename, const vector< pair< string, int>>& data) {

    ofstream fout(filename);

    if (!fout) {
        cout << "Error opening output file" << endl;
        exit(0);
    }

    // Ensure the longest length of any word is represented in the column format for each word
    int len = (int)(data.size());

    int longestLen = 0;

    for (int i = 0; i < len; i++) {
        if (longestLen < (int)data.at(i).first.size()) {
            longestLen = (int)data.at(i).first.size();
        }
    }

    for (int i = 0; i < len; i++) {
        fout << left << setw(longestLen) << data.at(i).first << " " << setw(5) << right << data.at(i).second << endl;
    }

}

// Process each baseline file
void processBaselineOutputFiles(const vector<string>& baselineFileNames, const vector< vector< pair< string, int>>>& baselineFileData) {
    for (size_t i = 0; i < baselineFileNames.size(); i++) {
        string filename = "./output/" + baselineFileNames.at(i);
        vector< pair< string, int>> data = baselineFileData.at(i);

        processOutputFile(filename, data); 
    }
}

int main() {

    string path = "../baseline-docs/";
    for (const auto & entry : fs::directory_iterator(path)) {
        cout << entry.path() << endl;
        const auto next_path = entry.path();
        for (const auto& nextList : fs::directory_iterator(next_path)) {
            cout << nextList.path() << endl;
        }
    }

    vector<string> baselineFileNames;
    callBaselineFilenames(baselineFileNames);

    /********************************************************************
     * Process Baseline Files
    ********************************************************************/
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
