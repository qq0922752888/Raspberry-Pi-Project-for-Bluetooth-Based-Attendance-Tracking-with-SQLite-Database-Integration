/*
Author : Tsung-Ying,Tsai 251 262 078
Description : DeviceRegister class sign up devices belonged to the student to the Database Tables.  This class as well offers modify and delete features to current existing advices.
Date : 2022-11-05
*/

#include <string>
#include <vector>
#include "DatabaseManager.h"

class DeviceRegister{
    private:
        static DeviceRegister* Register;

    protected:
        DeviceRegister();

    public:
        ~DeviceRegister();
        static DeviceRegister* instance();
        void StoreDeviceRegister(std::string DeviceID, std::string StudentID);
        void ModifyDevice(std::string StudentID, std::string DeviceID);
        void DeleteDevice(std::string DeviceID);

};
