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

    string path = "../baseline-docs/";
    vector<string> categoryNames;
    vector<string> categoryFiles;
    for (const auto & entry : fs::directory_iterator(path)) {
        string curr_category_name = entry.path();
        size_t last_instance = curr_category_name.find_last_of('/');
        curr_category_name = curr_category_name.substr((int)last_instance + 1, (int)curr_category_name.size());
        cout << endl;
        cout << "Current Category Name: " << curr_category_name << endl << endl;;

        categoryNames.push_back(curr_category_name);
        const auto next_path = entry.path();
        string categoryfile;
        for (const auto& nextList : fs::directory_iterator(next_path)) {
            string nextPath = nextList.path();
            cout << nextPath << endl;
            ifstream fin_import(nextPath);

            if (!fin_import) {
                cout << "Error importing baseline doc" << endl;
            }

            while(true) {

                string line;

                getline(fin_import, line);

                categoryfile += line;

                if (fin_import.eof()) {
                    break;
                }
            } 
        }

        cout << "Compact file size: " << categoryfile.size() << endl << endl;;
        categoryFiles.push_back(categoryfile);
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
