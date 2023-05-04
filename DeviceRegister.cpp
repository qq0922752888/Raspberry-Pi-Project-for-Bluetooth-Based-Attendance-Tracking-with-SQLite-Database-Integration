/**
*@author : Tsung-Ying,Tsai 251 262 078
*@brief : DeviceRegister class sign up devices belonged to the student to the Database Tables.  This class as well offers modify and delete features to current existing advices.
**/

using namespace std; //delete this later
#include "DeviceRegister.h"
DeviceRegister* DeviceRegister::Register = 0;

/**
*@brief Constructor for DeviceRegister class
*@author : Tsung-Ying,Tsai 251 262 078
*@param  no parameters
*@returns nothing
**/
DeviceRegister::DeviceRegister() {

}

/**
*@brief destructor for DeviceRegister class
*@author : Tsung-Ying,Tsai 251 262 078
*@param  no parameters
*@returns nothing
**/
DeviceRegister::~DeviceRegister() {

}

/**	
*@brief Following the singleton design pattern, this class will create only one object in the lifetime of the program
*@return instance of the class if none has been created
*@param  no parameters
*@author : Tsung-Ying,Tsai 251 262 078
**/

DeviceRegister* DeviceRegister::instance() {
    if (!DeviceRegister::Register) {
        DeviceRegister::Register = new DeviceRegister();
    }
    return Register;
}


/**
*@brief Given student's deviceID and their student ID, write into the database of device table
*@param DeviceID, StudentID - DeviceID: The Device identification string belonged to a student(s), StudentID: The Student identification string unique to each student.
*@author : Tsung-Ying Tsai 251 262 078
*@return returns nothing
**/
void DeviceRegister::StoreDeviceRegister(string DeviceID, string StudentID){
    DatabaseManager::instance()->WriteToDevice(DeviceID, StudentID);
}

/**	
*@brief Given student's deviceID and their student ID, update information the existing device in the device table if exists. Otherwise do nothing.
*@param DeviceID, StudentID - DeviceID: The Device identification string belonged to a student(s), StudentID: The Student identification string unique to each student.
*@author : Tsung-Ying Tsai 251 262 078
*@return returns nothing
**/
void DeviceRegister::ModifyDevice(string StudentID, string DeviceID){
    DatabaseManager::instance()->ModifyDeviceStudentNum(StudentID, DeviceID);
}


/**
*@brief Given student's deviceID, delete  device in the device table if exists.  Otherwise do nothing.
*@param DeviceID: The Device identification string belonged to a student(s)
*@author : Tsung-Ying Tsai 251 262 078
*@return returns nothing
**/
void DeviceRegister::DeleteDevice(string DeviceID){
    DatabaseManager::instance()->DeleteDevice(DeviceID);
}











