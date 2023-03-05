/*
Copyright (C) 2023 Anonymous student at National Taiwan University of Science and Technology

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

/*
*   Filename : SelectionTool.h
*   Language : C++14
*   Develop Environment : MSVC
*   Last Update: 05 March, 2023
*	Version : 1.3
*   Code Description: the header of class SelectionTool
*   Code Depends on : 
*   Third Party Library :
*       1. curl-7.84.0	(Static Linking)
*       2. FLTK-1.3.5	(Static Linking)
*/

#pragma once
#ifndef _SELECTIONTOOL_H_
#define _SELECTIONTOOL_H_
#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Input.H>
#include <FL/Fl_Choice.H>
#include <FL/Fl_Counter.H>
#include <FL/Fl_Box.H>


#include <thread>
#include <mutex>
#include <string>
#include <cstring>
#include <iostream>
#include <chrono>
#include <iomanip>
#include <sstream>
#include <vector>
#include <fstream>

class SelectionTool
{
private:
	std::mutex looping_mtx;
	bool looping = false;
	Fl_Window* toolWindow;
	Fl_Choice* selectionType;
	Fl_Input* courseCodes;
	Fl_Input* cookie;
	Fl_Counter* secondInterval;
	Fl_Button* playButton;
	Fl_Box* lastSelectionTimeLabel;
	Fl_Box* lastSelectionTimeText;
	Fl_Box* selectionCountLabel;
	Fl_Box* selectionCountText;
	int selectionCount = 0;
	bool closeSaved = false;


	void select_course(std::string postURL, std::string postData, std::string headerCookie);
	void loop_selection();
	static void static_play_button_callback(Fl_Widget* w,void* userdata);
	void play_button_callback();
	static void static_window_close_callback(Fl_Widget* w, void* userdata);
	void window_close_callback();
	void enable_setting_GUI();
	void disable_setting_GUI();

	const std::string ADD_DROP_COURSE_URL = "https://courseselection.ntust.edu.tw/AddAndSub/B01/ExtraJoin";
	const std::string AFTER_INITIAL_COURSE_SELECTION_URL = "https://courseselection.ntust.edu.tw/First/A06/ExtraJoin";
	const std::string POST_DATA_FRONT = "CourseNo=";
	const std::string POST_DATA_BACK = "&type=3";
	const std::string HEADER_COOKIE_FRONT = "cookie: ";
	const std::string LAST_SELECTION_TIME_FRONT = "Last Selection Time :";
	const std::string SELECTION_COUNT_FRONT = "Selection Count :";
	const std::string SETTING_FILENAME = "./setting.txt";
	
public:
	~SelectionTool();
	void SaveSettingFile();
	void ReadSettingFile();
	void GenGUI(int,int);
	void Run();
};
#endif