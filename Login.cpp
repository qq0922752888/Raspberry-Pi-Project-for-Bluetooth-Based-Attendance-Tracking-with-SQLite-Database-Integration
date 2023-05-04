/**
*@author: Uzair Salim 251 143 778
*@brief Singleton class for authenticating user's login attempt
**/
#include "Login.h"
using namespace std;
/**
*@brief private contstructor
*@author Uzair Salim 251 143 778
*@param nothing
*@returns nothing
**/
Login::Login(){
    
}
/**
*@brief destructor
*@author Uzair Salim 251 143 778
*@param nothing
*@returns nothing
**/
Login::~Login(){
}
Login* Login::loginPointer = NULL;

/**
Function name : instance	
*@brief Checks if an instance exists and returns it, otherwise it will create an instance and return it
*@return loginPointer - instance of the class if it has not yet been created
*@author Uzair Salim 251 143 778
*@param nothing
**/
Login* Login::instance() {
    if (Login::loginPointer == NULL) {
        Login::loginPointer = new Login();
    }
    return loginPointer;
}

/**
*@brief checks if username and password match any credentials in the professor database
*@return true if username and password match credentials in the professor table, false elsewise
*@author Uzair Salim 251 143 778
*@param nothing
**/
 bool Login::AuthenticateUser(string username, string password){
     return DatabaseManager::instance()->AuthenticateUser(username, password);
 }




