/*
Author: Uzair Salim 251 143 778
Description: Singleton class for authenticating user's login attempt
Last Edit: 2022-11-07
*/
#include "Login.h"
#include "DatabaseManager.h"
using namespace std;
//private contstructor
Login::Login(){
    
}

Login* Login::loginPointer = NULL;

/*
Function name : instance	
Description : Checks if an instance exists and returns it, otherwise it will create an instance and return it
parameter description :  no parameters
return description : instance of the class if it has not yet been created
*/
Login* Login::instance() {
    if (Login::loginPointer == NULL) {
        Login::loginPointer = new Login();
    }
    return loginPointer;
}

//checks if username and password match any credentials in the professor database
 bool Login::AuthenticateUser(string username, string password){
     return DatabaseManager::instance()->AuthenticateUser(username, password);
 }




