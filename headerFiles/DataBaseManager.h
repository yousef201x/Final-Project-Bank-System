#ifndef FINAL_PROJECT_DATABASEMANAGER_H
#define FINAL_PROJECT_DATABASEMANAGER_H

#pragma once
#include "DataBase.h"
#include "Client.h"
#include "Admin.h"
#include "Employee.h"
#include "../sqlite/sqlite3.h"
#include "Validate.h"

using namespace std;

class DataBaseManager : public DataBase
{
public:
    // Constructor: takes the name of the database file
    DataBaseManager(const string& name) : DataBase(name) {}

    void insertTo(const string& table,Client& client) {
        string name = client.getName();
        string password = client.getPassword();
        double balance = client.getBalance();

        if(!Validate::isValidName(name)){
            cout << "Not valid name.";
            return;
        }
        if(!Validate::isStrInRange(password)){
            cout << "Not valid password.";
            return;
        }

        const string sql = "INSERT INTO "+table+" (name, password, balance) VALUES ('"
                                + name + "', '" + password + "', " + to_string(balance) + ");";

        if(execute(sql)){
            cout << "Client created successfully." << endl;
            return;
        }else{
            cout << "An error occurred while creating new Client." << endl;
            return;
        }
    }

    void insertTo(const string& table,Employee& employee) {
        string name = employee.getName();
        string password = employee.getPassword();
        double salary = employee.getSalary();

        if(!Validate::isValidName(name)){
            cout << "Not valid name.";
            return;
        }
        if(!Validate::isStrInRange(password)){
            cout << "Not valid password.";
            return;
        }

        const string sql = "INSERT INTO "+table+" (name, password, salary) VALUES ('"
                           + name + "', '" + password + "', " + to_string(salary) + ");";

        if(execute(sql)){
            cout << "Employee created successfully." << endl;
        }else{
            cout << "An error occurred while creating new Employee." << endl;
        }
    }

    void insertTo(const string& table,Admin& admin) {
        string name = admin.getName();
        string password = admin.getPassword();
        double salary = admin.getSalary();

        if(!Validate::isValidName(name)){
            cout << "Not valid name.";
            return;
        }
        if(!Validate::isStrInRange(password)){
            cout << "Not valid password.";
            return;
        }

        const string sql = "INSERT INTO "+table+" (name, password, salary) VALUES ('"
                           + name + "', '" + password + "', " + to_string(salary) + ");";

        if(execute(sql)){
            cout << "Admin created successfully." << endl;
            return;
        }else{
            cout << "An error occurred while creating new Admin." << endl;
            return;
        }
    }

    void all(const string& table) {
        sqlite3_stmt *stmt;
        const string sql = "SELECT * FROM " + table;

        int rc = sqlite3_prepare_v2(getDb(), sql.c_str(), -1, &stmt, nullptr);

        if (sqlite3_step(stmt) == SQLITE_ROW) {
            do {
                cout << "ID: " << sqlite3_column_text(stmt, 0) << endl;
                cout << "NAME: " << sqlite3_column_text(stmt, 1) << endl;
                cout << (table == "clients" ? "BALANCE: " : "SALARY: ")
                << sqlite3_column_text(stmt, 3) << "$" << endl << endl;
            } while (sqlite3_step(stmt) == SQLITE_ROW);
        } else {
            cout << "No Data found." << endl;
        }
    }

    void findById(const string& table ,const int& id) {
        sqlite3_stmt *stmt;
        const string sql = "SELECT * FROM "+table+" WHERE id = "+ to_string(id)+";";

        int rc = sqlite3_prepare_v2(getDb(), sql.c_str(), -1, &stmt, nullptr);

        if (sqlite3_step(stmt) == SQLITE_ROW) {
            do {
                cout << "ID: " << sqlite3_column_text(stmt, 0) << endl;
                cout << "NAME: " << sqlite3_column_text(stmt, 1) << endl;
                cout << (table == "clients" ? "BALANCE: " : "SALARY: ") << sqlite3_column_text(stmt, 3) << "$" << endl << endl;
            } while (sqlite3_step(stmt) == SQLITE_ROW);
        } else {
            cout << "No Data found." << endl;
            return;
        }
    }

    bool isFound(const string& table ,const int& id){
        sqlite3_stmt *stmt;
        const string sql = "SELECT * FROM "+table+" WHERE id = "+ to_string(id)+";";

        int rc = sqlite3_prepare_v2(getDb(), sql.c_str(), -1, &stmt, nullptr);

        return sqlite3_step(stmt) == SQLITE_ROW;
    }

    void update(const string& table ,const int& id , const string& name , const string& password , double val = -9999){

        if(!isFound(table,id)){
            cout << "Record not found" << endl;
            return;
        }

        if(!Validate::isValidName(name)){
            cout << "Not valid name.";
            return;
        }
        if(!Validate::isStrInRange(password)){
            cout << "Not valid password.";
            return;
        }

        string sql;

        if(!empty(name)) {
            sql = "UPDATE " + table + " SET name = '" + name + "';";
            if (execute(sql)) {
                cout << "Name updated successfully." << endl;
            } else {
                cout << "An Error occurred while updating name." << endl;
            }
        }

        if (!empty(password)) {
            sql = "UPDATE " + table + " SET password = '" + password + "';";
            if (execute(sql)) {
                cout << "Password updated successfully." << endl;
            } else {
                cout << "An Error occurred while updating password." << endl;
            }
        }

        if(val != -9999){
            if(table == "clients"){
                sql = "UPDATE " + table + " SET balance = " + to_string(val) + ";";
            }else{
                sql = "UPDATE " + table + " SET salary = " + to_string(val) + ";";
            }


            if (execute(sql)) {
                cout << (table == "clients" ? "Balance updated successfully." : "Salary updated successfully.") << endl;
            } else {
                    cout << (table == "clients" ? "An Error occurred while updating Balance." : "An Error occurred while updating Salary.") << endl;
            }
        }
    }

    void updateColumn(const string& table ,const string& column , const int& id , const string& value){

        if(!isFound(table,id)){
            cout << "Record not found" << endl;
            return;
        }

        if(column == "name"){
            if(!Validate::isValidName(value)){
                cout << "Not valid name.";
                return;
            }
        }else{
            if(!Validate::isStrInRange(value)){
                cout << "Not valid password.";
                return;
            }
        }

        string sql = "UPDATE " + table + " SET "+column+"= '" + value + "';";
        if (execute(sql)) {
            cout << column+" updated successfully." << endl;
        } else {
            cout << "An Error occurred while updating"+column+"." << endl;
        }
    }

    void updateColumn(const string& table ,const string& column , const int& id , double value){

        if(!isFound(table,id)){
            cout << "Record not found" << endl;
            return;
        }

        string sql = "UPDATE " + table + " SET "+column+"= '" + to_string(value) + "';";
        if (execute(sql)) {
            cout << column+" updated successfully." << endl;
        } else {
            cout << "An Error occurred while updating"+column+"." << endl;
        }
    }

    void destroy(const string& table , int id){
        if(!isFound(table,id)){
            cout << "Record not found" << endl;
            return;
        }

        const string sql = "DELETE FROM "+table+" WHERE id = "+ to_string(id);

        if(execute(sql)){
            cout << "Record deleted"<< endl;
            return;
        }else{
            cout << "An error occurred while deleting the record." << endl;
            return;
        }
    }

    void clear(const string& table){
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
