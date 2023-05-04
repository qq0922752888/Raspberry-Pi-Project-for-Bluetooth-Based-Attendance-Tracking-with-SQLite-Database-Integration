/*
Author : Xu Wang 250 748 901, Henry Chen 251 166 178
Description : DatabaseManager is responsible for formatting SQL queries so that the SQLQuery class can read or write into database
Date : 2022-10-31
*/
#include <string>
#include <vector>
#include <iostream>
#include "DatabaseManager.h"
#include "SQLQuery.h"
#include "Scanner.h"

using namespace std;

DatabaseManager *DatabaseManager::Manager = 0;

/*
Function name : instance
Description : along with the constructor, this class will only create one object
parameter description :  no parameters
return description : instance of the class if none has been created
*/
DatabaseManager* DatabaseManager::instance()
{
    if (DatabaseManager::Manager == NULL) {
        DatabaseManager::Manager = new DatabaseManager();
    }
    return Manager;
}
//constructor for the class
DatabaseManager::DatabaseManager()
{
}

/*
Function name : ReadAllStudents
Description : selects all data from Attends table which represents student data
parameter description : none
return description : SQL table
*/
vector<vector<string>> DatabaseManager::ReadAllStudents()
{
    string sqlCommand = "select * from Attends;";
    return SQLQuery::instance()->ReadMany(sqlCommand);
}

/*
Function name : ReadSomeStudents
Description : selects data from some students given their student ID's in a vector
parameter description : stuID is a vector of string containing student Id's which are fed into the for loop which completes a seperate SQLQuery call
return description : returns a container which is a vector of vector which contains the data for the relevant students
*/
vector<vector<string>> DatabaseManager::ReadSomeStudents(vector<std::string> stuID, std::string courseInput)
{
    vector<vector<string>> returnContainer;
    for (int i = 0; i < stuID.size(); i++)
    {
        string sqlCommand = "select * from Attends where StudentNumber = \"" + stuID[i] + "\" and CourseID = \"" + courseInput + "\";";
        returnContainer.push_back(SQLQuery::instance()->ReadOne(sqlCommand));
    }

    return returnContainer;
}


/*
Function name : ReadStudentCondition
Description : selects data from some students given CourseID or Time condition
parameter description : CID is courseID, time is entered time
return description : returns a container which is a vector of vector which contains the data for the relevant students
*/

vector<vector<string>> DatabaseManager::ReadStudentCondition(std::string input , int mode)
{


    //Mode 1: Read by CourseID
    if(mode == 1){

            string sqlCommand = "select * from Attends where CourseId = \"" + input +"\";";
            return SQLQuery::instance()->ReadMany(sqlCommand);

    }
    //Mode 2: Read by Date
    else if (mode == 2){

            string sqlCommand = "select * from Attends where Date = \"" + input +"\";";
            return SQLQuery::instance()->ReadMany(sqlCommand);


    }
    else{
        cout << "Error, not valid input\n" <<endl;
        return {};
    }

}





/*
Function name : WhoTakesWhat
Description : returns Takes table which represents which student takes what class
parameter description : none
return description : SQL
*/
vector<vector<string>> DatabaseManager::WhoTakesWhat()
{
    string sqlCommand = "select * from Takes;";
    return SQLQuery::instance()->ReadMany(sqlCommand);
}

/*
Function name : WelcomeScreen
Description : welcome screen print outs and prompts
parameter description : username and passwords which represent logins
return description : SQL
*/
vector<string> DatabaseManager::WelcomeScreen(string username, string password)
{
    vector<vector<string>> tempContainer;
    vector<string> returnContainer;
    string sqlCommand = "select ProfessorID from Professor where Username = \"" + username + "\" and Password = \"" + password + "\";";
    string PID = SQLQuery::instance()->ReadOne(sqlCommand).front();
    sqlCommand = "select CourseName, CourseID from Course where ProfessorID = \"" + PID + "\";";
    string message = "Hello, welcome to attendence for courses: ";
    tempContainer = SQLQuery::instance()->ReadMany(sqlCommand);
    for (auto& vect : tempContainer) {
        message = message + vect.front();
        message = message + "(" + vect.back() + "); ";
        returnContainer.push_back(vect.back());
    }
    cout << message << endl;
    return returnContainer;
}

/*
Function name : ReadAllDevice
Description : Displays all data from Device table
parameter description : none
return description : SQL
*/
vector<vector<string>> DatabaseManager::ReadAllDevice()
{
    string sqlCommand = "select * from Device;";
    return SQLQuery::instance()->ReadMany(sqlCommand);
}

/*
Function name : GetDeviceStudent
Description : returns student number from the device table given the device id
parameter description : string representation of the device ID
return description : SQL
*/
vector<string> DatabaseManager::GetDeviceStudent(std::string DID)
{
    string sqlCommand = "select StudentNumber from Device where DeviceID = \"" + DID + "\";";
    return SQLQuery::instance()->ReadOne(sqlCommand);
}

/*
Function name : AuthenticateUser
Description : Will submit a query given username and password, if it returns empty we know both are not correct
parameter description : string of username and password which represent login credentials
return description : true if both entries are true
*/
bool DatabaseManager::AuthenticateUser(std::string username, std::string password) {
    string sqlCommand = "select ProfessorID from Professor where Username = \"" + username + +"\" and Password = \"" + password +"\";";
    if (SQLQuery::instance()->ReadOne(sqlCommand).empty() == false) {
        return true;
    }
    else {
        return false;
    }
}

/*
Function name : ScannerNoTime
Description : Scanner method without a user input time
parameter description : course ID
return description : none
*/
void DatabaseManager::ScannerNoTime(std::string CID)
{
    time_t now = time(0);
    tm* localTime = localtime(&now);
    int year = 1900 + localTime->tm_year;
    int month = 1 + localTime->tm_mon;
    int day = localTime->tm_mday;
    string date = to_string(year) + "/" + to_string(month) + "/" + to_string(day);
    vector<string> Devices = Scanner::getScanner()->scan();

    vector<vector<string>> students = DatabaseManager::instance()->WhoTakesWhat();
    for (auto& vect : students) {
        if (CID == vect[0]) {
            DatabaseManager::instance()->WriteToAttendence(CID, vect[1], date, "absent");
        }
    }

    for (auto& vect : Devices) {
        vector<string> student = DatabaseManager::instance()->GetDeviceStudent(vect);
        if (!student.empty()){
            DatabaseManager::instance()->markPresent(CID, student.front(), date);
        }
        else {
            cout << vect + " is a deviceid not paired to any student" << endl;
       	 }
    }
}

/*
Function name : ScannerTimed
Description : Scanner method with a user input time
parameter description : course ID, set time for start time and what time a student is considered late
return description : none
*/
void DatabaseManager::ScannerTimed(std::string CID, time_t timeTillStart, time_t timeTillLate)
{
    time_t now = time(0);
    tm* localTime = localtime(&now);
    int year = 1900 + localTime->tm_year;
    int month = 1 + localTime->tm_mon;
    int day = localTime->tm_mday;
    string date = to_string(year) + to_string(month) + to_string(day);

    Scanner* scanner = Scanner::getScanner();

    //Wait until we reached the desired time to perform the first scan
    sleep(difftime(timeTillStart, time(0)));

    cout <<"Taking first attendence scan" << endl;

    //Scan the devices currently present and store them in devices
    vector<string> devices = scanner->scan();

    for (auto& vect : devices) {
        cout << vect << endl;
        vector<string> student = DatabaseManager::instance()->GetDeviceStudent(vect);
        if (!student.empty()){
            DatabaseManager::instance()->WriteToAttendence(CID, student.front(), date, "present");
        }
    }

    cout << "Completed first attendence scan" << endl;

    //Wait until we reached the desired time to perform the second scan
    sleep(difftime(timeTillLate, time(0)));

    cout << "Taking late attendence scan" << endl;

    //Scan the devices that are now all present
    vector<string> temp = scanner->scan();

    bool contains;

    //Check to see if the devices in temp was not scanned into devices, if it is not, it is marked as late, and added to devices
    for (int i = 0; i < temp.size(); i++){
        contains = false;
        for (int j = 0; j < devices.size() && !contains; j++){
            if (strcmp(temp[i].c_str(), devices[j].c_str()) == 0){
                contains = true;
            }
        }
        if(!contains){
            vector<string> student = DatabaseManager::instance()->GetDeviceStudent(temp[i]);
            if (!student.empty()){
                DatabaseManager::instance()->WriteToAttendence(CID, student.front(), date, "late");
            }
        }
    }
}

/*
Function name : WriteToAttendance
Description : writes into the Attends table
parameter description : courseID which identifies the course, student number which identifies the student and date and presence which determines a students state and which day
return description : none
*/
void DatabaseManager::WriteToAttendence(std::string courseId, std::string studentNumber, std::string date, std::string presence)
{
    string sqlCommand = "insert into Attends values (\"" + courseId + "\" , \"" + studentNumber + "\", \"" + date + "\", \"" + presence + "\");";
    SQLQuery::instance()->Exec(sqlCommand);
}

/*
Function name : WriteToDevice
Description : writes into the Device table which is a table containing all registered devices along with their owners
parameter description : Device identification and ID which is the owner
return description : none
*/
void DatabaseManager::WriteToDevice(std::string Device, std::string ID)
{

    std::string sqlCommand = "insert into Device values (\"" + Device + "\" , \"" + ID + "\");";
    SQLQuery::instance()->Exec(sqlCommand);
}

/*
Function name : WriteToProfessor
Description : writes into the Professor table which functions as the login table
parameter description : ID which is the professor ID and username and password which are the logins
return description : none
*/
void DatabaseManager::WriteToProfessor(std::string ID, std::string Username, std::string Password)
{

    std::string sqlCommand = "insert into Professor values (\"" + ID + "\" , \"" + Username + "\" , \"" + Password + "\");";
    SQLQuery::instance()->Exec(sqlCommand);
}

/*
Function name : WriteToStudent
Description : writes into the Student table which identifies each student ID with first and last name
parameter description : ID is the identification, FName and LName are first and last name
return description : none
*/
void DatabaseManager::WriteToStudent(std::string ID, std::string FName, std::string LName)
{

    std::string sqlCommand = "insert into Student values (\"" + ID + "\" , \"" + FName + "\" , \"" + LName + "\");";
    SQLQuery::instance()->Exec(sqlCommand);
}

/*
Function name : WriteToCourse
Description : writes into the Course table which contains what course, name and who teaches it
parameter description : CID is the course ID, Cname is the common name of the course and PID is the professor ID who teaches it
return description : none
*/
void DatabaseManager::WriteToCourse(std::string CID, std::string CName, std::string PID)
{

    std::string sqlCommand = "insert into Course values (\"" + CID + "\" , \"" + CName + "\" , \"" + PID + "\");";
    SQLQuery::instance()->Exec(sqlCommand);
}

/*
Function name : WriteToTakes
Description : writes into the Takes table which contains the membership of all students and classes they take
parameter description : CID is the course ID and SID is student ID
return description : none
*/
void DatabaseManager::WriteToTakes(std::string CID, std::string SID)
{
    string sqlCommand = "insert into Takes values (\"" + CID + "\" , \"" + SID + "\");";
    SQLQuery::instance()->Exec(sqlCommand);
}

/*
Function name : markPresent
Description : updates Attends table and sets the student as present
parameter description : CourseID, studentID and date will identify which entry to change to present
return description : none
*/
void DatabaseManager::markPresent(std::string CourseID, std::string studentID, std::string date)
{
    string sqlCommand = "update Attends set Prescence = \"present\" where StudentNumber = \"" + studentID + "\" and CourseID = \"" + CourseID + "\" and Date = \"" + date + "\";";
    SQLQuery::instance()->Exec(sqlCommand);
}
/*
Function name : markLAte
Description : updates Attends table and sets the student as late
parameter description : CourseID, studentID and date will identify which entry to change to late
return description : none
*/
void DatabaseManager::markLate(std::string CourseID, std::string studentID, std::string date)
{
    string sqlCommand = "update Attends set Prescence = \"late\" where StudentNumber = \"" + studentID + "\" and CourseID = \"" + CourseID + "\" and Date = \"" + date + "\";";
    SQLQuery::instance()->Exec(sqlCommand);
}
/*
Function name : markAbsent
Description : updates Attends table and sets the student as absent
parameter description : CourseID, studentID and date will identify which entry to change to absent
return description : none
*/
void DatabaseManager::markAbsent(std::string CourseID, std::string studentID, std::string date)
{
    string sqlCommand = "update Attends set Prescence = \"absent\" where StudentNumber = \"" + studentID + "\" and CourseID = \"" + CourseID + "\" and Date = \"" + date + "\";";
    SQLQuery::instance()->Exec(sqlCommand);
}
/*
Function name : ModifyDeviceStudentNum
Description : updates student number in Device table given the device ID
parameter description : SID is student ID and DID is device ID
return description : none
*/
void DatabaseManager::ModifyDeviceStudentNum(std::string SID, std::string DID)
{
    string sqlCommand = "update Device set StudentNumber = \"" + SID + "\" where DeviceID = \"" + DID + "\"; ";
    SQLQuery::instance()->Exec(sqlCommand);
}
/*
Function name : DeleteAttendence
Description : deletes an entry from Attends
parameter description : SID is student ID and DID is device ID and Date is the specified date
return description : none
*/
void DatabaseManager::DeleteAttendence(std::string SID, std::string CID, std::string Date)
{
    string sqlCommand = "delete from Attends where StudentNumber = \"" + SID + "\" and CourseID = \"" + CID + "\" and Date = \"" + Date + "\";";
    SQLQuery::instance()->Exec(sqlCommand);
}
/*
Function name : DeleteDevice
Description : deletes an entry from Device
parameter description : DID is device ID
return description : none
*/
void DatabaseManager::DeleteDevice(std::string DID)
{
    string sqlCommand = "delete from Device where DeviceID = \"" + DID + "\";";
    SQLQuery::instance()->Exec(sqlCommand);
}
/*
Function name : createTable
Description : attempts to create tables if they have not been before
parameter description : name is the name of the table
return description : none
*/
void DatabaseManager::createTable(std::string name)
{
    std::string sqlCommand;
    if (name == "Device")
    {
        sqlCommand = "create table if not exists " + name + "(DeviceID varchar(255), StudentNumber varchar(255), PRIMARY KEY(DeviceID), FOREIGN KEY(StudentNumber) REFERENCES Student(StudentNumber)); ";
    }
    else if (name == "Attends")
    {
        sqlCommand = "create table if not exists " + name + "(CourseID varchar(255), StudentNumber varchar(255), Date varchar(255), Prescence varchar(255), PRIMARY KEY(CourseID, StudentNumber, Date), FOREIGN KEY(CourseID) REFERENCES Course(CourseID), FOREIGN KEY(StudentNumber) REFERENCES Student(StudentNumber)); ";
    }
    else if (name == "Professor")
    {
        sqlCommand = "create table if not exists " + name + "(ProfessorID varchar(255), Username varchar(255), Password varchar(255), PRIMARY KEY(ProfessorID)); ";
    }
    else if (name == "Student")
    {
        sqlCommand = "create table if not exists " + name + "(StudentNumber varchar(255), FirstName varchar(255), LastName varchar(255), PRIMARY KEY(StudentNumber)); ";
    }
    else if (name == "Course")
    {
        sqlCommand = "create table if not exists " + name + "(CourseID varchar(255), CourseName varchar(255), ProfessorID varchar(255), PRIMARY KEY(CourseID), FOREIGN KEY(ProfessorID) REFERENCES Professor(ProfessorID)); ";
    }
    else if (name == "Takes")
    {
        sqlCommand = "create table if not exists " + name + "(CourseID varchar(255) NOT NULL, StudentNumber varchar(255) NOT NULL, PRIMARY KEY(CourseID, StudentNumber), FOREIGN KEY(CourseID) REFERENCES Course(CourseID), FOREIGN KEY(StudentNumber) REFERENCES Student(StudentNumber)); ";
    }
    SQLQuery::instance()->createTable(sqlCommand);
}

