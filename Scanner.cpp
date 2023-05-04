#include "Scanner.h"

using namespace std;

/**
*@brief A Scanner class that parses the data retrieved from BluetoothScanner
*@author Artur Krupa, 251190423
**/

//Initialize our Scanner pointer to not point to anything at the begining
Scanner* Scanner::scanner = 0;

/**
*@brief Constructor to initialize our BluetoothScanner pointer to point to the BluetoothScanner singleton object when creating a Scanner object
*@author Artur Krupa, 251190423
*@return nothing
*@param nothing
**/
Scanner::Scanner(){
    this->bluetoothScanner = BluetoothScanner::getBluetoothScanner();
}

/**
*@brief Destructor to delete both Scanner and BluetoothScanner as they are no longer needed anymore when we're done with Scanner
*@author Artur Krupa, 251190423
*@return nothing
*@param nothing
**/
Scanner::~Scanner(){
    delete(bluetoothScanner);
    delete(scanner);
}
/**
*@brief If the Scanner object is not initialized, initialize it and then return the pointer to the Scanner object
*@return scanner - The current instance of the Scanner class
*@author Artur Krupa, 251190423
*@param nothing
**/
Scanner* Scanner::getScanner(){
    if (!scanner){
        scanner = new Scanner();
    }
    return scanner;
}
/**
*@brief Scan returns the bluetooth MAC addresses of the devices that we found
*@return devices - the MAC addresses of the scanned bluetooth devices
*@author Artur Krupa, 251190423
*@param nothing
**/
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
