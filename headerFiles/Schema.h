#ifndef FINAL_PROJECT_SCHEMA_H
#define FINAL_PROJECT_SCHEMA_H

#include <iostream>
#include "../sqlite/sqlite3.h"
#include "Client.h"
#include "Employee.h"
#include "Admin.h"
using namespace std;



class Schema{
private:
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
    static void insertTo(const string& table,Client& client) {
        string name = client.getName();
        string password = client.getPassword();
        double balance = client.getBalance();

        if(!Validate::isValidName(name)){
            cout << "Not valid name." << endl;
            return;
        }
        if(!Validate::isStrInRange(password)){
            cout << "Not valid password." << endl;
            return;
        }

        const string sql = "INSERT INTO "+table+" (name, password, balance) VALUES ('"
                           + name + "', '" + password + "', " + to_string(balance) + ");";

        sqlite3* db = Schema::open();
        char* error = nullptr;

        int connection = sqlite3_exec(db, sql.c_str(), nullptr, nullptr, &error);

        if (connection != SQLITE_OK) {
            cout << "SQL error: " << error << endl;
            sqlite3_free(error);
            cout << "Failed" << endl;
            return;
        }

        cout << "Client created." << endl;

        Schema::close(db);
    }

    static void insertTo(const string& table,Employee& employee) {
        string name = employee.getName();
        string password = employee.getPassword();
        double balance = employee.getSalary();

        if(!Validate::isValidName(name)){
            cout << "Not valid name." << endl;
            return;
        }
        if(!Validate::isStrInRange(password)){
            cout << "Not valid password." << endl;
            return;
        }

        const string sql = "INSERT INTO "+table+" (name, password, balance) VALUES ('"
                           + name + "', '" + password + "', " + to_string(balance) + ");";

        sqlite3* db = Schema::open();
        char* error = nullptr;

        int connection = sqlite3_exec(db, sql.c_str(), nullptr, nullptr, &error);

        if (connection != SQLITE_OK) {
            cout << "SQL error: " << error << endl;
            sqlite3_free(error);
            cout << "Failed" << endl;
            return;
        }

        cout << "Employee created." << endl;

        Schema::close(db);
    }

    static void insertTo(const string& table,Admin& admin) {
        string name = admin.getName();
        string password = admin.getPassword();
        double balance = admin.getSalary();

        if(!Validate::isValidName(name)){
            cout << "Not valid name." << endl;
            return;
        }
        if(!Validate::isStrInRange(password)){
            cout << "Not valid password." << endl;
            return;
        }

        const string sql = "INSERT INTO "+table+" (name, password, balance) VALUES ('"
                           + name + "', '" + password + "', " + to_string(balance) + ");";

        sqlite3* db = Schema::open();
        char* error = nullptr;

        int connection = sqlite3_exec(db, sql.c_str(), nullptr, nullptr, &error);

        if (connection != SQLITE_OK) {
            cout << "SQL error: " << error << endl;
            sqlite3_free(error);
            cout << "Failed";
            return;
        }

        cout << "Admin created." << endl;

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

        sqlite3_finalize(stmt);  // Finalize the prepared statement
        Schema::close(db);
    }


    static bool isFound(const string& table ,const int& id) {
        sqlite3* db = Schema::open();
        sqlite3_stmt *stmt;
        const string sql = "SELECT * FROM " + table + " WHERE id = " + to_string(id) + ";";

        int rc = sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr);

        bool found = sqlite3_step(stmt) == SQLITE_ROW;

        Schema::close(db);  // Close database connection after step operation
        return found;
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

        // Ensure you update only the specific record by id
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

        // Close the database connection to avoid locking issues
        Schema::close(db);
    }

    static void destroy(const string& table , int id){
        sqlite3* db = Schema::open();
        char* error = nullptr;

        if(!isFound(db,table,id)){
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
            sqlite3_busy_timeout(db, 5000); // Retry after a delay of 5000ms
            connection = sqlite3_exec(db, sql.c_str(), nullptr, nullptr, &error);
        }

        Schema::close(db);

        cout << table+" cleared." << endl;
    }


};

#endif //FINAL_PROJECT_SCHEMA_H