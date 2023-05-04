/**
*@author : Henry Chen 251 166 178
*@brief SQLQuery is responsible for passing SQL query commands into the sqlite3 server.
**/
#include "SQLQuery.h"
using namespace std;
SQLQuery* SQLQuery::Query = 0;
/**
*@brief Constructor for the class, which initlizes the name of the database (always "data.db")
*@author : Henry Chen 251 166 178
*@param nothing
*@return nothing
**/
SQLQuery::SQLQuery() {
    DatabaseName = "data.db";
}

/**
*@brief Deconstructor for the class, which closes the connection between the sqlite3 server and this class
*@author : Henry Chen 251 166 178
*@param nothing
*@return nothing
**/
SQLQuery::~SQLQuery() {
    sqlite3_close(Database);
}
/**
Function name : instance	
*@brief this function initlizes the classes pointer to itself if unitilized; Otherwise, it returns it. 
*@return Query - instance of the class if none has been created
*@author : Henry Chen 251 166 178
*@param nothing
**/
SQLQuery* SQLQuery::instance() {
    if (!SQLQuery::Query) {
        SQLQuery::Query = new SQLQuery();
    }
    return Query;
}
/**
Function name : Exec
*@brief This class passes sql queries to the sqlite3 server that are related to writing to tables, insertting to tables, updating tables, or deleting table entries.
*@parameter sqlCommand - a string variable that represents a sql query
*@author : Henry Chen 251 166 178
*@return nothing
**/
void SQLQuery::Exec(std::string sqlCommand) {
    char* errMsg;
    int programStatus;
    programStatus = sqlite3_exec(Database, sqlCommand.c_str(), NULL, 0, &errMsg);

}
/**
Function name : ReadMany
*@brief this class passes sql queries to the sqlite3 server that are related to selecting two or more entries from a table
*@param sqlCommand - a string variable that represents a sql query
*@return container - a vector that holds vectors. The vectors held in the vector each induvidually hold multiple strings representing the data in a row that was selected from a table
*@author : Henry Chen 251 166 178
**/
vector <vector<string>> SQLQuery::ReadMany(std::string sqlCommand) {
    vector <vector<string>> container;
    vector<string> rowEntry;
    int programStatus;
    int varNum;
    sqlite3_stmt* handle;
    const char* UNUSED;
    programStatus = sqlite3_prepare(Database, sqlCommand.c_str(), sqlCommand.size(), &handle, &UNUSED);

    programStatus = sqlite3_step(handle);
    varNum = sqlite3_data_count(handle);

    if (programStatus == SQLITE_DONE) {
        return container;
    }

    while (programStatus != SQLITE_DONE) {
        for (int x = 0; x < varNum; x++) {
            string columunEntry = reinterpret_cast<const char*>(sqlite3_column_text(handle, x));
            rowEntry.push_back(columunEntry);
        }
        container.push_back(rowEntry);
        rowEntry.clear();
    
        programStatus = sqlite3_step(handle);

    }

    programStatus = sqlite3_finalize(handle); 

    return container;
}
/**
Function name : Readone
*@brief This function passes sql queries to the sqlite3 server that are related to selecting one entry from a table
*@param sqlCommand - a string variable that represents a sql query
*@return rowEntry - a vector that holds strings. The each of the strings in the vector represents a part of the data from the row that was selected from the table
*@author : Henry Chen 251 166 178
**/
vector<string> SQLQuery::ReadOne(std::string sqlCommand) {
    vector<string> rowEntry;
    int programStatus;
    int varNum;
    sqlite3_stmt* handle;
    const char* UNUSED;
    programStatus = sqlite3_prepare(Database, sqlCommand.c_str(), sqlCommand.size(), &handle, &UNUSED);

    programStatus = sqlite3_step(handle);
    varNum = sqlite3_data_count(handle);

    if (programStatus == SQLITE_DONE) {
        return rowEntry;
    }

        for (int x = 0; x < varNum; x++) {
            string columunEntry = reinterpret_cast<const char*>(sqlite3_column_text(handle, x));
            rowEntry.push_back(columunEntry);
        }

    programStatus = sqlite3_finalize(handle);

    return rowEntry;
}
/**
*@brief This class passes sql queries to the sqlite3 server that are related to creating a table
*@param sqlCommand - a string variable that represents a sql query
*@author : Henry Chen 251 166 178
*@return nothing
**/
void SQLQuery::createTable(std::string sqlCommand) {
    char* errMsg;
    int programStatus;
    programStatus = sqlite3_open(DatabaseName.c_str(), &Database);

    programStatus = sqlite3_exec(Database, sqlCommand.c_str(), NULL, 0, &errMsg);

}
