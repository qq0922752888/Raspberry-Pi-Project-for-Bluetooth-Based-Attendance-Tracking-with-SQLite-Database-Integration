/*
Author : Xu Wang 250 748 901, Henry Chen 251 166 178
Description : DatabaseManager is responsible for formatting SQL queries so that the SQLQuery class can read or write into database
Date : 2022-10-31
*/
#pragma once
#include <string>
#include <iostream>
#include <ctime>
#include <vector>
#include <QLabel>
#include "SQLQuery.h"
#include "Scanner.h"
class DatabaseManager
{
private:
    static DatabaseManager *Manager;
    QLabel *textBox;

protected:
    DatabaseManager();

public:
    time_t now;
    tm* localTime;
    ~DatabaseManager();
	static DatabaseManager *instance();
    std::vector<std::vector<std::string>> ReadAllStudents();
    std::vector<std::vector<std::string>> ReadSomeStudents(std::vector<std::string> input, std::string Table);
    std::vector<std::string> CheckCourses(std::string username, std::string password);
    std::vector<std::vector<std::string>> WhoTakesWhat();
    std::vector<std::vector<std::string>> ReadAllDevice();
    std::vector<std::vector<std::string>> ReadStudentCondition(std::string input , int mode);
    std::vector<std::string> GetDeviceStudent(std::string DID);
    bool AuthenticateUser(std::string username, std::string password);
    void ScannerNoTime(std::string CID);
    void ScannerTimed(std::string CID, time_t timeTillStart, time_t timeTillLate);
    void WriteToAttendence(std::string courseId, std::string studentNumber, std::string date, std::string presence);
    void WriteToDevice(std::string ID, std::string Device);
    void WriteToProfessor(std::string ID, std::string Username, std::string Password);
    void WriteToStudent(std::string ID, std::string FName, std::string LName);
    void WriteToCourse(std::string CID, std::string CName, std::string PID);
    void WriteToTakes(std::string CID, std::string CName);
    void markPresent(std::string CourseID, std::string studentID, std::string date);
    void markLate(std::string CourseID, std::string studentID, std::string date);
    void markAbsent(std::string CourseID, std::string studentID, std::string date);
    void ModifyDeviceStudentNum(std::string SID, std::string DID);
    void DeleteAttendence(std::string SID, std::string CID, std::string Date);
    void DeleteDevice(std::string CID);
    void createTable(std::string name);
    void setLabel(QLabel *label);
};
