//
//  fltkCode.cpp
//  textAnalyzerFLTK
//
//  Created by Sarah Carter on 3/3/20.
//  Copyright © 2020 Sarah Carter. All rights reserved.
//

#include <FL/Fl_Button.H>
#include <FL/Fl_File_Browser.H>
#include <FL/Fl_Input.H>
#include <FL/Fl_Output.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_Text_Display.H>
#include <FL/Fl_Text_Buffer.H>
#include <fstream>
#include <iostream>

#include "fltkCode.hpp"

//Fl_File_Browser* fileFind = nullptr;
Fl_Box* progTitle = nullptr;
Fl_Box* instructions = nullptr;
Fl_Box* description = nullptr;
Fl_Button* browser = nullptr;
Fl_Button* quit = nullptr;
Fl_Output* report = nullptr;
Fl_Text_Display* reportDisp = nullptr;
Fl_Text_Buffer* buff = nullptr;

//void browserClicked(Fl_Widget*, void* data){
//
//
//}

//Close window when "Exit" button is clicked
void OnExitClicked_cb(Fl_Widget* w, void* data){
    if(!data) return;
    Fl_Window* win = (Fl_Window*)data;
    win->hide();
}

Fl_Window* CreateWindow(){
    Fl_Window* win = new Fl_Window(800, 600,"");
    win -> begin();
    std::string output, line;
    std::ifstream fin("Output.txt");
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
    Fl_File_Browser fileFind(10,10,300-20,400-20);
    fileFind.load("*");

//    fileFind->type(Fl_Native_File_Chooser::BROWSE_DIRECTORY);
//    fileFind->title("Choose a file to analyze");
//    fileFind->filter("Textfiles\t*.txt");
//    fileFind->directory("/var/tmp");
//    fileFind->show();
    
    buff = new Fl_Text_Buffer();
    
    progTitle = new Fl_Box(275,10,250, 50, "Text Analyzer");
    progTitle->box(FL_UP_BOX);
    progTitle->labelsize(24);
    
    description = new Fl_Box(100,70,600,50, "This program will take a text that you select"
                                           " and analyze the content for frequency \nof "
                             "specific words to categorize the text for you.");
    description->labelsize(14);
    description->box(FL_UP_BOX);
    
    instructions = new Fl_Box(200, 155, 500, 40, "Click the \"Browse\" button to search "
                              "for the file you wish to analyze.");
    instructions->box(FL_UP_BOX);
    
    reportDisp = new Fl_Text_Display(25, 200, 750, 300);
    browser = new Fl_Button(50, 165, 100, 20, "Browse");
    quit = new Fl_Button(350, 575, 100, 20, "Exit");
    
    reportDisp -> buffer(buff);
    buff->text(output.c_str());
    quit -> callback(OnExitClicked_cb, (void*) win);

    win -> end();
    return win;
}
