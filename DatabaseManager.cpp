/**
**@brief DatabaseManager is responsible for formatting SQL queries so that the SQLQuery class can read or write into database
**@author Xu Wang 250 748 901, Henry Chen 251 166 178, Artur Krupa 251190423
**/
#include "DatabaseManager.h"

using namespace std;

DatabaseManager *DatabaseManager::Manager = 0;

/**
*@brief along with the constructor, this class will ensure only one object of this class is ever created
*@param  no parameters
*@returns instance of the class if none has been created
*@author Xu Wang 250 748 901
**/
DatabaseManager* DatabaseManager::instance()
{
    if (DatabaseManager::Manager == NULL) {
        DatabaseManager::Manager = new DatabaseManager();
    }
    return Manager;
}

/**
*@brief constructor for the class; does nothing on its own
*@param  no parameters
*@returns nothing
*@author Xu Wang 250 748 901
**/
DatabaseManager::DatabaseManager()
{
}

/**
*@brief sets the output label in the gui that information will be displayed to
*@param  a label pointer that points at the display box in the gui
*@returns nothing
*@author Artur Krupa 251190423
**/
void DatabaseManager::setLabel(QLabel* label){
    textBox = label;
}

/**
*@brief selects all data from Attends table which represents student data
*@param  none
*@returns a vector that holds vectors; this represents the collections of attendence data for particular attendence entries
*@author Xu Wang 250 748 901
**/
vector<vector<string>> DatabaseManager::ReadAllStudents()
{
    string sqlCommand = "select * from Attends;";
    return SQLQuery::instance()->ReadMany(sqlCommand);
}

/**
*@brief selects data from some students given their student ID's in a vector
*@param stuID is a vector of string containing student Id's which are fed into the for loop which completes a seperate SQLQuery call
*@returns returns a container which is a vector of vector which contains the data for the relevant students
*@author Xu Wang 250 748 901
**/
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


/**
*@brief selects data from some students given CourseID or Time condition
*@param CID is courseID, time is entered time
*@returns returns a container which is a vector of vector which contains the data for the relevant students
*@author Tsung-Ying Tsai 251 262 078
**/

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
        textBox->setText("Error, not valid input\n");
        return {};
    }

}





/**
*@brief returns Takes table which represents which student takes what class
*@param none
*@returns SQL
*@author Henry Chen 251 166 178
**/
vector<vector<string>> DatabaseManager::WhoTakesWhat()
{
    string sqlCommand = "select * from Takes;";
    return SQLQuery::instance()->ReadMany(sqlCommand);
}

/**
*@brief checks which courses are okay for a logged in user to access. Also updates and refreshes which courses the professor can access
*@param username and passwords which represent logins
*@returns SQL
*@author Henry Chen 251 166 178
**/
vector<string> DatabaseManager::CheckCourses(string username, string password)
{
    vector<vector<string>> tempContainer;
    vector<string> returnContainer;
    string sqlCommand = "select ProfessorID from Professor where Username = \"" + username + "\" and Password = \"" + password + "\";";
    string PID = SQLQuery::instance()->ReadOne(sqlCommand).front();
    sqlCommand = "select CourseName, CourseID from Course where ProfessorID = \"" + PID + "\";";
    tempContainer = SQLQuery::instance()->ReadMany(sqlCommand);
    for (auto& vect : tempContainer) {
        returnContainer.push_back(vect.back());
    }
    return returnContainer;
}

/**
*@brief Displays all data from Device table
*@param none
*@returns SQL
*@author Henry Chen 251 166 178
**/
vector<vector<string>> DatabaseManager::ReadAllDevice()
{
    string sqlCommand = "select * from Device;";
    return SQLQuery::instance()->ReadMany(sqlCommand);
}

/**
*@brief returns student number from the device table given the device id
*@param string representation of the device ID
*@returns SQL
*@author Henry Chen 251 166 178
**/
vector<string> DatabaseManager::GetDeviceStudent(std::string DID)
{
    string sqlCommand = "select StudentNumber from Device where DeviceID = \"" + DID + "\";";
    return SQLQuery::instance()->ReadOne(sqlCommand);
}

/**
*@brief Will submit a query given username and password, if it returns empty we know both are not correct
*@param string of username and password which represent login credentials
*@returns true if both entries are true
*@author Henry Chen 251 166 178
**/
bool DatabaseManager::AuthenticateUser(std::string username, std::string password) {
    string sqlCommand = "select ProfessorID from Professor where Username = \"" + username + +"\" and Password = \"" + password +"\";";
    if (SQLQuery::instance()->ReadOne(sqlCommand).empty() == false) {
        return true;
    }
    else {
        return false;
    }
}

/**
*@brief Scanner method without a user input time
*@param course ID
*@returns none
*@author Henry Chen 251 166 178
**/
void DatabaseManager::ScannerNoTime(std::string CID)
{
    time_t now = time(0);
    tm* localTime = localtime(&now);
    int year = 1900 + localTime->tm_year;
    int month = 1 + localTime->tm_mon;
    int day = localTime->tm_mday;
    string date = to_string(year) + "/" + to_string(month) + "/" + to_string(day);
    vector<string> Devices = Scanner::getScanner()->scan();
    
    //List of students who are suppose to take this class and have not had their attendence taken
    vector<vector<string>> knownStudents = SQLQuery::instance()->ReadMany("SELECT StudentNumber FROM Takes WHERE CourseID='" +CID +"' AND StudentNumber NOT IN (SELECT StudentNumber FROM Attends WHERE CourseID='" +CID +"' AND Date='"+date+"');");
    string unKnownDevices = "";

    for (auto& vect : Devices) {
        vector<string> student = DatabaseManager::instance()->GetDeviceStudent(vect);
        //If there is a student paired with the device
        if (!student.empty()){
            //If the student is supose to be in this class and their attendence has not been marked for today
            for (auto& knownStudent : knownStudents){
                if(strcmp(student.front().c_str(), knownStudent[0].c_str()) == 0){
                    DatabaseManager::instance()->WriteToAttendence(CID, student.front(), date, "present");
                }
            }
        }
        else {
            unKnownDevices = unKnownDevices + vect +" ";
       	 }
    }

    unKnownDevices = unKnownDevices + "deviceids not paired to any student";

    textBox->setText(QString::fromStdString(unKnownDevices));

    string sqlCommand = "SELECT StudentNumber FROM Takes WHERE CourseID='"+CID+"' AND StudentNumber NOT IN (SELECT StudentNumber FROM Attends WHERE CourseID='" +CID +"' AND Date='" +date+"');";
    vector<vector<string>> absentStudents = SQLQuery::instance()->ReadMany(sqlCommand);

    for (auto& student : absentStudents){
        DatabaseManager::instance()->WriteToAttendence(CID, student[0], date, "absent");
    }
}

/**
*@brief Scanner method with a user input time
*@param course ID, set time for start time and what time a student is considered late
*@returns none
*@author Artur Krupa 251190423
**/
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

    textBox->setText("Taking first attendence scan");

    //Scan the devices currently present and store them in devices
    vector<string> devices = scanner->scan();

    vector<vector<string>> knownStudents = SQLQuery::instance()->ReadMany("SELECT StudentNumber FROM Takes WHERE CourseID='" +CID +"' AND StudentNumber NOT IN (SELECT StudentNumber FROM Attends WHERE CourseID='" +CID +"' AND Date='"+date+"');");
    string unKnownDevices = "";

     for (auto& vect : devices) {
        vector<string> student = DatabaseManager::instance()->GetDeviceStudent(vect);
        //If there is a student paired with the device
        if (!student.empty()){
            //If the student is supose to be in this class and their attendence has not been marked for today
            for (auto& knownStudent : knownStudents){
                if(strcmp(student.front().c_str(), knownStudent[0].c_str()) == 0){
                    DatabaseManager::instance()->WriteToAttendence(CID, student.front(), date, "present");
                }
            }
        }
        else {
            unKnownDevices = unKnownDevices + vect +" ";
         }
    }

    unKnownDevices = unKnownDevices + "deviceids not paired to any student";
    textBox->setText(QString::fromStdString(unKnownDevices));

    textBox->setText("Completed first attendence scan");

    //Wait until we reached the desired time to perform the second scan
    sleep(difftime(timeTillLate, time(0)));

    textBox->setText("Taking late attendence scan");

    //Scan the devices that are now all present
    vector<string> temp = scanner->scan();

    bool contains;
    unKnownDevices = "";

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
               for (auto& knownStudent : knownStudents){
                if(strcmp(student.front().c_str(), knownStudent[0].c_str()) == 0){
                    DatabaseManager::instance()->WriteToAttendence(CID, student.front(), date, "late");
                }
            }
            }
        else {
            unKnownDevices = unKnownDevices + temp[i] +" ";
       	 }
        }
    }
    unKnownDevices = unKnownDevices + "deviceids not paired to any student";
    textBox->setText(QString::fromStdString(unKnownDevices));

    string sqlCommand = "SELECT StudentNumber FROM Takes WHERE CourseID='"+CID+"' AND StudentNumber NOT IN (SELECT StudentNumber FROM Attends WHERE CourseID='" +CID +"' AND Date='" +date+"');";
    vector<vector<string>> absentStudents = SQLQuery::instance()->ReadMany(sqlCommand);

    for (auto& student : absentStudents){
        DatabaseManager::instance()->WriteToAttendence(CID, student[0], date, "absent");
    }
}

/**
*@brief writes into the Attends table
*@param courseID which identifies the course, student number which identifies the student and date and presence which determines a students state and which day
*@returns none
*@author Henry Chen 251 166 178
**/
void DatabaseManager::WriteToAttendence(std::string courseId, std::string studentNumber, std::string date, std::string presence)
{
    string sqlCommand = "insert into Attends values (\"" + courseId + "\" , \"" + studentNumber + "\", \"" + date + "\", \"" + presence + "\");";
    SQLQuery::instance()->Exec(sqlCommand);
}

/**
*@brief writes into the Device table which is a table containing all registered devices along with their owners
*@param Device identification and ID which is the owner
*@returns none
*@author Henry Chen 251 166 178
**/
void DatabaseManager::WriteToDevice(std::string Device, std::string ID)
{

    std::string sqlCommand = "insert into Device values (\"" + Device + "\" , \"" + ID + "\");";
    SQLQuery::instance()->Exec(sqlCommand);
}

/**
*@brief writes into the Professor table which functions as the login table
*@param ID which is the professor ID and username and password which are the logins
*@returns none
*@author Henry Chen 251 166 178
**/
void DatabaseManager::WriteToProfessor(std::string ID, std::string Username, std::string Password)
{

    std::string sqlCommand = "insert into Professor values (\"" + ID + "\" , \"" + Username + "\" , \"" + Password + "\");";
    SQLQuery::instance()->Exec(sqlCommand);
}

/**
*@brief writes into the Student table which identifies each student ID with first and last name
*@param ID is the identification, FName and LName are first and last name
*@returns none
*@author Henry Chen 251 166 178
**/
void DatabaseManager::WriteToStudent(std::string ID, std::string FName, std::string LName)
{

    std::string sqlCommand = "insert into Student values (\"" + ID + "\" , \"" + FName + "\" , \"" + LName + "\");";
    SQLQuery::instance()->Exec(sqlCommand);
}

/**
*@brief writes into the Course table which contains what course, name and who teaches it
*@param CID is the course ID, Cname is the common name of the course and PID is the professor ID who teaches it
*@returns none
*@author Henry Chen 251 166 178
**/
void DatabaseManager::WriteToCourse(std::string CID, std::string CName, std::string PID)
{

    std::string sqlCommand = "insert into Course values (\"" + CID + "\" , \"" + CName + "\" , \"" + PID + "\");";
    SQLQuery::instance()->Exec(sqlCommand);
}

/**
*@brief writes into the Takes table which contains the membership of all students and classes they take
*@param CID is the course ID and SID is student ID
*@returns none
*@author Henry Chen 251 166 178
**/
void DatabaseManager::WriteToTakes(std::string CID, std::string SID)
{
    string sqlCommand = "insert into Takes values (\"" + CID + "\" , \"" + SID + "\");";
    SQLQuery::instance()->Exec(sqlCommand);
}

/**
*@brief updates Attends table and sets the student as present
*@param CourseID, studentID and date will identify which entry to change to present
*@returns none
*@author Henry Chen 251 166 178
**/
void DatabaseManager::markPresent(std::string CourseID, std::string studentID, std::string date)
{
    string sqlCommand = "update Attends set Prescence = \"present\" where StudentNumber = \"" + studentID + "\" and CourseID = \"" + CourseID + "\" and Date = \"" + date + "\";";
    SQLQuery::instance()->Exec(sqlCommand);
}
/**
*@brief updates Attends table and sets the student as late
*@param CourseID, studentID and date will identify which entry to change to late
*@returns none
*@author Henry Chen 251 166 178
**/
void DatabaseManager::markLate(std::string CourseID, std::string studentID, std::string date)
{
    string sqlCommand = "update Attends set Prescence = \"late\" where StudentNumber = \"" + studentID + "\" and CourseID = \"" + CourseID + "\" and Date = \"" + date + "\";";
    SQLQuery::instance()->Exec(sqlCommand);
}
/**
*@brief updates Attends table and sets the student as absent
*@param CourseID, studentID and date will identify which entry to change to absent
*@returns none
*@author Henry Chen 251 166 178
**/
void DatabaseManager::markAbsent(std::string CourseID, std::string studentID, std::string date)
{
    string sqlCommand = "update Attends set Prescence = \"absent\" where StudentNumber = \"" + studentID + "\" and CourseID = \"" + CourseID + "\" and Date = \"" + date + "\";";
    SQLQuery::instance()->Exec(sqlCommand);
}
/**
*@brief updates student number in Device table given the device ID
*@param SID is student ID and DID is device ID
*@returns none
*@author Henry Chen 251 166 178
**/
void DatabaseManager::ModifyDeviceStudentNum(std::string SID, std::string DID)
{
    string sqlCommand = "update Device set StudentNumber = \"" + SID + "\" where DeviceID = \"" + DID + "\"; ";
    SQLQuery::instance()->Exec(sqlCommand);
}
/**
*@brief deletes an entry from Attends
*@param SID is student ID and DID is device ID and Date is the specified date
*@returns none
*@author Henry Chen 251 166 178
**/
void DatabaseManager::DeleteAttendence(std::string SID, std::string CID, std::string Date)
{
    string sqlCommand = "delete from Attends where StudentNumber = \"" + SID + "\" and CourseID = \"" + CID + "\" and Date = \"" + Date + "\";";
    SQLQuery::instance()->Exec(sqlCommand);
}
/**
*@brief deletes an entry from Device
*@param DID is device ID
*@returns none
*@author Henry Chen 251 166 178
**/
void DatabaseManager::DeleteDevice(std::string DID)
{
    string sqlCommand = "delete from Device where DeviceID = \"" + DID + "\";";
    SQLQuery::instance()->Exec(sqlCommand);
}
/**
*@brief attempts to create tables if they have not been before
*@param name is the name of the table
*@returns none
*@author Henry Chen 251 166 178
**/
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

