#include "Scanner.h"

using namespace std;

/*Scanner.cpp: A Scanner class that parses the data retrieved from BluetoothScanner
Created by: Artur Krupa, 251190423*/

//Initialize our Scanner pointer to not point to anything at the begining
Scanner* Scanner::scanner = 0;

//When we create a Scanner object, we initialize our BluetoothScanner pointer to point to the BluetoothScanner singleton object
Scanner::Scanner(){
    this->bluetoothScanner = BluetoothScanner::getBluetoothScanner();
}

//when we are finished with scanner, we delete both Scanner and BluetoothScanner as they are no longer needed anymore
Scanner::~Scanner(){
    delete(bluetoothScanner);
    delete(scanner);
}

//If the Scanner object is not initialized, initialize it and then return the pointer to the Scanner object
Scanner* Scanner::getScanner(){
    if (!scanner){
        scanner = new Scanner();
    }
    return scanner;
}

//scan returns the bluetooth MAC addresses of the devices that we found
vector<string> Scanner::scan(){

    //Get the data from BluetoothScan and store it in scannedDevices
    string scannedDevices = bluetoothScanner->BluetoothScan();

    vector<string> devices;

    size_t pos = 0;
    size_t posDeviceIdStart = 0;
    string end = "\n";
    string temp;

    //While we are not at the end of the string scannedDevices, strip all unnessasry data in the string and add only the MAC addresses of the devices to devices
    while ((pos = scannedDevices.find(end)) != std::string::npos){
        temp = scannedDevices.substr(0, pos);
        posDeviceIdStart = temp.find("\t");

        //If the line read does not follow the correct format, ignore it and move to the next line
        if (posDeviceIdStart == std::string::npos){
            scannedDevices.erase(0, pos+end.length());
            continue;
        }

        devices.push_back(temp.substr(posDeviceIdStart+1, posDeviceIdStart+17));
        scannedDevices.erase(0, pos+end.length());
    }

    //Return the MAC addresses of the scanned bluetooth devices
    return devices;
}

// //scan() performs a bluetooth scan at desired times and dtermines if a device is present or if it arrived late
// vector<ScannedDevice> Scanner::scan(time_t timeTillStart, time_t timeTillLate){
    
//     //Wait until we reached the desired time to perform the first scan
//     sleep(difftime(timeTillStart, time(0)));

//     cout <<"Taking first attendence scan" << endl;
    
//     //Scan the devices currently present and store them in devices
//     vector<ScannedDevice> devices = this->scan();

//     cout << "Completed first attendence scan" << endl;

//     //Wait until we reached the desired time to perform the second scan
//     sleep(difftime(timeTillLate, time(0)));

//     cout << "Taking late attendence scan" << endl;

//     //Scan the devices that are now all present
//     vector<ScannedDevice> temp = this->scan();

//     bool contains;

//     //Check to see if the devices in temp was not scanned into devices, if it is not, it is marked as late, and added to devices
//     for (int i = 0; i < temp.size(); i++){
//         contains = false;
//         for (int j = 0; j < devices.size() && !contains; j++){
//             if (strcmp(temp[i].getDeviceID().c_str(), devices[j].getDeviceID().c_str()) == 0){
//                 contains = true;
//             }
//         }
//         if(!contains){
//             temp[i].setLateStatus(true);
//             devices.push_back(temp[i]);
//         }
//     }

//     //Return all scanned present and late devices
//     return devices;

// }