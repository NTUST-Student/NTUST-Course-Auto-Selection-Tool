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
*   Filename : SelectionTool.cpp
*   Language : C++14
*   Develop Environment : MSVC
*   Last Update: 05 March, 2023
*   Version : 1.3
*   Code Description: the implementation of class SelectionTool
*   Code Depends on : SelectionTool.h
*   Third Party Library :
*       1. curl-7.84.0  (Static Linking)
*       2. FLTK-1.3.5   (Static Linking)
*/

#define _CRT_SECURE_NO_WARNINGS
#include "SelectionTool.h"
#define CURL_STATICLIB
#include <curl/curl.h>



void SelectionTool::select_course(std::string postURL, std::string postData, std::string headerCookie) {
    CURL* curl;
    CURLcode res;
    struct curl_slist* headers = NULL;
    curl_global_init(CURL_GLOBAL_ALL);
    curl = curl_easy_init();
    if (curl) {
        curl_easy_setopt(curl, CURLOPT_URL, postURL.c_str());
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, postData.c_str());
        headers = curl_slist_append(headers, headerCookie.c_str());
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
        res = curl_easy_perform(curl);
        if (res != CURLE_OK) {
            std::cerr << "curl_easy_perform() failed: " << curl_easy_strerror(res) << std::endl;
        }
        curl_easy_cleanup(curl);
    }
    curl_global_cleanup();
}

void SelectionTool::loop_selection() {
    if (strlen(courseCodes->value()) == 0 || strlen(cookie->value()) == 0)
    {
        looping_mtx.lock();
        looping = false;
        playButton->label("Start Auto Selection");
        enable_setting_GUI();
        looping_mtx.unlock();
        return;
    }
    double sCount = secondInterval->value();
    int msCount = secondInterval->value() * 1000;
    std::string postURL = "";
    if (selectionType->value() == 0)
    {
        postURL = ADD_DROP_COURSE_URL;
    }
    else if (selectionType->value() == 1)
    {
        postURL = AFTER_INITIAL_COURSE_SELECTION_URL;
    }
    std::stringstream ss(courseCodes->value());
    std::string token;
    std::vector<std::string> courseCodeArr;
    while (std::getline(ss, token, ',')) {
        if (!token.empty())
        {
            courseCodeArr.push_back(token);
        }
    }
    std::string headerCookie = HEADER_COOKIE_FRONT + cookie->value();
    selectionCount = 0;
    while (looping) {
        for (int i = 0; i < courseCodeArr.size(); i++)
        {
            std::time_t now_c = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
            std::tm* now_tm = std::localtime(&now_c);
            std::stringstream ss;
            ss << std::put_time(now_tm, "%Y-%m-%d %H:%M:%S");
            std::string lastSelectionTimeStr = ss.str();
            std::cout << "Select Course : " << courseCodeArr[i] << " at " << lastSelectionTimeStr.c_str() << std::endl;
            std::string postData = POST_DATA_FRONT + courseCodeArr[i] + POST_DATA_BACK;
            select_course(postURL, postData, headerCookie);
            lastSelectionTimeText->label(lastSelectionTimeStr.c_str());
        }
        selectionCount++;
        selectionCountText->label(std::to_string(selectionCount).c_str());
        std::cout << "Sleep For " << sCount << " seconds" << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(msCount));
    }
}


void SelectionTool::static_play_button_callback(Fl_Widget* w, void* userdata) {
    static_cast<SelectionTool*>(userdata)->play_button_callback();
}

void SelectionTool::play_button_callback() {
    looping_mtx.lock();
    if (!looping) {
        looping = true;
        looping_mtx.unlock();
        std::cout << "======Start Auto Selection======" << std::endl;
        playButton->label("Stop Auto Selection");
        disable_setting_GUI();
        std::thread selection_thread([this] {this->loop_selection(); });
        selection_thread.detach();
    }
    else {
        looping = false;
        looping_mtx.unlock();
        std::cout << "======Stop Auto Selection======" << std::endl;
        playButton->label("Start Auto Selection");
        selectionCountText->label("");
        enable_setting_GUI();
    }
}

void SelectionTool::static_window_close_callback(Fl_Widget* w, void* userdata)
{
    static_cast<SelectionTool*>(userdata)->window_close_callback();
}
void SelectionTool::window_close_callback()
{
    std::cout << "Window Closing..." << std::endl;
    if (closeSaved == false)
    {
        SaveSettingFile();
    }
    toolWindow->hide();
}

void SelectionTool::enable_setting_GUI()
{
    selectionType->activate();
    courseCodes->activate();
    cookie->activate();
    secondInterval->activate();
}
void SelectionTool::disable_setting_GUI()
{
    selectionType->deactivate();
    courseCodes->deactivate();
    cookie->deactivate();
    secondInterval->deactivate();
}


SelectionTool::~SelectionTool()
{
    std::cout << "Destructor..." << std::endl;
    if (closeSaved == false)
    {
        SaveSettingFile();
    }
}

void SelectionTool::SaveSettingFile()
{
    std::cout << "Saving Setting File..." << std::endl;
    closeSaved = true;
    std::ofstream setting_file;
    setting_file.open(SETTING_FILENAME, std::ios::trunc);
    if (!setting_file)
    {
        std::cerr << "Failed to open file" << std::endl;
        return;
    }
    setting_file << selectionType->value() << std::endl;
    setting_file << courseCodes->value() << std::endl;
    setting_file << cookie->value() << std::endl;
    setting_file << secondInterval->value() << std::endl;
    setting_file.close();
    std::cout << "Save Finished" << std::endl;
}

void SelectionTool::ReadSettingFile()
{
    std::cout << "Reading Setting File..." << std::endl;
    std::ifstream setting_file;
    setting_file.open(SETTING_FILENAME);
    if (!setting_file)
    {
        std::cout << "Setting File Not Found" << std::endl;
        return;
    }
    std::string line;
    std::getline(setting_file, line);
    selectionType->value(std::stoi(line));
    std::getline(setting_file, line);
    courseCodes->value(line.c_str());
    std::getline(setting_file, line);
    cookie->value(line.c_str());
    std::getline(setting_file, line);
    secondInterval->value(std::stod(line));
    setting_file.close();
    std::cout << "Read Finished" << std::endl;
}

void SelectionTool::GenGUI(int windowWidth,int windowHeight)
{
    int defaultX = windowWidth / 3;
    int defaultW = windowWidth * 2 / 3 - 10;
    toolWindow = new Fl_Window(windowWidth, windowHeight, "NTUST Course Auto Selection Tool v1.3");
    toolWindow->callback(static_window_close_callback, (void*)this);
    selectionType = new Fl_Choice(defaultX, 10, defaultW, 30, "Choose Selection Type:");
    selectionType->add("Adding or Droping");
    selectionType->add("Pre-registration(After the draw)");
    selectionType->value(0);
    courseCodes = new Fl_Input(defaultX, 50, defaultW, 30, "Enter Course Codes (comma split):");
    cookie = new Fl_Input(defaultX, 90, defaultW, 30, "Enter Cookie here:");
    secondInterval = new Fl_Counter(defaultX + 30, 130, 200, 30, "Selection Interval (seconds) :");
    secondInterval->align(FL_ALIGN_LEFT);
    secondInterval->bounds(3, 6000);
    secondInterval->value(30);
    playButton = new Fl_Button(50, 170, windowWidth - 100, 30, "Start Auto Selection");
    playButton->callback(static_play_button_callback, (void*)this);
    lastSelectionTimeLabel = new Fl_Box(defaultX - 30, 210, 60, 30, LAST_SELECTION_TIME_FRONT.c_str());
    lastSelectionTimeText = new Fl_Box(windowWidth / 2 - 50, 210, 200, 30);
    selectionCountLabel = new Fl_Box(defaultX - 30, 250, 60, 30, SELECTION_COUNT_FRONT.c_str());
    selectionCountText = new Fl_Box(windowWidth / 2 - 30, 250, 60, 30);
    ReadSettingFile();
}

void SelectionTool::Run()
{
    toolWindow->end();
    toolWindow->show();
    Fl::run();
}