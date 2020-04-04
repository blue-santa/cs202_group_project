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

//Fl_Native_File_Chooser* fileFind = nullptr;
Fl_Box* progTitle = nullptr;
Fl_Box* instructions = nullptr;
Fl_Box* description = nullptr;
Fl_Input* fileChoice = nullptr;
Fl_Button* browser = nullptr;
Fl_Button* analyze = nullptr;
Fl_Button* quit = nullptr;
Fl_Output* report = nullptr;
Fl_Text_Display* reportDisp = nullptr;
Fl_Text_Buffer* buff = nullptr;

std::string userFile;
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

void textAnalysis_CB(Fl_Widget*, void* data){
    std::string line;
    std::ifstream fin(userFile);
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

Fl_Window* CreateWindow(){
    Fl_Window* win = new Fl_Window(800, 600,"");
    win -> begin();
    
    fileChoice = new Fl_Input(175,155,500,40);
    browser = new Fl_Button(50, 165, 100, 20, "Browse");
    analyze = new Fl_Button(50, 190, 100, 20, "Analyze");
    
    browser->callback(browserClicked);
    analyze->callback(textAnalysis_CB);
        
    progTitle = new Fl_Box(275,10,250, 50, "Text Analyzer");
    progTitle->box(FL_UP_BOX);
    progTitle->labelsize(24);
    
    description = new Fl_Box(100,70,600,50, "This program will take a text that you select"
                                           " and analyze the content for frequency \nof "
                             "specific words to categorize the text for you.");
    description->labelsize(14);
    description->box(FL_UP_BOX);
    
//    instructions = new Fl_Box(175, 155, 500, 40, "Click the \"Browse\" button to search "
//                              "for the file you wish to analyze.");
//    instructions->box(FL_UP_BOX);
    

    reportDisp = new Fl_Text_Display(25, 215, 750, 300);
    quit = new Fl_Button(350, 575, 100, 20, "Exit");
    

    quit -> callback(OnExitClicked_cb, (void*) win);

    win -> end();
    return win;
}
