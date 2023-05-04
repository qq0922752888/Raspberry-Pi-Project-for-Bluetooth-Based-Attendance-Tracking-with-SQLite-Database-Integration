/*
Author : Tsung-Ying, Tsai 251 260 078
Description : Optional feature for displaying attendence of students in certain class 
Date : 2022-11-17
*/


#ifndef ANALYZER_H_INCLUDED
#define ANALYZER_H_INCLUDED


using namespace std; //delete this later
#include <iostream>
#include <algorithm> // gotta include this
#include <cstring>
#include <vector>
#include <string>
#include "DatabaseManager.h"

class Analyzer{

    private:
        static Analyzer* AnalyzerPointer;
        DatabaseManager* DatabasePointer;

        Analyzer();

    public:

        ~Analyzer();
        static Analyzer* instance();
        void DayAttendence(string Start,string End, string courseID);
        void AverageAttendence(string Start,string End, string cID);



};





#endif // ANALYZER_H_INCLUDED
