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

#include "fltkCode.hpp"

Fl_Native_File_Chooser* fileFind = nullptr;
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
    Fl_Window* win = new Fl_Window(800, 600, "Text Analyzer");
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
    fileFind = new Fl_Native_File_Chooser;
    fileFind->type(Fl_Native_File_Chooser::BROWSE_DIRECTORY);
    fileFind->title("Choose a file to analyze");
    fileFind->filter("Textfiles\t*.txt");
    fileFind->directory("/var/tmp");
    fileFind->show();
    buff = new Fl_Text_Buffer();
    reportDisp = new Fl_Text_Display(25, 150, 750, 300);
    browser = new Fl_Button(50, 125, 100, 20, "Browse");
    quit = new Fl_Button(350, 575, 100, 20, "Exit");
    
    reportDisp -> buffer(buff);
    buff->text(output.c_str());
    quit -> callback(OnExitClicked_cb, (void*) win);

    win -> end();
    return win;
}
