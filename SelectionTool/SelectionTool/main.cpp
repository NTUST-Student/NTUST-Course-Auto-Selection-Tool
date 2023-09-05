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
*   Filename : main.cpp
*   Language : C++14
*   Develop Environment : MSVC
*   Last Update: 05 March, 2023
*   Version : 1.3
*   Code Description: the enter point of this program
*   Code Depends on : SelectionTool.h
*   Third Party Library :
*       1. curl-7.84.0  (Static Linking)
*       2. FLTK-1.3.5   (Static Linking)
*/

/*
Project History : 
v1.0 : basic function
v1.1 : allow multiple course selection, and show the selection time
v1.2 : save the setting in setting.txt
v1.3 : add program guide, and revise some words.
v1.4 : Since school have change some request rules, so I modify the header to make tool still working. 2023-09-15
*/

#include "SelectionTool.h"

int main(int argc, char *argv[]) {
    SelectionTool tool;
    tool.GenGUI(700, 290);
    tool.Run();
    return 0;
}
