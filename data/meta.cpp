#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <iomanip>
#include <iostream>
#include <iterator>
#include <filesystem>
#include <stdlib.h>

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

namespace fs = std::filesystem;

string captureFileContent(ifstream& fin_import) { 
    bool startActivated = false;
    bool endActivated = false;

    string categoryfile = "";
    while(true) {

        string line;

        getline(fin_import, line);

        if (line.find("END OF THIS PROJECT GUTENBERG EBOOK") != string::npos || line.find("END OF THE PROJECT GUTENBERG EBOOK") != string::npos) {
            endActivated = !endActivated;
            // cout << "Deactivating: " << nextPath << endl;
        }

        if (startActivated && !endActivated) {
            categoryfile += line;
            categoryfile += "\n";
        }

        if (line.find("START OF THIS PROJECT GUTENBERG EBOOK") != string::npos || line.find("START OF THE PROJECT GUTENBERG EBOOK") != string::npos) {
            startActivated = !startActivated;
            // cout << "Activating: " << nextPath << endl;
        }


        if (fin_import.eof()) {
            break;
        } 
    } 

    if (categoryfile.length() == 0) {
        cout << "File provided is empty, invalid, or is not a Project Gutenberg file" << endl;
        exit(0);
    }

    return categoryfile;
}

void processAnyFile(const string& filename) {

    ifstream fin(filename);

    if (!fin) {
        cout << "Error importing file" << endl;
        exit(0);
    }

    string data = "";

    string line;
}

// Import the list of filenames for the baseline files and add to a vector for later usage
void callBaselineFilenames(vector<string>& baselineFileNames) {

    string path = "../baseline-docs/temp_analysis_dir/"; 
    for (const auto & entry : fs::directory_iterator(path)) {
        string curr_file = entry.path();
        
        if (curr_file.find("freq.1.txt") == string::npos) continue;

        baselineFileNames.push_back(curr_file); 
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
                // cout << "skipping " << word << endl;
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
        string currentFilename = baselineFileNames.at(i);

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
        string filename = baselineFileNames.at(i);
        vector< pair< string, int>> data = baselineFileData.at(i);

        processOutputFile(filename, data); 
    }
}

void captureCategories(vector<string>& categoryNames, vector<string>& categoryFiles) {

    string path = "../baseline-docs/categories/";

    for (const auto & entry : fs::directory_iterator(path)) {
        string curr_category_name = entry.path();
        size_t last_instance = curr_category_name.find_last_of('/');
        curr_category_name = curr_category_name.substr((int)last_instance + 1, (int)curr_category_name.size());
        // cout << endl;
        // cout << "Current Category Name: " << curr_category_name << endl << endl;;

        categoryNames.push_back(curr_category_name);
        const auto next_path = entry.path();
        string categoryfile;
        for (const auto& nextList : fs::directory_iterator(next_path)) {
            string nextPath = nextList.path();
            // cout << endl;
            // cout << string(40, '-') << endl;
            // cout << nextPath << endl;
            ifstream fin_import(nextPath);

            if (!fin_import) {
                cout << "Error importing baseline doc" << endl;
            }

            bool startActivated = false;
            bool endActivated = false;

            while(true) {

                string line;

                getline(fin_import, line);

                if (line.find("END OF THIS PROJECT GUTENBERG EBOOK") != string::npos || line.find("END OF THE PROJECT GUTENBERG EBOOK") != string::npos) {
                    endActivated = !endActivated;
                    // cout << "Deactivating: " << nextPath << endl;
                }

                if (startActivated && !endActivated) {
                    categoryfile += line;
                    categoryfile += "\n";
                }

                if (line.find("START OF THIS PROJECT GUTENBERG EBOOK") != string::npos || line.find("START OF THE PROJECT GUTENBERG EBOOK") != string::npos) {
                    startActivated = !startActivated;
                    // cout << "Activating: " << nextPath << endl;
                }


                if (fin_import.eof()) {
                    break;
                } 
            } 

            // cout << string(40, '-') << endl;
            // cout << endl;
        }

        // cout << "Compact file size: " << categoryfile.size() << endl << endl;;
        categoryFiles.push_back(categoryfile);
    }

}

// Create the files for MeTA to analyze
void createAnalysisFiles(const vector<string>& categoryNames, const vector<string>& categoryFiles) {
    string dir_path = "../baseline-docs/temp_analysis_dir";
    fs::create_directory(dir_path);
    for (size_t i = 0; i < categoryNames.size(); i++) {
        string currentFilename = "../baseline-docs/temp_analysis_dir/" + categoryNames.at(i) + ".txt";
        ofstream fout(currentFilename);

        if (!fout) {
            cout << "Error opening output file" << endl;
            exit(0);
        }

        fout << categoryFiles.at(i) << endl;
    }

}

// Execute a command on the command line and return the result
string exec(const char* cmd) {

    char buffer[128];
    std::string result = "";

#ifdef _WIN32 
    FILE* pipe = _popen(cmd, "r"); 
#elif __unix__ 
    FILE* pipe = popen(cmd, "r");
#endif

    if (!pipe) throw std::runtime_error("popen() failed!");
    try {
        while (fgets(buffer, sizeof buffer, pipe) != NULL) {
            result += buffer;
        }
    } catch (...) {
#ifdef _WIN32 
        _pclose(pipe);
#elif __unix__ 
        pclose(pipe);
#endif
        throw;
    }
#ifdef _WIN32 
    _pclose(pipe);
#elif __unix__ 
    pclose(pipe);
#endif
    return result;
}

// Perform analsysi on the baseline files using MeTA software
void performAnalysisOnBaselineFiles(const vector<string>& categoryNames, const vector<string>& categoryFiles) {

    for (size_t i = 0; i < categoryNames.size(); i++) {

        string command;
        command += "cd ../submodules/meta/build/ ";
        command += "&& ./profile config.toml ../../../baseline-docs/temp_analysis_dir/";
        command += categoryNames.at(i);

        string stopCmd = ".txt --stop";
        size_t stopLen = stopCmd.size();
        command += stopCmd;

        string res = exec(command.c_str());
        cout << res << endl;

        command = command.substr(0, command.size() - stopLen);
        string stemCmd = ".stops.txt --stem";
        size_t stemLen = stemCmd.size();
        command += stemCmd;

        res = exec(command.c_str());
        cout << res << endl;

        command = command.substr(0, command.size() - stemLen);
        string freqCmd = ".stops.stems.txt --freq-unigram";
        // size_t freqLen = freqCmd.size();
        command += freqCmd;

        res = exec(command.c_str());
        cout << res << endl;

    }

}

// Remove the temporary analysis directory
void removeTempAnalysisDir() { 
    fs::remove_all("../baseline-docs/temp_analysis_dir/");
}
