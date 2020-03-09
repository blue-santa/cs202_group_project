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

int main() {

    vector< pair<string, int> > data;

    string inputFilename = "doc.stops.stems.freq.1.txt";
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

        int count;
        iss >> count;

        if (!iss) {
            cout << "Error reading integer" << endl;
            exit(0);
        }

        data.push_back(make_pair(word, count)); 

        if (fin.eof()) {
            break;
        }
    }

    string outputFile = "output.txt";

    ofstream fout(outputFile);

    if (!fout) {
        cout << "Error opening output file" << endl;
        exit(0);
    }

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

    return 0;
}
