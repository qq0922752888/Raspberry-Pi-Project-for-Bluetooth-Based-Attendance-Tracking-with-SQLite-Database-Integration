/*
Author: Uzair Salim 251 143 778
Description: Header file for login class authenticating user's login attempt
Last Edit: 2022-11-07
*/
#pragma once
#include <string>
#include <iostream>
#include <string>
#include "DatabaseManager.h"
class Login {
private:
    static Login* loginPointer;
protected:
    Login();
public:
    ~Login();
    static Login* instance();
    bool AuthenticateUser(std::string username, std::string password);
    
};
