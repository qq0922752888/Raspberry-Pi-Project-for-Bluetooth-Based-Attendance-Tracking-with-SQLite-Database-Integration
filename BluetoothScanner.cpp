#include "BluetoothScanner.h"

/*BluetoothScanner.h - Header file for a class to scan for bluetooth devices
Created by: Artur Krupa, 251190423*/

using namespace std;

BluetoothScanner::BluetoothScanner(){

}

//Delete the pointer and object to the BluetoothScanner object
BluetoothScanner::~BluetoothScanner(){
    delete(BluetoothScanner::scanner);
}

//Initialize our BluetoothScanner pointer to nothing initially
BluetoothScanner* BluetoothScanner::scanner = 0;


BluetoothScanner* BluetoothScanner::getBluetoothScanner(){
    
    //If the getBluetoothScanner() method is called, check to see if the pointer points to a created BluetoothScanner object
    if (!BluetoothScanner::scanner){
        
        //If not, create a new BluetoothScanner object and have our pointer point to it
        BluetoothScanner::scanner = new BluetoothScanner();
    }

    //Return the pointer to our BluetoothScanner object
    return BluetoothScanner::scanner;
}

string BluetoothScanner::BluetoothScan(){
    
    //Create a char array buffer to store the output of the Raspberry Pi's bluetooth scan command
    char buffer[128];
    string output = "";

    //Open up a pipe to recieve the output of the Raspberry Pi's bluetooth controller app called hcitool, and ask it to perform a device scan
    FILE* pipe = popen("hcitool scan", "r");
    
    //If the program fails to run and give an output
    if (!pipe) {
        return NULL;
    }

    //While we have not read in all of the ouput of the Raspberry Pi's bluetooth command 
    while (!feof(pipe)) {

        //Read it in and store it in output
        if (fgets(buffer, 128, pipe) != NULL)
         output += buffer;
    }

    //Close the pipe we created
    pclose(pipe);

    //Return the Bluetooth MAC addresses we scanned
    return output;
}