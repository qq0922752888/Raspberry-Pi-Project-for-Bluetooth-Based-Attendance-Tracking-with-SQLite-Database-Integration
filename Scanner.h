#pragma once
#include <vector>
#include <ctime>
#include <unistd.h>
#include <string.h>
#include "BluetoothScanner.h"

/*Scanner.h: A header file for a Scanner class that parses the data retrieved from BluetoothScanner
Created by: Artur Krupa, 251190423*/

class Scanner
{
private:

    //Store a pointer to the BluetoothScanner object to use for scanning
    BluetoothScanner* bluetoothScanner;
    
    //Store a private pointer to our scanner object to enforce the signleton design pattern
    static Scanner* scanner;
    
    //Private constructor for scanner to enforce the signleton design pattern
    Scanner();
public:

    //Deconstructor to destroy our Scanner object and pointer, and free up the used memory
    ~Scanner();

    //Accessor method to retrieve our single instance of the Scanner object
    static Scanner* getScanner();

    //Method to scan for bluetooth devices and return their MAC addresses
    std::vector<std::string> scan();
};
