#ifndef FINAL_PROJECT_SCHEMA_H
#define FINAL_PROJECT_SCHEMA_H
#pragma once

#include <iostream>
#include "../sqlite/sqlite3.h"
#include "Validate.h"
#include "Response.h"
using namespace std;

class Client;
class Employee;
class Admin;

class Schema{
protected:
    static pair<bool,const char*> createClientsTable() {
        const string sql = "CREATE TABLE IF NOT EXISTS clients("
                           "id INTEGER PRIMARY KEY AUTOINCREMENT, "
                           "name TEXT NOT NULL, "
                           "password TEXT NOT NULL, "
                           "balance FLOAT(10,3) NOT NULL);";
        sqlite3* db = Schema::open();
        char* error = nullptr;

        int connection = sqlite3_exec(db, sql.c_str(), nullptr, nullptr, &error);

        if (connection != SQLITE_OK) {
            return {false,Response::DB_FAILED_TO_BUILD_TABLE};
        }

        Schema::close(db);
        return {true,Response::DB_SUCCESS};
    }

    static pair<bool,const char*> createEmployeeTable() {
        const string sql = "CREATE TABLE IF NOT EXISTS employees("
                           "id INTEGER PRIMARY KEY AUTOINCREMENT, "
                           "name TEXT NOT NULL, "
                           "password TEXT NOT NULL, "
                           "salary FLOAT(10,3) NOT NULL);";
        sqlite3* db = Schema::open();
        char* error = nullptr;

        int connection = sqlite3_exec(db, sql.c_str(), nullptr, nullptr, &error);

        if (connection != SQLITE_OK) {
            return {false,Response::DB_FAILED_TO_BUILD_TABLE};
        }

        Schema::close(db);
        return {true,Response::DB_SUCCESS};
    }
    static pair<bool,const char*> createAdminsTable() {
        const string sql = "CREATE TABLE IF NOT EXISTS admins("
                           "id INTEGER PRIMARY KEY AUTOINCREMENT, "
                           "name TEXT NOT NULL, "
                           "password TEXT NOT NULL, "
                           "salary FLOAT(10,3) NOT NULL);";
        sqlite3* db = Schema::open();
        char* error = nullptr;

        int connection = sqlite3_exec(db, sql.c_str(), nullptr, nullptr, &error);

        if (connection != SQLITE_OK) {
            return {false,Response::DB_FAILED_TO_BUILD_TABLE};
        }

        Schema::close(db);
        return {true,Response::DB_SUCCESS};
    }

public:
    static sqlite3* open() {
        sqlite3* db ;
        int connection = sqlite3_open("DB.db", &db);
        return db;
    }

    static void close(sqlite3* db){
        sqlite3_close(db);
        db = nullptr;
    }

    static pair<bool,const char*> buildTables() {
        createClientsTable();
        createEmployeeTable();
        createAdminsTable();
        return {true , Response::DB_SUCCESS};
    }

    template<typename Ty>
    static pair<bool,const char*> insertTo(const string& table,Ty& user) {
        string name = user.getName();
        string password = user.getPassword();
        double balanceOrSalary = 0 ;
        string userType ;

        if constexpr (is_same_v<Ty, Client>) {
            balanceOrSalary = user.getBalance();
            if (!Validate::isMinBalance(balanceOrSalary)){
                return {false,Response::NOT_MIN_BALANCE};
            }
            userType = "Client";
        } else if constexpr (is_same_v<Ty, Employee>) {
            balanceOrSalary = user.getSalary();
            if (!Validate::isMinBalance(balanceOrSalary)){
                return {false,Response::NOT_MIN_SALARY};
            }
            userType = "Employee";
        } else if constexpr (is_same_v<Ty, Admin>) {
            balanceOrSalary = user.getSalary();
            if (!Validate::isMinBalance(balanceOrSalary)){
                return {false,Response::NOT_MIN_SALARY};
            }
            userType = "Admin";
        }


        if(!Validate::isValidName(name)){
            return {false,Response::NOT_VALID_NAME};
        }
        if(!Validate::isStrInRange(password)){
            return {false , Response::NOT_VALID_PASSWORD};
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

        if (connection == SQLITE_BUSY) {
            // Handle database locking error
            cout << "Database is locked. Retrying..." << endl;
            sqlite3_busy_timeout(db, 5000); // Retry after a delay of 5000ms
            connection = sqlite3_exec(db, sql.c_str(), nullptr, nullptr, &error);
        }

        if (connection != SQLITE_OK) {
            return {false,Response::DB_FAILURE};
        }

        Schema::close(db);

        return {true,Response::DB_SUCCESS};
    }

    static pair<bool,const char*> all(const string& table) {
        sqlite3* db = Schema::open();
        char* error;
        sqlite3_stmt *stmt;
        const string sql = "SELECT * FROM " + table;

        int connection = sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr);

        if (connection == SQLITE_BUSY) {
            // Handle database locking error
            cout << "Database is locked. Retrying..." << endl;
            sqlite3_busy_timeout(db, 5000); // Retry after a delay of 5000ms
            connection = sqlite3_exec(db, sql.c_str(), nullptr, nullptr, &error);
        }

        if (sqlite3_step(stmt) == SQLITE_ROW) {
            do {
                cout << "ID: " << sqlite3_column_text(stmt, 0) << endl;
                cout << "NAME: " << sqlite3_column_text(stmt, 1) << endl;
                cout << (table == "clients" ? "BALANCE: " : "SALARY: ")
                     << sqlite3_column_text(stmt, 3) << "$" << endl << endl;
            } while (sqlite3_step(stmt) == SQLITE_ROW);
        } else {
            return {false,Response::DB_NO_ROWS_RETURNED};
        }

        Schema::close(db);

        return {true,Response::DB_SUCCESS};
    }

    static pair<bool,const char*> findById(const string& table ,const int& id) {
        sqlite3* db = Schema::open();
        char* error;
        sqlite3_stmt *stmt;
        const string sql = "SELECT * FROM "+table+" WHERE id = "+ to_string(id)+";";

        int connection = sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr);

        if (connection == SQLITE_BUSY) {
            // Handle database locking error
            cout << "Database is locked. Retrying..." << endl;
            sqlite3_busy_timeout(db, 5000); // Retry after a delay of 5000ms
            connection = sqlite3_exec(db, sql.c_str(), nullptr, nullptr, &error);
        }

        if (sqlite3_step(stmt) == SQLITE_ROW) {
            do {
                cout << "ID: " << sqlite3_column_text(stmt, 0) << endl;
                cout << "NAME: " << sqlite3_column_text(stmt, 1) << endl;
                cout << (table == "clients" ? "BALANCE: " : "SALARY: ") << sqlite3_column_text(stmt, 3) << "$" << endl << endl;
            } while (sqlite3_step(stmt) == SQLITE_ROW);
        } else {
            return {false,Response::DB_NO_ROWS_RETURNED};
        }

        sqlite3_finalize(stmt);
        Schema::close(db);

        return {true,Response::DB_SUCCESS};
    }

    static bool isFound(const string& table ,const int& id) {
        sqlite3* db = Schema::open();
        sqlite3_stmt *stmt;
        const string sql = "SELECT * FROM " + table + " WHERE id = " + to_string(id) + ";";

        int connection = sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr);

        sqlite3_finalize(stmt);
        Schema::close(db);
        return  sqlite3_step(stmt) == SQLITE_ROW;
    }

    static bool isFound(sqlite3* db, const string& table, const int& id) {

        sqlite3_stmt* stmt;
        const string sql = "SELECT * FROM " + table + " WHERE id = " + to_string(id) + ";";

        int connection = sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr);

        bool found = sqlite3_step(stmt) == SQLITE_ROW;  // Check if the row exists

        sqlite3_finalize(stmt);  // Finalize the statement regardless of the outcome
        return found;  // Return whether the ID was found
    }


    static pair<bool,const char*> updateColumn(const string& table ,const string& column , const int& id , const string& value){

        sqlite3* db = Schema::open();
        char* error = nullptr;


        if(!isFound(db,table,id)){
            return {false,Response::DB_NO_ROWS_RETURNED};
        }

        string sql = "UPDATE " + table + " SET " + column + " = '" + value+ "' WHERE id = " + to_string(id) + ";";
        int connection = sqlite3_exec(db, sql.c_str(), nullptr, nullptr, &error);
        if (connection == SQLITE_BUSY) {
            // Handle database locking error
            cout << "Database is locked. Retrying..." << endl;
            sqlite3_busy_timeout(db, 5000); // Retry after a delay of 5000ms
            connection = sqlite3_exec(db, sql.c_str(), nullptr, nullptr, &error);
        }
        if (connection != SQLITE_OK) {
            return {false,Response::DB_FAILURE};
        }

        Schema::close(db);
        return {true,Response::DB_SUCCESS};
    }

    static pair<bool,const char*> updateColumn(const string& table ,const string& column , const int& id , const double & value){

        sqlite3* db = Schema::open();
        char* error = 0;

        if(!isFound(db,table,id)){
            return {false,Response::DB_NO_ROWS_RETURNED};
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
            return {false,Response::DB_FAILURE};
        }

        Schema::close(db);

        return {true,Response::DB_SUCCESS};
    }

    static pair<bool , const char*>destroy(const string& table , int id){
        sqlite3* db = Schema::open();
        char* error = nullptr;

        if(!isFound(table,id)){
            return {false,Response::DB_NO_ROWS_RETURNED};
        }

        const string sql = "DELETE FROM "+table+" WHERE id = "+ to_string(id);

        int connection = sqlite3_exec(db, sql.c_str(), nullptr, nullptr, &error);

        if (connection == SQLITE_BUSY) {
            cout << "Database is locked. Retrying..." << endl;
            sqlite3_busy_timeout(db, 5000);
            connection = sqlite3_exec(db, sql.c_str(), nullptr, nullptr, &error);
        }

        if (connection != SQLITE_OK) {
            return {false,Response::DB_FAILURE};
        }

        Schema::close(db);

        return {true,Response::DB_SUCCESS};
    }

    static pair<bool,const char*> clear(const string& table){
        sqlite3* db = Schema::open();
        char* error = nullptr;
        const string sql = "DELETE FROM "+table;

        int connection = sqlite3_exec(db, sql.c_str(), nullptr, nullptr, &error);

        if (connection == SQLITE_BUSY) {
            cout << "Database is locked. Retrying..." << endl;
            sqlite3_busy_timeout(db, 5000);
            connection = sqlite3_exec(db, sql.c_str(), nullptr, nullptr, &error);
        }

        if (connection != SQLITE_OK) {
            return {false,Response::DB_FAILURE};
        }

        Schema::close(db);

        return {true,Response::DB_SUCCESS};
    }
};

#endif //FINAL_PROJECT_SCHEMA_H