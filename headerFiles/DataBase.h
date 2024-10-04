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
    sqlite3* db;
    string dbName;

public:
    DataBase(const string& name) : db(nullptr), dbName(name) {}

    ~DataBase() {
        close();
    }

    bool open() {
        int connection = sqlite3_open(dbName.c_str(), &db);
        if (connection != SQLITE_OK) {
            cout << "Failed to connect to the database: " << sqlite3_errmsg(db) << endl;
            return false;
        }
        return true;
    }

    sqlite3 *getDb() const {
        return db;
    }

    void close() {
        if (db) {
            sqlite3_close(db);
            db = nullptr;
        }
    }

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

    bool createClientsTable() {
        const string sql = "CREATE TABLE IF NOT EXISTS clients("
                           "id INTEGER PRIMARY KEY AUTOINCREMENT, "
                           "name TEXT NOT NULL, "
                           "password TEXT NOT NULL, "
                           "balance FLOAT(10,3) NOT NULL);";

        if (execute(sql)) {
            return true;
        }
        return false;
    }

    bool createEmployeeTable() {
        const string sql = "CREATE TABLE IF NOT EXISTS employees("
                           "id INTEGER PRIMARY KEY AUTOINCREMENT, "
                           "name TEXT NOT NULL, "
                           "password TEXT NOT NULL, "
                           "salary FLOAT(10,3) NOT NULL);";

        if (execute(sql)) {
            return true;
        }
        return false;
    }

    bool createAdminsTable() {
        const string sql = "CREATE TABLE IF NOT EXISTS admins("
                           "id INTEGER PRIMARY KEY AUTOINCREMENT, "
                           "name TEXT NOT NULL, "
                           "password TEXT NOT NULL, "
                           "salary FLOAT(10,3) NOT NULL);";

        if (execute(sql)) {
            return true;
        }
        return false;
    }

    bool buildTables() {
        createClientsTable();
        createEmployeeTable();
        createAdminsTable();
        return true;
    }
};


#endif //FINAL_PROJECT_DATABASE_H
