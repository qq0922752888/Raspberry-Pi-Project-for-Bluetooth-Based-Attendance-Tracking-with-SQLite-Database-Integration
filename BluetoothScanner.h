#pragma once
#include <iostream>
#include <stdexcept>
#include <stdio.h>
#include <string>

/*BluetoothScanner.h - Header file for a class to scan for bluetooth device MAC addresses from a Raspberry Pi
Created by: Artur Krupa, 251190423*/

class BluetoothScanner{
    private:

        //Private pointer to our BluetoothScanner object to enforce singleton design pattern
        static BluetoothScanner* scanner;
        
        //Private constructor to enforce singleton design pattern
        BluetoothScanner();
    public:

        //Deconstructor for the BluetoothScanner object
        ~BluetoothScanner();

        //Static getBluetoothScanner() method to return our single instance of our BluetoothScanner object
        static BluetoothScanner *getBluetoothScanner();
        
        //BluetoothScan performs the bluetooth device scan and returns found bluetooth device MAC addresses
        std::string BluetoothScan();
};