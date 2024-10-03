#include <iostream>
#include "headerFiles/DataBaseManager.h"
using namespace std ;

DataBaseManager startDB(){
    string dbName = "DB.db"; // Database File Name
    DataBaseManager cursor(dbName);

    // Open connection with database
    cursor.open();

    // Build All Tables
    cursor.buildTables();

    return cursor;
}