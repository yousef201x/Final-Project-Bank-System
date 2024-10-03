//
// Created by yousef on 10/2/2024.
//

#ifndef FINAL_PROJECT_DATABASEMANAGER_H
#define FINAL_PROJECT_DATABASEMANAGER_H

#pragma once
#include "DataBase.h"
#include "Client.h"
#include "Admin.h"
#include "Employee.h"
#include "../sqlite/sqlite3.h"

using namespace std;

class DataBaseManager : public DataBase
{
public:
    // Constructor: takes the name of the database file
    DataBaseManager(const string& name) : DataBase(name) {}

    bool insertTo(const string& table,Client& client) {
        string name = client.getName();
        string password = client.getPassword();
        double balance = client.getBalance();

        const string sql = "INSERT INTO "+table+" (name, password, balance) VALUES ('"
                                + name + "', '" + password + "', " + to_string(balance) + ");";

        if(execute(sql)){
            cout << "Client created successfully." << endl;
            return true;
        }else{
            cout << "An error occurred while creating new Client." << endl;
            return false;
        }
    }

    bool insertTo(const string table,Employee& employee) {
        string name = employee.getName();
        string password = employee.getPassword();
        double salary = employee.getSalary();

        const string sql = "INSERT INTO "+table+" (name, password, salary) VALUES ('"
                           + name + "', '" + password + "', " + to_string(salary) + ");";

        if(execute(sql)){
            cout << "Employee created successfully." << endl;
            return true;
        }else{
            cout << "An error occurred while creating new Employee." << endl;
            return false;
        }
    }

    bool insertTo(const string table,Admin& admin) {
        string name = admin.getName();
        string password = admin.getPassword();
        double salary = admin.getSalary();

        const string sql = "INSERT INTO "+table+" (name, password, salary) VALUES ('"
                           + name + "', '" + password + "', " + to_string(salary) + ");";

        if(execute(sql)){
            cout << "Admin created successfully." << endl;
            return true;
        }else{
            cout << "An error occurred while creating new Admin." << endl;
            return false;
        }
    }


    void all(const string& table) {
        sqlite3_stmt *stmt;
        const string sql = "SELECT * FROM " + table;

        int rc = sqlite3_prepare_v2(getDb(), sql.c_str(), -1, &stmt, nullptr);

        if (sqlite3_step(stmt) == SQLITE_ROW) {
            do {
                cout << "ID: " << sqlite3_column_text(stmt, 0) << std::endl;
                cout << "NAME: " << sqlite3_column_text(stmt, 1) << std::endl;
                cout << (table == "clients" ? "BALANCE: " : "SALARY: ")
                << sqlite3_column_text(stmt, 3) << "$" << endl << endl;
            } while (sqlite3_step(stmt) == SQLITE_ROW);
        } else {
            cout << "No Data found." << std::endl;
        }
    }

    void removeAll(const string& table){
        const string sql = "DELETE FROM "+table;

        if(execute(sql)){
            cout << table << " cleared."<< endl;
            return;
        }else{
            cout << "An error occurred while deleting data." << endl;
            return;
        }
    }

    // Destructor: ensures the database is closed
    ~DataBaseManager() {
        close();
    }
};


#endif //FINAL_PROJECT_DATABASEMANAGER_H
