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
#include <analyzer.h>

#include <analyzers/all.h>
#include <analyzers/token_stream.h>
#include <document.h>
#include <create_config.h>
#include <bandit/bandit.h>
#include <io/filesystem.h>
#include <util/shim.h>

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

using namespace meta;
using namespace bandit;

namespace {

std::unique_ptr<analyzers::token_stream> make_filter() {
    using namespace analyzers;
    auto line_cfg = tests::create_config("line");
    return analyzers::default_filter_chain(*line_cfg);
}

template <class Analyzer>
void check_analyzer_expected(Analyzer& ana, corpus::document doc,
                             uint64_t num_unique, uint64_t length) {
    auto counts = ana.template analyze<uint64_t>(doc);
    // AssertThat(counts.size(), Equals(num_unique));

    auto total = std::accumulate(
        counts.begin(), counts.end(), uint64_t{0},
        [](uint64_t acc,
           const hashing::kv_pair<std::string, uint64_t>& count) {
            return acc + count.value();
        });

    // AssertThat(total, Equals(length));
    // AssertThat(doc.id(), Equals(47ul));
}
}

int main() {

    clearConsole();
    corpus::document doc{doc_id{47}};
    std::string content = "one one two two two three four one five";
    doc.content(content);
    // corpus::document doc(doc_id{47});

    // my_doc.document();

    // my_doc.content("content", "utf-8");
    // cout << my_doc.id() << endl;

    return 0;

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
    vector<string> baselineFileNames;
    callBaselineFilenames(baselineFileNames);

    vector< vector< pair< string, int>>> baselineFileData;
    processBaselineFiles(baselineFileData, baselineFileNames); 

    /********************************************************************
     * Process Main File
    ********************************************************************/
    // vector< pair<string, int> > mainData; 
    // string inputFilename = "doc.stops.stems.freq.1.txt";

    // processFile(inputFilename, mainData);

    /********************************************************************
     * Process Output Files for Each Baseline File
    ********************************************************************/
    processBaselineOutputFiles(baselineFileNames, baselineFileData);

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
