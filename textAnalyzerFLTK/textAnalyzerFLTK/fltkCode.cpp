//
//  fltkCode.cpp
//  textAnalyzerFLTK
//
//  Created by Sarah Carter on 3/3/20.
//  Copyright © 2020 Sarah Carter. All rights reserved.
//

#include <FL/Fl_Widget.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Native_File_Chooser.H>
#include <FL/Fl_Input.H>
#include <FL/Fl_Output.H>
#include <FL/Fl_Box.H>

#include "fltkCode.hpp"

Fl_Native_File_Chooser* fileFind = nullptr;

Fl_Window* CreateWindow(){
    Fl_Window* win = new Fl_Window(800, 600, "Text Analyzer");
    win -> begin();
    
    fileFind = new Fl_Native_File_Chooser;
    fileFind->type(Fl_Native_File_Chooser::BROWSE_DIRECTORY);
    
    
    win -> end();
    return win;
}
