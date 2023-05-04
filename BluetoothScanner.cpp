#include "BluetoothScanner.h"

//BluetoothScanner.h - Header file for a class to scan for bluetooth devices

/**
*@brief Bluetooth Scanner class uses raspberry pi's bluetooth controller app hcitool to receive the bluetooth devices and put them into a string to be used by the scanenr class
*@author Artur Krupa 251190423
**/

using namespace std;

/**
*@brief constructor for the BluetoothScanner class
*@author Artur Krupa 251190423
*@param  no parameters 
*@return returns nothing
**/
BluetoothScanner::BluetoothScanner(){

}

/**
*@brief Destructor to delete the pointer and object to the BluetoothScanner object
*@author Artur Krupa 251190423
*@param  no parameters
*@return returns nothing
**/
BluetoothScanner::~BluetoothScanner(){
    delete(BluetoothScanner::scanner);
}

//Initialize our BluetoothScanner pointer to nothing initially
BluetoothScanner* BluetoothScanner::scanner = 0;

/**
*@brief getter method to create a new BluetoothScanner object if it does not exist
*@author Artur Krupa 251190423 
*@param  no parameters
*@return returns nothing
**/
BluetoothScanner* BluetoothScanner::getBluetoothScanner(){
    
    //If the getBluetoothScanner() method is called, check to see if the pointer points to a created BluetoothScanner object
    if (!BluetoothScanner::scanner){
        
        //If not, create a new BluetoothScanner object and have our pointer point to it
        BluetoothScanner::scanner = new BluetoothScanner();
    }

    //Return the pointer to our BluetoothScanner object
    return BluetoothScanner::scanner;
}
/**
*@brief function to run the scan by receiving the output from hcitool and store it in the output string variable
*@param  no parameters
*@return output - the string holding the output from hcitool
*@author Artur Krupa, 251190423
**/
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
