/*
Author : Henry Chen 251 166 178
Description : SQLQuery is responsible for passing SQL query commands into the sqlite3 server.
Date : 2022-11-08
*/
#pragma once
#include <iostream>
#include <sqlite3.h>
#include <vector>

class SQLQuery {
private:
    sqlite3* Database;
    static SQLQuery* Query;
    std::string DatabaseName;
protected:
    SQLQuery();
public:
    ~SQLQuery();
    static SQLQuery* instance();
    void Exec(std::string sqlCommand);
    std::vector <std::vector<std::string>> ReadMany(std::string sqlCommand);
    std::vector<std::string> ReadOne(std::string sqlCommand);
    void createTable(std::string sqlCommand);
};
