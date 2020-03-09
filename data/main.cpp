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

int main() {

    vector< pair<string, int> > data;

    string inputFilename = "doc.stops.stems.freq.1.txt";
    ifstream fin(inputFilename);

    if (!fin) {
        cout << "Error opening file" << endl;
        exit(0);
    }

    string alphabet = "abcdefghijklmnopqrstuvwxyz"

    string line;
    while (true) {

        getline(fin, line);

        cout << line << endl;
        
        if (line == "") {
            cout << "Error reading line" << endl;
            break;
        }

        istringstream iss(line);
        string word;

        iss >> word;

        if (!iss) {
            cout << "Error reading word" << endl;
            exit(0);
        }

        for (auto c: word) {
            cout << "skipping: " << word << endl;
            if (alphabet.find(alphabet.begin(), alphabet.end(), c) == std::string::npos) {
                continue;
            }
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
        fout << setw(longestLen) << data.at(i).first << " " << setw(5) << right << data.at(i).second << endl;
    }

    return 0;
}
