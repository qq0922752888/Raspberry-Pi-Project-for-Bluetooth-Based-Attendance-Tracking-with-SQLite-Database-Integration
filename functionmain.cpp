#include "functionmain.h"
#include "ui_functionmain.h"
#include <stdlib.h>

using namespace std;

/**
*@brief Main GUI for performing system operations
*@author Xu Wang 250 748 901, Henry Chen 251 166 178, Artur Krupa, 251190423
**/

/**
*@brief Constructor for FunctionMain object
*@param *parent, username, password; these respectivly reprsent the previous login gui, and passed in username and password
*@author Xu Wang 250 748 901
*@returns nothing
**/
FunctionMain::FunctionMain(QWidget *parent, QString username, QString password) :
    QDialog(parent),
    ui(new Ui::FunctionMain)
{
    ui->setupUi(this);
    user = username;
    pass = password;
    DatabaseManager::instance()->setLabel(ui->label_3);
}

/**
*@brief Destructor for the FunctionMain object
*@author Xu Wang 250 748 901
*@param nothing
*@returns nothing
**/
FunctionMain::~FunctionMain()
{
    delete ui;
}

/**
*@brief Gets attendance data from all the courses that the professors teach from the database
*@param nothing
*@author Henry Chen 251 166 178, Artur Krupa 251190423
*@returns nothing
**/
void FunctionMain::on_Display_clicked() 
{
    string output;
    vector<string> okayCourses = DatabaseManager::instance()->CheckCourses(user.toStdString(), pass.toStdString());
    vector<vector<string>> students = DatabaseManager::instance()->ReadAllStudents();
    for (auto& vect : students) {
        if (std::find(okayCourses.begin(), okayCourses.end(), vect[0]) != okayCourses.end()) {
            for (auto& entry : vect) {
                output = output + entry + " ";
            }
            output = output + "\n";
        }
    }
    ui->label_3->setText(QString::fromStdString(output));
}

/**
*@brief Gets all the attandance data for a course that the professor teaches from the database
*@author Henry Chen 251 166 178, Artur Krupa 251190423
*@returns nothing
*@param nothing
**/
void FunctionMain::on_Display_3_clicked() 
{
    QString course;
    course=ui->lineEdit->text();
    string output;
    vector<string> okayCourses = DatabaseManager::instance()->CheckCourses(user.toStdString(), pass.toStdString());
    vector<vector<string>> students = DatabaseManager::instance()->ReadStudentCondition(course.toStdString(),1);
    for (auto& vect : students) {
        if (std::find(okayCourses.begin(), okayCourses.end(), vect[0]) != okayCourses.end()) {
            for (auto& entry : vect) {
                output = output + entry + " ";
            }
            output = output + "\n";
        }
    }
    ui->label_3->setText(QString::fromStdString(output));
    ui->lineEdit->clear();
}

/**
*@brief Gets all attendence data from the courses that the professor teaches on a particular day
*@author Henry Chen 251 166 178, Artur Krupa 251190423
*@returns nothing
*@param nothing
**/
void FunctionMain::on_Display_4_clicked() 
{
    int year;
    int month;
    int day;
    ui->dateEdit_3->date().getDate(&year, &month, &day);
    string date = to_string(year) + "/" + to_string(month) + "/" + to_string(day);
    string output;
    vector<string> okayCourses = DatabaseManager::instance()->CheckCourses(user.toStdString(), pass.toStdString());
    vector<vector<string>> students = DatabaseManager::instance()->ReadStudentCondition(date,2);
    for (auto& vect : students) {
        if (std::find(okayCourses.begin(), okayCourses.end(), vect[0]) != okayCourses.end()) {
            for (auto& entry : vect) {
                output = output + entry + " ";
            }
            output = output + "\n";
        }
    }
    ui->label_3->setText(QString::fromStdString(output));
}

/**
*@brief Gets all the devices stored in the database
*@author Henry Chen 251 166 178
*@returns nothing
*@param nothing
**/
void FunctionMain::on_Display_2_clicked() 
{
    string output;
    vector<vector<string>> devices = DatabaseManager::instance()->ReadAllDevice();
    for (const auto& vect : devices) {
        for (const auto& entry : vect) {
            output = output + entry + " ";
        }
        output = output + "\n";
    }
    ui->label_3->setText(QString::fromStdString(output));
}


/**
*@brief Allows user to edit the attendence status of a student
*@author Henry Chen 251 166 178, Artur Krupa 251190423
*@returns nothing
*@param nothing
**/
void FunctionMain::on_pushButton_2_clicked()
{
    QString course, studentID, status;
    course = ui->lineEdit_6->text();
    studentID = ui->lineEdit_7->text();

    int year;
    int month;
    int day;
    ui->dateEdit->date().getDate(&year, &month, &day);
    string date = to_string(year) + "/" + to_string(month) + "/" + to_string(day);

    status = ui->comboBox->currentText();
    vector<string> okayCourses = DatabaseManager::instance()->CheckCourses(user.toStdString(), pass.toStdString());
    if (std::find(okayCourses.begin(), okayCourses.end(), course.toStdString()) != okayCourses.end()) {
        if (status.toStdString() == "Present"){
            DatabaseManager::instance()->markPresent(course.toStdString(), studentID.toStdString(), date);
        }
        else if (status.toStdString() == "Late"){
            DatabaseManager::instance()->markLate(course.toStdString(), studentID.toStdString(), date);
        }
        else {
            DatabaseManager::instance()->markAbsent(course.toStdString(), studentID.toStdString(), date);
        }
    }
    else {
        ui->label_3->setText("You are not a professor who is in charge of the course that's represented by the ID you entered.\n");
    }

    ui->lineEdit_6->clear();
    ui->lineEdit_7->clear();
}


/**
*@brief Allows the user to modify the studentid of a device
*@author Henry Chen 251 166 178
*@returns nothing
*@param nothing
**/
void FunctionMain::on_pushButton_4_clicked() 
{
    QString deviceID, studentID;
    deviceID = ui->lineEdit_10->text();
    studentID = ui->lineEdit_11->text();
    DeviceRegister::instance()->ModifyDevice(studentID.toStdString(), deviceID.toStdString());
    ui->label_3->setText("Device Modified");
    ui->lineEdit_10->clear();
    ui->lineEdit_11->clear();
}


/**
*@brief Allows use to delete the attendance record for a student for a course on a particular day
*@author Henry Chen 251 166 178, Artur Krupa 251190423
*@returns nothing
*@param nothing
**/
void FunctionMain::on_pushButton_3_clicked()
{
    QString course, studentID;
    course = ui->lineEdit_12->text();
    studentID = ui->lineEdit_13->text();

    int year;
    int month;
    int day;
    ui->dateEdit_2->date().getDate(&year, &month, &day);
    string date = to_string(year) + "/" + to_string(month) + "/" + to_string(day);

    vector<string> okayCourses = DatabaseManager::instance()->CheckCourses(user.toStdString(), pass.toStdString());
    if (std::find(okayCourses.begin(), okayCourses.end(), course.toStdString()) != okayCourses.end()) {
        DatabaseManager::instance()->DeleteAttendence(studentID.toStdString(), course.toStdString(), date);
    }
    else {
        ui->label_3->setText("You are not a professor who is in charge of the course that's represented by the ID you entered.\n");
    }

    ui->lineEdit_12->clear();
    ui->lineEdit_13->clear();
}


/**
*@brief Allows user to select a device to delete
*@author Henry Chen 251 166 178
*@returns nothing
*@param nothing
**/
void FunctionMain::on_pushButton_5_clicked()
{
    QString deviceID;
    deviceID = ui->lineEdit_14->text();
    DeviceRegister::instance()->DeleteDevice(deviceID.toStdString());
    ui->label_3->setText("Device Deleted");
    ui->lineEdit_14->clear();
}


/**
*@brief Allow user to perform a non timed scan
*@author Henry Chen 251 166 178, Artur Krupa 251190423
*@returns nothing
*@param nothing
**/
void FunctionMain::on_pushButton_6_clicked() 
{
    QString course;
    course = ui->lineEdit_15->text();
    vector<string> okayCourses = DatabaseManager::instance()->CheckCourses(user.toStdString(), pass.toStdString());
    if (std::find(okayCourses.begin(), okayCourses.end(), course.toStdString()) != okayCourses.end()) {
        DatabaseManager::instance()->ScannerNoTime(course.toStdString());
    }
    else {
        ui->label_3->setText("You are not a professor who is in charge of the course that's represented by the ID you entered.\n");
    }

    ui->lineEdit_15->clear();
}

/**
*@brief Allow user to perform a timed scan
*@author Henry Chen 251 166 178, Artur Krupa 251190423
*@returns nothing
*@param nothing
**/
void FunctionMain::on_pushButton_8_clicked() 
{
    QString course;
    course = ui->lineEdit_18->text();

    time_t startT = ui->dateTimeEdit->dateTime().toSecsSinceEpoch();
    time_t endT = ui->dateTimeEdit_2->dateTime().toSecsSinceEpoch();

    vector<string> okayCourses = DatabaseManager::instance()->CheckCourses(user.toStdString(), pass.toStdString());
    if (std::find(okayCourses.begin(), okayCourses.end(), course.toStdString()) != okayCourses.end()) {
        DatabaseManager::instance()->ScannerTimed(course.toStdString(), startT, endT);
    }
    else {
        ui->label_3->setText("You are not a professor who is in charge of the course that's represented by the ID you entered.\n");
    }

    ui->dateEdit->clear();
    ui->dateEdit_2->clear();
    ui->lineEdit_18->clear();

}

/**
*@brief Allow user to regester a device by inputing the device ID and student ID
*@author Henry Chen 251 166 178
*@returns nothing
*@param nothing
**/
void FunctionMain::on_pushButton_7_clicked()
{
    QString deviceID, studentID;
    deviceID = ui->lineEdit_16->text();
    studentID = ui->lineEdit_17->text();
    DeviceRegister::instance()->StoreDeviceRegister(deviceID.toStdString(), studentID.toStdString());
    ui->label_3->setText("Device Registered");
    ui->lineEdit_16->clear();
    ui->lineEdit_17->clear();
}

