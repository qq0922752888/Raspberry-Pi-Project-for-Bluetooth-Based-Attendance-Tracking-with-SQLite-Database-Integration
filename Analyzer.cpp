/*
Author : Tsung-Ying, Tsai 251 260 078
Description : Optional feature for displaying attendence of students in certain class 
Date : 2022-11-17
*/


#include "Analyzer.h"


//Initialize our Scanner pointer to not point to anything at the begining
Analyzer* Analyzer::AnalyzerPointer = 0;


		//constructor
        Analyzer::Analyzer(){
            DatabaseManager* DatabasePointer = DatabaseManager::instance();
        }

		/*
		Function name : instance
		Description : along with the constructor, this class will only create one object
		parameter description :  no parameters
		return description : instance of the class if none has been created
		*/
        Analyzer* Analyzer::instance(){

            if(!AnalyzerPointer){
                AnalyzerPointer = new Analyzer();

            }
            return AnalyzerPointer;

        }


		//destructor delete allocated memory by pointer referencing other class	
        Analyzer::~Analyzer(){
            delete (DatabasePointer);
            delete (AnalyzerPointer);
        }




/*
Function name : AverageAttendence
Description : Outputs the average attendence rate given interval of date and courseID 
parameter description :  Start: String carrying the start date of the interval, End: String carrying the end interval date, cID: String carrying the courseID of display
return description : none
*/

void Analyzer::AverageAttendence(string Start,string End, string cID){

            Start.erase(remove(Start.begin(),Start.end(),'/'),Start.end());
            End.erase(remove(End.begin(),End.end(),'/'),End.end());

            vector<vector<string>> students = DatabasePointer ->ReadAllStudents();
            vector<string> inner;
            int attendee = 0;
            int numOfStudent = 0;
            string today;

            if(students.size()<1){
                cout << "No attendence log available";
                return;
            }

            if(stoi(End) < stoi(Start)){
                cout << "invalid date interval\n" <<endl;
                return;
            }


            for(int i = 0; i < students.size();i++){
                    inner = students[i];
                    today = inner[2];
                    today.erase(remove(today.begin(),today.end(),'/'),today.end());

                    if(inner.front() == cID && stoi(Start) <= stoi(today) && stoi(End) >= stoi(today)){
                        if(inner.back() == "present"){
                        attendee++;
                        }
                        numOfStudent++;
                    }
                }

            double avg_attendence = (double)attendee / numOfStudent;

            cout << "Attendence Rate is " + to_string(avg_attendence * 100) + "% \n";

}


/*
Function name : DayAttendence
Description : Outputs the attendence rate of everyday given the interval of date and courseID 
parameter description :  Start: String carrying the start date of the interval, End: String carrying the end interval date, cID: String carrying the courseID of display
return description : none
*/

void Analyzer::DayAttendence(string Start,string End, string cID){

        string myStart = Start;
        myStart.erase(remove(myStart.begin(),myStart.end(),'/'),myStart.end());
        End.erase(remove(End.begin(),End.end(),'/'),End.end());

        vector<vector<string>> students = DatabasePointer ->ReadAllStudents();
        vector<string> inner;
        int attendee = 0;
        int numOfStudent = 0;
        string today = myStart;
        string classDay;

        const char* starter = myStart.c_str();
        string startYear = string(1,starter[0]) + string(1,starter[1]) + string(1,starter[2]) + string(1,starter[3]);
        string startMonth = string(1,starter[4]) + string(1,starter[5]);
        string startDay = string(1,starter[6]) + string(1,starter[7]);


        if(students.size()<1){
            cout << "No attendence log available\n" << endl;
            return;
        }


        if(stoi(End) < stoi(today)){
            cout << "invalid date interval\n" <<endl;
            return;
        }


        while(stoi(today) <= stoi(End)){
            attendee = 0;
            numOfStudent = 0;
            classDay = startYear + '/' + startMonth + '/' + startDay;

            for(int i = 0; i < students.size();i++){
                inner = students[i];

                if(inner.front() == cID && inner[2] == classDay){


                    if(inner.back() == "present"){
                        attendee++;
                    }
                    numOfStudent++;
                    }


            }

            if(numOfStudent <1){
                cout << "On the day of " + classDay + " There are no classes for " + cID + "\n";
            }
            else{
                cout << "The attendence rate of " + classDay + " " + to_string( ((double)attendee/numOfStudent) * 100) + "% \n";
            }



                if(startMonth == "12" && startDay == "31"){
                    startYear = to_string(stoi(startYear) +1);
                    startMonth = "01";
                    startDay = "01";
                }
                else if(startDay == "31"){
                    if(stoi(startMonth) < 9){
                        startMonth = "0" + to_string(stoi(startMonth) +1);
                    }
                    else{
                        startMonth = to_string(stoi(startMonth) +1);
                    }

                    startDay = "01";
                }
                else{
                    if(stoi(startDay) < 9){
                        startDay = "0" + to_string(stoi(startDay) +1);
                    }
                    else{
                        startDay = to_string(stoi(startDay) +1);
                    }

                }


                today = startYear + startMonth + startDay;
            }
}







