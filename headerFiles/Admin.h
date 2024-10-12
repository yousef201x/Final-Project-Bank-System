//
// Created by yousef on 9/15/2024.
//

#ifndef FINAL_PROJECT_ADMIN_H
#define FINAL_PROJECT_ADMIN_H

#include "Employee.h"
#include "Schema.h"

class Admin : public Employee{
public:
    Admin(int id,string name, string password, double salary)
    : Employee(id,name, password,salary)
    {}

    pair<bool,const char*> addEmployee(Employee& employee){
        auto stmt = Schema::insertTo<Employee>("employees",employee);
        return {stmt.first,stmt.second};
    }

    pair<bool,const char*> searchEmployee(int id){
        auto stmt = Schema::findById("employees",id);
        return {stmt.first,stmt.second};
    }

    pair<bool,const char*> listEmployees(){
        auto stmt = Schema::all("employees");
        return {stmt.first,stmt.second};
    }

    pair<bool,const char*> editEmployeeName(int id ,string name){
        auto stmt = Schema::updateColumn("employees","name",id,name);
        return {stmt.first,stmt.second};
    }

    pair<bool,const char*> editEmployeePassword(int id ,string password){
        auto stmt = Schema::updateColumn("employees","password",id,password);
        return {stmt.first,stmt.second};
    }

    pair<bool,const char*> editEmployeeSalary(int id ,double salary){
        auto stmt = Schema::updateColumn("employees","salary",id,salary);
        return {stmt.first,stmt.second};
    }

    static Admin login(int id, const string& password) {
        sqlite3* db = Schema::open();
        sqlite3_stmt *stmt;

        // Add single quotes around the password value
        const string sql = "SELECT * FROM admins WHERE id = " + to_string(id) + " AND password = '" + password + "';";

        int rc = sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr);
        if (rc != SQLITE_OK) {
            cout << "Failed to prepare statement: " << sqlite3_errmsg(db) << endl;
            sqlite3_finalize(stmt);
            Schema::close(db);
            return {-1, "", "", -1}; // Return an invalid Client
        }

        int userId = -1;
        string username{};
        string userPassword{};
        double balance = -1;

        if (sqlite3_step(stmt) == SQLITE_ROW) {
            // Fetching the columns from the result row
            userId = sqlite3_column_int(stmt, 0);
            username = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
            userPassword = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2));
            balance = sqlite3_column_double(stmt, 3);

        } else {
            cout << "\nInvalid credentials or no matching record!" << endl;
        }

        sqlite3_finalize(stmt);
        Schema::close(db);
        return {userId, username, userPassword, balance};
    }

};

#endif //FINAL_PROJECT_ADMIN_H