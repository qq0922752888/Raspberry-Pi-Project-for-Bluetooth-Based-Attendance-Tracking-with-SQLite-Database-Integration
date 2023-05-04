/*
Author: Uzair Salim 251 143 778, Henry Chen 251 166 178
Description: Terminal based user interface to run the program, user is guided through various commands to do what they please.
Last Edit: 2022-11-07
*/
#include "UI.h"
#include "DatabaseManager.h"
#include "DeviceRegister.h"
#include "Login.h"
#include "Analyzer.h"

using namespace std;

//Constructor for the UI class
UI::UI(){ }

/*
Function name : main
Description : allows user to login and perform various operations
parameter description :  no parameters
return description : always returns 0
*/
int main(){
    //instantiate database manager and create tables
    DatabaseManager* manager = DatabaseManager::instance();
    manager->createTable("Device");
    manager->createTable("Attends");

    //Get username and password
    string username;
    string password;
    cout << "WELCOME \n";
    cout << "Enter username\n";
    cin >> username;
    cout << "Enter password\n";
    cin >> password;

    //authenticate the user
    bool userLogin = Login::instance()->AuthenticateUser(username, password);

    //if user is authenticated, run the program
    if (userLogin){
        vector<string> okayCourses = manager->WelcomeScreen(username, password);
        bool useProgram = true;
        //run the program while the user wants to
        while(useProgram){
            //Display commands and ask user which one to use
            int x;
            cout << "\nList of commands\n";
            cout << "1 - Read Data \n2 - Modify Data \n3 - Delete Data \n4 - Run Classroom Scan \n5 - Register a Device \n6 - Attendence Rate \n7 - Logout \n";
            cin >> x;

            if (!cin.good())
            {
                throw invalid_argument("Invalid Input type. Enter Integers.");
            }
			//Allow user to view  either the attendance table or the devices table
            if(x==1){
                int q;
                cout << "\nPress 1 to display students or 2 to display devices: ";
                cin >> q;
                if (!cin.good())
                {
                    throw invalid_argument("Invalid Input type. Enter Integers.");
                }
              	//read all students
                if (q == 1) {
                    int y;
                    cout << "\nPress 1 to display all attendence log, Press 2 to display by Course ID, Press 3 to display student by Date: ";
                    cin >> y;

                    if(!cin.good()){
                        throw invalid_argument("Invalid Input type. Enter Integers.");
                    }
                    if(y==1){
                    //Display all student
                        vector<vector<string>> students = manager->ReadAllStudents(); //Would it good if we keep same student var., and not redeclare everytime?
                        for (auto& vect : students) {
                            if (std::find(okayCourses.begin(), okayCourses.end(), vect[0]) != okayCourses.end()) {
                                for (auto& entry : vect) {
                                    cout << entry + " ";
                                }
                                cout << "\n";
                            }
                        }

                    }
                    else if(y==2){

                        cout << "\nPlease enter Course ID: ";
                        string two;
                        cin >> two;
                        if(!cin.good()){
                            throw invalid_argument("Invalid Input type. Enter Integers.");
                        }


                        vector<vector<string>> students = manager->ReadStudentCondition(two,1);
                        for (auto& vect : students) {
                            if (std::find(okayCourses.begin(), okayCourses.end(), vect[0]) != okayCourses.end()) {
                                for (auto& entry : vect) {
                                    cout << entry + " ";
                                }
                                cout << "\n";
                            }
                        }



                    }
                    else if (y==3){
                        cout << "\nPlease enter Date (YYYY/MM/DD): ";
                        string two;
                        cin >> two;
                        if(!cin.good()){
                            throw invalid_argument("Invalid Input type. Enter Integers.");
                        }

                        vector<vector<string>> students = manager->ReadStudentCondition(two,2);
                        for (auto& vect : students) {
                            if (std::find(okayCourses.begin(), okayCourses.end(), vect[0]) != okayCourses.end()) {
                                for (auto& entry : vect) {
                                    cout << entry + " ";
                                }
                                cout << "\n";
                            }
                        }


                    }


                }
				//display devices
                else if (q == 2) {
                    vector<vector<string>> devices = manager->ReadAllDevice();
                    for (const auto& vect : devices) {
                        for (const auto& entry : vect) {
                            cout << entry + " ";
                        }
                        cout << "\n";
                    }
                }

                else {
                    cout << "Invalid input.\n";
                }
            }
			//user can modify attendance or devices
            else if(x==2){
                int q;
                cout << "\nPress 1 to modify attendence or 2 to modify devices: ";
                cin >> q;
                if (!cin.good())
                {
                    throw invalid_argument("Invalid Input type. Enter Integers.");
                }
              	//user will modify attendance
                if (q == 1) {
                    string sID;
                    string cID;
                    string date;
                    int option;
                    cout << "\nEnter course ID:";
                    cin >> cID;
                    cout << "\nEnter student ID:";
                    cin >> sID;
                    cout << "\nEnter the date:";
                    cin >> date;
                    cout << "\nPress 1 to set present, 2 to set late, 3 to set absent: ";
                    cin >> option;
                    if (!cin.good())
                    {
                        throw invalid_argument("Invalid Input type. Enter Integers.");
                    }

                    if (std::find(okayCourses.begin(), okayCourses.end(), cID) != okayCourses.end()) {
                        if (option == 1) {
                            DatabaseManager::instance()->markPresent(cID, sID, date);
                            cout << "\n";
                        }
                        else if (option == 2) {
                            DatabaseManager::instance()->markLate(cID, sID, date);
                            cout << "\n";
                        }
                        else if (option == 3) {
                            DatabaseManager::instance()->markAbsent(cID, sID, date);
                            cout << "\n";
                        }
                        else {
                            cout << "Invalid input.\n";
                        }
                    }
                    else {
                        cout << "You are not a professor who is in charge of the course that's represented by the ID you entered.\n";
                    }

                }
				//user will modify devices
                else if (q == 2) {
                    string devID;
                    string studentID;
                    cout << "\nEnter the Device ID to modify: ";
                    cin >> devID;
                    cout << "\nEnter the new student ID for: ";
                    cin >> studentID;
                    DeviceRegister::instance()->ModifyDevice(studentID, devID);
                    cout << "\n";
                }

                else {
                    cout << "Invalid input.\n";
                }

            }
            //if user selects 3, they can delete from device or attendance
            else if(x==3){
                int q;
                cout <<"\nPress 1 to delete from attendance or 2 to delete from device: ";
                cin >> q;
                if (!cin.good())
                {
                    throw invalid_argument("Invalid Input type. Enter Integers.");
                }
                if(q==1){
                    string sID;
                    string cID;
                    string date;
                    cout << "\nEnter student ID: ";
                    cin >> sID;
                    cout << "\nEnter course ID: ";
                    cin >> cID;
                    cout << "\nEnter the date: ";
                    cin >> date;
                    if (std::find(okayCourses.begin(), okayCourses.end(), cID) != okayCourses.end()) {
                        manager->DeleteAttendence(sID, cID, date);
                        cout << "\n";
                    }
                    else {
                        cout << "You are not a professor who is in charge of the course that's represented by the ID you entered.\n";
                    }
                }
                if(q==2){
                    string dId;
                    cout << "\nEnter device ID: ";
                    cin >>dId;
                    DeviceRegister::instance()->DeleteDevice(dId);
                    cout << "\n";
                    //cout <<"\nDevice deleted";
                }

            }
            //run a classroom scan
            else if(x==4){
                    string q;
                    cout << "\nPlease enter the course you want the scan to be for: ";
                    cin >> q;
                    if (std::find(okayCourses.begin(), okayCourses.end(), q) != okayCourses.end()) {
                        DatabaseManager::instance()->ScannerNoTime(q);
                        cout << "\n";
                    }
                    else {
                        cout << "You are not a professor who is in charge of the course that's represented by the ID you entered.\n";
                    }
            }
            //if user selects 5, they can register a device
            else if(x==5){
                string dID;
                string sID;
                cout <<"\nEnter Device ID: ";
                cin >> dID;
                cout << "\nEnter Student ID: ";
                cin >> sID;
                DeviceRegister::instance()->StoreDeviceRegister(dID, sID);
                //cout << "\nDevice has been registered";
                cout << "\n";
            }

            else if(x==6){
                string cID;
                string startDate;
                string endDate;
                string input;


                cout << "\nEnter Course ID: ";
                cin >> cID;
                if(!cin.good()){
                    throw invalid_argument("Invalid Input type. Enter Integers.");
                }
                cout << "\n Enter Start Date for the attendence interval(in order of YYYY/MM/DD): ";
                cin >> startDate;
                if(!cin.good()){
                    throw invalid_argument("Invalid Input type. Enter Integers.");
                }
                cout << "\n Enter End Date for the attendence interval(in order of YYYY/MM/DD): ";
                cin >> endDate;
                if(!cin.good()){
                    throw invalid_argument("Invalid Input type. Enter Integers.");
                }

                cout << "Press 1 for Average Attendence over a period of Time, Press 2 for Attendence of each class day \n";
                cin >> input;
                if(!cin.good()){
                    throw invalid_argument("Invalid Input type. Enter Integers.");
                }

                if(stoi(input)==1){
                    Analyzer::instance()-> AverageAttendence(startDate,endDate,cID);
                }
                else if(stoi(input)==2){
                    Analyzer::instance()-> DayAttendence(startDate,endDate,cID);
                }






            }
            else if (x==7) {
                useProgram = false;
                cout << "\n";
            }

            else{
                cout << "\nInvalid input, please try again";
            }

        }
        cout <<"You have been logged out\n";
    }

    else {
        cout << "Sorry, your credentials do not match any on record. Exiting program.\n";
    }

    return 0;

}
