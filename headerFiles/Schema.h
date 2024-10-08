#ifndef FINAL_PROJECT_SCHEMA_H
#define FINAL_PROJECT_SCHEMA_H
#pragma once

#include <iostream>
#include "../sqlite/sqlite3.h"
#include "Validate.h"
using namespace std;

class Client;
class Employee;
class Admin;

class Schema{
protected:
    static sqlite3* open() {
        sqlite3* db ;
        int connection = sqlite3_open("DB.db", &db);
        if (connection != SQLITE_OK) {
            cout << "Failed to connect to the database: " << sqlite3_errmsg(db) << endl;
            return nullptr;
        }
        return db;
    }

    static void close(sqlite3* db){
        if (db) {
            sqlite3_close(db);
            db = nullptr;
        }
    }

public:
    template<typename Ty>
    static void insertTo(const string& table,Ty& user) {
        string name = user.getName();
        string password = user.getPassword();
        double balanceOrSalary = 0 ;
        string userType ;

        if constexpr (is_same_v<Ty, Client>) {
            balanceOrSalary = user.getBalance();
            userType = "Client";
        } else if constexpr (is_same_v<Ty, Employee>) {
            balanceOrSalary = user.getSalary();
            userType = "Employee";
        } else if constexpr (is_same_v<Ty, Admin>) {
            balanceOrSalary = user.getSalary();
            userType = "Admin";
        }else{
            cout << "Unknown user type." << endl;
            return;
        }


        if(!Validate::isValidName(name)){
            cout << "Not valid name." << endl;
            return;
        }
        if(!Validate::isStrInRange(password)){
            cout << "Not valid password." << endl;
            return;
        }

        if(is_same_v<Ty, Client>){
            if(!Validate::isMinBalance(balanceOrSalary)){
                cout << "Min Balance is 1500.";
            }
        }
        else{
            if(!Validate::isMinBalance(balanceOrSalary,5000)){
                cout << "Min salary is 5000.";
            }
        }

        string sql;


        if constexpr (is_same_v<Ty, Client>) {
            sql = "INSERT INTO " + table + " (name, password, balance) VALUES ('"
                               + name + "', '" + password + "', " + to_string(balanceOrSalary) + ");";
        }else{
            sql = "INSERT INTO " + table + " (name, password, salary) VALUES ('"
                               + name + "', '" + password + "', " + to_string(balanceOrSalary) + ");";
        }

        sqlite3* db = Schema::open();
        char* error = nullptr;

        int connection = sqlite3_exec(db, sql.c_str(), nullptr, nullptr, &error);

        if (connection != SQLITE_OK) {
            cout << "SQL error: " << error << endl;
            sqlite3_free(error);
            cout << "Failed" << endl;
            return;
        }

        cout << userType+" created." << endl;

        Schema::close(db);
    }

    static void all(const string& table) {
        sqlite3* db = Schema::open();
        sqlite3_stmt *stmt;
        const string sql = "SELECT * FROM " + table;

        int rc = sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr);

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

        Schema::close(db);
    }

    static void findById(const string& table ,const int& id) {
        sqlite3* db = Schema::open();
        sqlite3_stmt *stmt;
        const string sql = "SELECT * FROM "+table+" WHERE id = "+ to_string(id)+";";

        int rc = sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr);

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

        sqlite3_finalize(stmt);
        Schema::close(db);
    }

    static bool isFound(const string& table ,const int& id) {
        sqlite3* db = Schema::open();
        sqlite3_stmt *stmt;
        const string sql = "SELECT * FROM " + table + " WHERE id = " + to_string(id) + ";";

        int rc = sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr);

        Schema::close(db);
        return  sqlite3_step(stmt) == SQLITE_ROW;
    }

    static bool isFound(sqlite3* db , const string& table ,const int& id){
        sqlite3_stmt *stmt;
        const string sql = "SELECT * FROM " + table + " WHERE id = " + to_string(id) + ";";

        int rc = sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr);
        return sqlite3_step(stmt) == SQLITE_ROW;
    }

    static void updateColumn(const string& table ,const string& column , const int& id , const string& value){

        sqlite3* db = Schema::open();
        char* error = nullptr;


        if(!isFound(db,table,id)){
            cout << "Record not found" << endl;
            return;
        }

        if(column == "name"){
            if(!Validate::isValidName(value)){
                cout << "Not valid name." << endl;
                return;
            }
        }else{
            if(!Validate::isStrInRange(value)){
                cout << "Not valid password." << endl;
                return;
            }
        }

        string sql = "UPDATE " + table + " SET " + column + " = '" + value + "' WHERE id = " + to_string(id) + ";";

        int connection = sqlite3_exec(db, sql.c_str(), nullptr, nullptr, &error);

        if (connection == SQLITE_BUSY) {
            // Handle database locking error
            cout << "Database is locked. Retrying..." << endl;
            sqlite3_busy_timeout(db, 5000); // Retry after a delay of 5000ms
            connection = sqlite3_exec(db, sql.c_str(), nullptr, nullptr, &error);
        }

        if (connection != SQLITE_OK) {
            cout << "SQL error: " << error << endl;
            sqlite3_free(error);
            cout << "Failed" << endl;
        } else {
            cout << "Update successful." << endl;
        }

        Schema::close(db);
    }

    static void updateColumn(const string& table ,const string& column , const int& id , const double & value){

        sqlite3* db = Schema::open();
        char* error = nullptr;


        if(!isFound(db,table,id)){
            cout << "Record not found" << endl;
            return;
        }

        string sql = "UPDATE " + table + " SET " + column + " = '" + to_string(value) + "' WHERE id = " + to_string(id) + ";";

        int connection = sqlite3_exec(db, sql.c_str(), nullptr, nullptr, &error);

        if (connection == SQLITE_BUSY) {
            // Handle database locking error
            cout << "Database is locked. Retrying..." << endl;
            sqlite3_busy_timeout(db, 5000); // Retry after a delay of 5000ms
            connection = sqlite3_exec(db, sql.c_str(), nullptr, nullptr, &error);
        }

        if (connection != SQLITE_OK) {
            cout << "SQL error: " << error << endl;
            sqlite3_free(error);
            cout << "Failed" << endl;
        } else {
            cout << "Update successful." << endl;
        }

        Schema::close(db);
    }

    static void destroy(const string& table , int id){
        sqlite3* db = Schema::open();
        char* error = nullptr;

        if(!isFound(table,id)){
            cout << "Record not found" << endl;
            return;
        }

        const string sql = "DELETE FROM "+table+" WHERE id = "+ to_string(id);

        int connection = sqlite3_exec(db, sql.c_str(), nullptr, nullptr, &error);

        if (connection == SQLITE_BUSY) {
            // Handle database locking error
            cout << "Database is locked. Retrying..." << endl;
            sqlite3_busy_timeout(db, 5000); // Retry after a delay of 5000ms
            connection = sqlite3_exec(db, sql.c_str(), nullptr, nullptr, &error);
        }

        Schema::close(db);

        cout << "Record deleted." << endl;
    }

    static void clear(const string& table){
        sqlite3* db = Schema::open();
        char* error = nullptr;
        const string sql = "DELETE FROM "+table;

        int connection = sqlite3_exec(db, sql.c_str(), nullptr, nullptr, &error);

        if (connection == SQLITE_BUSY) {
            // Handle database locking error
            cout << "Database is locked. Retrying..." << endl;
            sqlite3_busy_timeout(db, 5000);
            connection = sqlite3_exec(db, sql.c_str(), nullptr, nullptr, &error);
        }

        Schema::close(db);

        cout << table+" cleared." << endl;
    }
};

#endif //FINAL_PROJECT_SCHEMA_H