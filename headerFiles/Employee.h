//
// Created by yousef on 9/15/2024.
//

#ifndef FINAL_PROJECT_EMPLOYEE_H
#define FINAL_PROJECT_EMPLOYEE_H

#pragma once
#include "Person.h"

class Employee : public Person{
protected:
    double salary{};
public:
    class invalidSalaryException : public exception{
    public:
        const char * what() const noexcept override {
            return "Error: Salary Cannot be less than 5000";
        }
    };

    Employee(string name, string password, double salary)
            : Person(name, password)
    {
        if(Validate::isMinBalance(salary, 5000)){
            this->salary = salary ;
        }else{
            throw invalidSalaryException();
        }
    }

    const double &getSalary(){
        return salary;
    }

    void displayInfo(){
        Person::displayInfo();
        cout << this->salary;
    }

    pair<int, bool> login(const int& id, const string& password){
        sqlite3* db ;

        int connection = sqlite3_open("DB.db", &db);

        if (connection != SQLITE_OK) {
            cout << "Failed to connect to the database: " << sqlite3_errmsg(db) << endl;
        }

        sqlite3_stmt* stmt;

        // Prepare the SQL query to select the record where id and password match
        const string sql = "SELECT id FROM employees WHERE id = ? AND password = ?;";

        // Prepare the statement
        int rc = sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr);

        // Bind the id and password to the prepared statement
        sqlite3_bind_int(stmt, 1, id);  // Bind id as integer
        sqlite3_bind_text(stmt, 2, password.c_str(), -1, SQLITE_STATIC);  // Bind password as text

        // Execute the query and check if a result exists
        if (sqlite3_step(stmt) == SQLITE_ROW) {
            // Retrieve the user's ID
            int foundId = sqlite3_column_int(stmt, 0);

            sqlite3_finalize(stmt);
            sqlite3_close(db);
            db = nullptr;
            return {foundId, true};  // Return the user's ID and userType
        }

        // Login failed
        cout << "Login failed. Invalid ID or password." << endl;
        sqlite3_finalize(stmt);
        sqlite3_close(db);
        db = nullptr;
        return {-1, false};  // Return -1 for id and an empty string for userType indicating failure
    }

};


#endif //FINAL_PROJECT_EMPLOYEE_H