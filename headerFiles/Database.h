//
// Created by yousef on 10/2/2024.
//

#ifndef FINAL_PROJECT_DATABASE_H
#define FINAL_PROJECT_DATABASE_H

#pragma once
#include "../sqlite/sqlite3.h"
#include <string>
#include <iostream>
using namespace std;

class DataBase
{
private:
    sqlite3* db;          // SQLite database connection
    string dbName;        // Database file name

public:
    // Constructor: takes the name of the database file
    DataBase(const string& name) : db(nullptr), dbName(name) {}

    // Destructor: ensures the database is closed
    ~DataBase() {
        close();
    }

    // Function to open the database
    bool open() {
        int connection = sqlite3_open(dbName.c_str(), &db);
        if (connection != SQLITE_OK) {
            cout << "Failed to connect to the database: " << sqlite3_errmsg(db) << endl;
            return false;
        }
        cout << "Database opened successfully." << endl;
        return true;
    }

    // Function to close the database
    void close() {
        if (db) {
            sqlite3_close(db);
            db = nullptr;
            cout << "Database closed successfully." << endl;
        }
    }

    // Function to execute an SQL query
    bool execute(const string& query) {
        char* error = nullptr;
        int connection = sqlite3_exec(db, query.c_str(), nullptr, nullptr, &error);

        if (connection != SQLITE_OK) {
            cout << "SQL error: " << error << endl;
            sqlite3_free(error);
            return false;
        }
        return true;
    }

    // Function to create the clients table
    bool createClientsTable() {
        const string sql = "CREATE TABLE IF NOT EXISTS clients("
                           "id INTEGER PRIMARY KEY AUTOINCREMENT, "
                           "name TEXT NOT NULL, "
                           "password TEXT NOT NULL, "
                           "balance FLOAT(10,3) NOT NULL);";

        if (execute(sql)) {
            cout << "Clients table created successfully." << endl;
            return true;
        }
        return false;
    }

    // Function to create the employees table
    bool createEmployeeTable() {
        const string sql = "CREATE TABLE IF NOT EXISTS employees("
                           "id INTEGER PRIMARY KEY AUTOINCREMENT, "
                           "name TEXT NOT NULL, "
                           "password TEXT NOT NULL, "
                           "salary FLOAT(10,3) NOT NULL);";

        if (execute(sql)) {
            cout << "Employees table created successfully." << endl;
            return true;
        }
        return false;
    }

    // Function to create the admins table
    bool createAdminsTable() {
        const string sql = "CREATE TABLE IF NOT EXISTS admins("
                           "id INTEGER PRIMARY KEY AUTOINCREMENT, "
                           "name TEXT NOT NULL, "
                           "password TEXT NOT NULL, "
                           "salary FLOAT(10,3) NOT NULL);";

        if (execute(sql)) {
            cout << "Admins table created successfully." << endl;
            return true;
        }
        return false;
    }

    // Function to build all tables
    bool buildTables() {
        createClientsTable();
        createEmployeeTable();
        createAdminsTable();
        return true;
    }
};


#endif //FINAL_PROJECT_DATABASE_H
