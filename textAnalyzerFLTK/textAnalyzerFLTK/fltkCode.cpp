//
//  fltkCode.cpp
//  textAnalyzerFLTK
//
//  Created by Sarah Carter on 3/3/20.
//  Copyright © 2020 Sarah Carter. All rights reserved.
//

#include <FL/Fl_Button.H>
#include <FL/Fl_Native_File_Chooser.H>
#include <FL/Fl_Input.H>
#include <FL/Fl_Output.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_Text_Display.H>
#include <FL/Fl_Text_Buffer.H>
#include <fstream>
#include <iostream>
#include <sstream>

#include "fltkCode.hpp"
#include "meta.hpp"

//Fl_Native_File_Chooser* fileFind = nullptr;
Fl_Box* progTitle = nullptr;
Fl_Box* instructions = nullptr;
Fl_Box* description = nullptr;
Fl_Box* resultDisp = nullptr;
Fl_Input* fileChoice = nullptr;
Fl_Input* fileTitle = nullptr;
Fl_Button* browser = nullptr;
Fl_Button* analyzeBase = nullptr;
Fl_Button* analyzeChoice = nullptr;
Fl_Button* display = nullptr;
Fl_Button* close = nullptr;
Fl_Button* quit = nullptr;
Fl_Output* report = nullptr;
Fl_Text_Display* reportDisp = nullptr;
Fl_Text_Buffer* buff = nullptr;

std::string userFile;
std::string processedFile;
std::string output;

void browserClicked(Fl_Widget*, void* data){
    Fl_Native_File_Chooser fileFind;
    fileFind.title("Select File to Analyze");
    fileFind.type(Fl_Native_File_Chooser::BROWSE_FILE);
    switch( fileFind.show() ){
        case -1: fprintf(stderr, "ERROR: %s\n", fileFind.errmsg()); break;    // ERROR
        case  1: fprintf(stderr, "*** CANCEL\n"); break;        // CANCEL
        default:                                 // PICKED FILE
            fileChoice->value(fileFind.filename());
          break;
    }
    std::string choice = fileChoice->value();
    std::istringstream is(choice);
    is >> userFile;
}

std::string fileNameNoExt(std::string& file){
    auto pd = file.find_first_of(".");
    std::string ext = file.substr(pd);
    std::string::size_type i = file.find(ext);
    if(i != std::string::npos)
        file.erase(i, ext.length());
    auto slsh = file.find_last_of("/");
    file = file.substr(slsh+1);
    for(int i = 0; i < file.size(); i++){
        if(file[i] == '-')
            file[i] = ' ';
    }
    file[0] = toupper(file[0]);
    for(int i = 0; i < file.size(); i++){
        if(file[i]==' ' && file[i+1]!='\0')
            file[i+1] = toupper(file[i+1]);
    }
    return file;
}



void textAnalysisBase_CB(Fl_Widget*, void* data){
    std::vector<string> categoryNames;
    std::vector<string> categoryFiles;
    /********************************************************************
     * Capture Category Names and Files
    ********************************************************************/
    captureCategories(categoryNames, categoryFiles);

    /********************************************************************
     * Create Baseline Analysis Files
    ********************************************************************/
    createAnalysisFiles(categoryNames, categoryFiles);

    /********************************************************************
     * Perform MeTA Analysis on Baseline Analysis Files
    ********************************************************************/
    performAnalysisOnBaselineFiles(categoryNames, categoryFiles);
}

void textDisplay_cb(Fl_Widget*, void* data){
    Fl_Window* win = (Fl_Window*)data;
    win->show();
    output.clear();
    std::string line;
    std::ifstream fin(userFile);
    fileTitle->value(fileNameNoExt(userFile).c_str());
    while(std::getline(fin, line)){
        if(!fin){
            if(fin.eof())
                std::cout << "End of file\n";
            else{
                std::cout << "Error opening file\n";
                break;
            }
        }
        output += (line + "\n");
    }
    buff = new Fl_Text_Buffer();
    reportDisp -> buffer(buff);
    buff->text(output.c_str());
}

//Close window when "Exit" button is clicked
void OnExitClicked_cb(Fl_Widget* w, void* data){
    if(!data) return;
    Fl_Window* win = (Fl_Window*)data;
    win->hide();
}

Fl_Window* PopupWindow(){
    Fl_Window* pWin = new Fl_Window(800, 600,"");
    pWin -> begin();
    
    resultDisp = new Fl_Box(250,20,300,40, "Analysis Results");
    resultDisp->box(FL_UP_BOX);
    resultDisp->labelsize(20);
    
    fileTitle = new Fl_Input(225, 80, 350, 40);
    fileTitle->box(FL_UP_BOX);
    fileTitle->textsize(16);
    
    reportDisp = new Fl_Text_Display(25, 160, 750, 300);
    close = new Fl_Button(350, 500, 100, 20, "Close");
    
    close->callback(OnExitClicked_cb, (void*) pWin);

    pWin -> end();
    return pWin;
}

Fl_Window* CreateWindow(){
    Fl_Window* win = new Fl_Window(800, 300, "Text Analyzer");
    win->begin();
    
//    progTitle = new Fl_Box(275,10,250, 50, "Text Analyzer");
//    progTitle->box(FL_UP_BOX);
//    progTitle->labelsize(24);
    
    description = new Fl_Box(100,10,600,50, "This program will take a text that you select"
                                           " and analyze the content for frequency \nof "
                             "specific words to categorize the text for you.");
    description->labelsize(14);
    
    instructions = new Fl_Box(175, 65, 500, 40, "Click the \"Browse\" button to search "
                              "for the file you wish to analyze.");
    
    fileChoice = new Fl_Input(175,115,500,25);
    browser = new Fl_Button(50, 117, 100, 20, "Browse");
    analyzeBase = new Fl_Button(250, 145, 160, 20, "Analyze Base Files");
    analyzeChoice = new Fl_Button(415, 145, 160, 20, "Analyze Chosen File");
    
    display = new Fl_Button(340, 170, 140, 30, "Display Results");
    display->color(FL_DARK_CYAN);
    display->labelsize(16);
    display->labelfont(FL_BOLD);
    
    quit = new Fl_Button(350, 265, 120, 30, "Exit");
    quit->color(FL_RED);
    quit->labelsize(20);
    quit->labelfont(FL_BOLD);
    
    quit -> callback(OnExitClicked_cb, (void*) win);

    browser->callback(browserClicked);
    analyzeBase->callback(textAnalysisBase_CB);
    display->callback(textDisplay_cb, (void*)PopupWindow());

    

    win->end();
    return win;
}
