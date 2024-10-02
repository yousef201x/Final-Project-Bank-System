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

using namespace std;

class DataBaseManager : public DataBase
{
public:
    // Constructor: takes the name of the database file
    DataBaseManager(const string& name) : DataBase(name) {}

    bool addClient(Client& client) {
        string name = client.getName();
        string password = client.getPassword();
        double balance = client.getBalance();

        const string sql = "INSERT INTO clients (name, password, balance) VALUES ('"
                                + name + "', '" + password + "', " + std::to_string(balance) + ");";

        if(execute(sql)){
            cout << "Client created successfully." << endl;
            return true;
        }else{
            cout << "An error occurred while creating new Client." << endl;
            return false;
        }
    }

    bool addEmployee(Employee& employee) {
        string name = employee.getName();
        string password = employee.getPassword();
        double salary = employee.getSalary();

        const string sql = "INSERT INTO admins (name, password, salary) VALUES ('"
                                + name + "', '" + password + "', " + std::to_string(salary) + ");";

        if(execute(sql)){
            cout << "Employee created successfully." << endl;
            return true;
        }else{
            cout << "An error occurred while creating new Employee." << endl;
            return false;
        }
    }


    bool addAdmin(Admin& admin) {
        string name = admin.getName();
        string password = admin.getPassword();
        double salary = admin.getSalary();

        const string sql = "INSERT INTO admins (name, password, salary) VALUES ('"
                                + name + "', '" + password + "', " + std::to_string(salary) + ");";

        if(execute(sql)){
            cout << "Admin created successfully." << endl;
            return true;
        }else{
            cout << "An error occurred while creating new Admin." << endl;
            return false;
        }
    }

    // Destructor: ensures the database is closed
    ~DataBaseManager() {
        close();
    }
};


#endif //FINAL_PROJECT_DATABASEMANAGER_H
