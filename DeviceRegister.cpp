/*
Author : Tsung-Ying,Tsai 251 262 078
Description : DeviceRegister class sign up devices belonged to the student to the Database Tables.  This class as well offers modify and delete features to current existing advices.
Date : 2022-11-05
*/

using namespace std; //delete this later
#include "DeviceRegister.h"
#include "DatabaseManager.h"
DeviceRegister* DeviceRegister::Register = 0;

//Class Constructor
DeviceRegister::DeviceRegister() {

}
//Class destructor
DeviceRegister::~DeviceRegister() {

}


/*
Function name : instance	
Description : Following the singleton design pattern, this class will create only one object in the lifetime of the program
parameter description :  no parameters
return description : instance of the class if none has been created
*/

DeviceRegister* DeviceRegister::instance() {
    if (!DeviceRegister::Register) {
        DeviceRegister::Register = new DeviceRegister();
    }
    return Register;
}


/*
Function name : StoreDeviceRegister	
Description : Given student's deviceID and their student ID, write into the database of device table
parameter description :  DeviceID: The Device identification string belonged to a student(s), StudentID: The Student identification string unique to each student.
return description : void
*/
void DeviceRegister::StoreDeviceRegister(string DeviceID, string StudentID){
    DatabaseManager::instance()->WriteToDevice(DeviceID, StudentID);
}

/*
Function name : ModifyDevice	
Description : Given student's deviceID and their student ID, update information the existing device in the device table if exists. Otherwise do nothing.
parameter description :  DeviceID: The Device identification string belonged to a student(s), StudentID: The Student identification string unique to each student.
return description : void
*/
void DeviceRegister::ModifyDevice(string StudentID, string DeviceID){
    DatabaseManager::instance()->ModifyDeviceStudentNum(StudentID, DeviceID);
}


/*
Function name : DeleteDevice	
Description : Given student's deviceID, delete  device in the device table if exists.  Otherwise do nothing.
parameter description :  DeviceID: The Device identification string belonged to a student(s)
return description : void
*/
void DeviceRegister::DeleteDevice(string DeviceID){
    DatabaseManager::instance()->DeleteDevice(DeviceID);
}











