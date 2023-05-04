/*
Author : Henry Chen 251 166 178
Description : SQLQuery is responsible for passing SQL query commands into the sqlite3 server.
Date : 2022-11-08
*/
#include "SQLQuery.h"
using namespace std;
SQLQuery* SQLQuery::Query = 0;
/*
Constructor for the class, which initlizes the name of the database (always "data.db")
*/
SQLQuery::SQLQuery() {
    DatabaseName = "data.db";
}

/*
Deconstructor for the class, which closes the connection between the sqlite3 server and this class
*/
SQLQuery::~SQLQuery() {
    sqlite3_close(Database);
}
/*
Function name : instance	
Description : this class initlizes the classes pointer to itself if unitilized; Otherwise, it returns it. 
parameter description :  no parameters
return description : instance of the class if none has been created
*/
SQLQuery* SQLQuery::instance() {
    if (!SQLQuery::Query) {
        SQLQuery::Query = new SQLQuery();
    }
    return Query;
}
/*
Function name : Exec
Description : this class passes sql queries to the sqlite3 server that are related to writing to tables, insertting to tables, updating tables, or deleting table entries.
parameter description :  a string variable that represents a sql query
return description : returns nothing
*/
void SQLQuery::Exec(std::string sqlCommand) {
    char* errMsg;
    int programStatus;
    programStatus = sqlite3_exec(Database, sqlCommand.c_str(), NULL, 0, &errMsg);
    if (programStatus == 19) {
        cerr << "Operation would would have resulted in duplicate primary key and/or a duplicate entry in a table. Operation Cancled: " + sqlCommand << endl;
    }
    else if (programStatus != SQLITE_OK) { 
        cerr << "Error writing, updating, or deleting a table. Canceling Operation: " + sqlCommand << endl;
        cerr << programStatus << endl;
    }
}
/*
Function name : ReadMany
Description : this class passes sql queries to the sqlite3 server that are related to selecting two or more entries from a table
parameter description :  a string variable that represents a sql query
return description : a vector that holds vectors. The vectors held in the vector each induvidually hold multiple strings representing the data in a row that was selected from a table
*/
vector <vector<string>> SQLQuery::ReadMany(std::string sqlCommand) {
    vector <vector<string>> container;
    vector<string> rowEntry;
    int programStatus;
    int varNum;
    sqlite3_stmt* handle;
    const char* UNUSED;
    programStatus = sqlite3_prepare(Database, sqlCommand.c_str(), sqlCommand.size(), &handle, &UNUSED);
    if (programStatus != SQLITE_OK) {
        cerr << "Error with preparing table for reading. Canceling Operation: " + sqlCommand << endl;
        cerr << programStatus << endl;
    }
    programStatus = sqlite3_step(handle);
    varNum = sqlite3_data_count(handle);

    if (programStatus == SQLITE_DONE) {
        return container;
    }

    if (programStatus != SQLITE_ROW) {
        cerr << "Error with reading table. Canceling Operation: " + sqlCommand << endl;
        cerr << programStatus << endl;
    }
    while (programStatus != SQLITE_DONE) {
        for (int x = 0; x < varNum; x++) {
            string columunEntry = reinterpret_cast<const char*>(sqlite3_column_text(handle, x));
            rowEntry.push_back(columunEntry);
        }
        container.push_back(rowEntry);
        rowEntry.clear();
    
        programStatus = sqlite3_step(handle);
        if (programStatus != SQLITE_ROW && programStatus != SQLITE_DONE) {
            cerr << "Error with reading table. Canceling Operation: " + sqlCommand << endl;
            cerr << programStatus << endl;
        }
    }

    programStatus = sqlite3_finalize(handle); 

    return container;
}
/*
Function name : Readone
Description : this class passes sql queries to the sqlite3 server that are related to selecting one entry from a table
parameter description :  a string variable that represents a sql query
return description : a vector that holds strings. The each of the strings in the vector represents a part of the data from the row that was selected from the table
*/
vector<string> SQLQuery::ReadOne(std::string sqlCommand) {
    vector<string> rowEntry;
    int programStatus;
    int varNum;
    sqlite3_stmt* handle;
    const char* UNUSED;
    programStatus = sqlite3_prepare(Database, sqlCommand.c_str(), sqlCommand.size(), &handle, &UNUSED);
    if (programStatus != SQLITE_OK) {
        cerr << "Error with preparing table for reading. Canceling Operation: " + sqlCommand << endl;
        cerr << programStatus << endl;
    }
    programStatus = sqlite3_step(handle);
    varNum = sqlite3_data_count(handle);

    if (programStatus == SQLITE_DONE) {
        return rowEntry;
    }

    if (programStatus != SQLITE_ROW) {
        cerr << "Error with reading table. Canceling Operation: " + sqlCommand << endl;
        cerr << programStatus << endl;
    }

        for (int x = 0; x < varNum; x++) {
            string columunEntry = reinterpret_cast<const char*>(sqlite3_column_text(handle, x));
            rowEntry.push_back(columunEntry);
        }

        if (programStatus != SQLITE_ROW && programStatus != SQLITE_DONE) {
            cerr << "Error with reading table. Canceling Operation: " +  sqlCommand << endl;
            cerr << programStatus << endl;
        }
    

    programStatus = sqlite3_finalize(handle);

    return rowEntry;
}
/*
Function name : createTable
Description : this class passes sql queries to the sqlite3 server that are related to creating a table
parameter description :  a string variable that represents a sql query
return description : returns nothing
*/
void SQLQuery::createTable(std::string sqlCommand) {
    char* errMsg;
    int programStatus;
    programStatus = sqlite3_open(DatabaseName.c_str(), &Database);
    if (programStatus != SQLITE_OK) { 
        cerr << "Error opening the database. Cancling Operation:" + sqlCommand << endl;
        cerr << programStatus << endl;
    }

    programStatus = sqlite3_exec(Database, sqlCommand.c_str(), NULL, 0, &errMsg);
    
    if (programStatus != SQLITE_OK) {
        cerr << "Error creating table. Cancling Operation:" + sqlCommand << endl;
        cerr << programStatus << endl;
    }

}
