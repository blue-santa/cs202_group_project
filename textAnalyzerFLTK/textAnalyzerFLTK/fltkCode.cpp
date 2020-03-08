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

#include "fltkCode.hpp"

Fl_Native_File_Chooser* fileFind = nullptr;
Fl_Button* browser = nullptr;
Fl_Button* quit = nullptr;

//void browserClicked(Fl_Widget*, void* data){
//    Fl_Native_File_Chooser* fileFind = (Fl_Native_File_Chooser*) data;
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
    
    fileFind = new Fl_Native_File_Chooser;
    fileFind->type(Fl_Native_File_Chooser::BROWSE_DIRECTORY);
    fileFind->directory("/var/tmp");
    fileFind->show();
    quit = new Fl_Button(270, 240, 100, 20, "Exit");
    
    quit -> callback(OnExitClicked_cb, (void*) win);

    win -> end();
    return win;
}
