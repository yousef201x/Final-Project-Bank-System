//
// Created by yousef on 9/15/2024.
//

#ifndef FINAL_PROJECT_EMPLOYEE_H
#define FINAL_PROJECT_EMPLOYEE_H

#pragma once
#include "Person.h"
#include "Schema.h"
#include "Client.h"

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

    Employee(int id,string name, string password, double salary)
            : Person(id,name, password)
    {}

    const double &getSalary(){
        return salary;
    }

    void displayInfo(){
        Person::displayInfo();
        cout << this->salary;
    }

    void addClient(Client& client){
        Schema::insertTo<Client>("clients",client);
    }

    void searchClient(int id){
        Schema::findById("clients",id);
    }

    void listClients(){
        Schema::all("clients");
    }

    void editClientName(int id ,string name){
        Schema::updateColumn("clients","name",id,name);
    }

    void editClientPassword(int id ,string password){
        Schema::updateColumn("clients","password",id,password);
    }

    void editClientBalance(int id ,double balance){
        Schema::updateColumn("clients","balance",id,balance);
    }

    static Employee login(int id, const string& password) {
        sqlite3* db = Schema::open();
        sqlite3_stmt *stmt;

        // Add single quotes around the password value
        const string sql = "SELECT * FROM employees WHERE id = " + to_string(id) + " AND password = '" + password + "';";

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


#endif //FINAL_PROJECT_EMPLOYEE_H