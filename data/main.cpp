#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <iomanip>
#include <iostream>
#include <iterator>

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

void callBaselineFilenames(vector<string>& baselineFileNames) {
    string listFile = "../baseline-docs/list.txt";
    ifstream fin(listFile);

    if (!fin) {
        cout << "Error loading baseline file list" << endl;
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

void processBaselineFiles(vector< vector< pair< string, int>>>& baselineFileData, const vector<string>& baselineFileNames) {

    for (size_t i = 0; i < baselineFileNames.size(); i++) { 
        vector< pair< string, int>> data;
        string currentFilename = "../baseline-docs/" + baselineFileNames.at(i);

        processFile(currentFilename, data);
        baselineFileData.push_back(data);

    }
}

int main() {

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
     * Process output file
    ********************************************************************/
    string outputFile = "output.txt";

    ofstream fout(outputFile);

    if (!fout) {
        cout << "Error opening output file" << endl;
        exit(0);
    }

    int len = (int)(mainData.size());

    int longestLen = 0;

    for (int i = 0; i < len; i++) {
        if (longestLen < (int)mainData.at(i).first.size()) {
            longestLen = (int)mainData.at(i).first.size();
        }
    }

    for (int i = 0; i < len; i++) {
        fout << left << setw(longestLen) << mainData.at(i).first << " " << setw(5) << right << mainData.at(i).second << endl;
    }

    return 0;
}
