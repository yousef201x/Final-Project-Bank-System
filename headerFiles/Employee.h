//
// Created by yousef on 9/15/2024.
//

#ifndef FINAL_PROJECT_EMPLOYEE_H
#define FINAL_PROJECT_EMPLOYEE_H

#include "Person.h"
#include "Database.h"

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

    void addClient(Client& client,sqlite3* db,string fileName = "DB.db"){
        string name = client.getName();
        string password = client.getPassword();
        double balance = client.getBalance();

        DataBase::openConnection(fileName,db);

        const string sql = "INSERT INTO clients (name, password, balance) VALUES ('"
                           + name + "', '" + password + "', " + to_string(balance) + ");";

        if(DataBase::executeSQL(db,sql)){
            cout << "Client created successfully." << endl;
        }else{
            cout << "An error occurred while creating new Client." << endl;
        }

        DataBase::closeConnection(db);
    }

    void listClients(sqlite3* db){
        sqlite3_stmt *stmt;
        const string sql = "SELECT * FROM clients";

        int rc = sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr);

        if (sqlite3_step(stmt) == SQLITE_ROW) {
            do {
                cout << "ID: " << sqlite3_column_text(stmt, 0) << std::endl;
                cout << "NAME: " << sqlite3_column_text(stmt, 1) << std::endl;
                cout << "BALANCE :"
                     << sqlite3_column_text(stmt, 3) << "$" << endl << endl;
            } while (sqlite3_step(stmt) == SQLITE_ROW);
        } else {
            cout << "No Data found." << std::endl;
        }
    }

    void findClient(const string& name, sqlite3* db, const string& fileName = "DB.db") {
        DataBase::openConnection(fileName,db);

        sqlite3_stmt *stmt;
        const string sql = "SELECT * FROM clients WHERE name LIKE ?;";

        int rc = sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr);

        // Create wildcard pattern
        string wildcard = "%" + name + "%";

        // Bind the wildcard pattern to the SQL statement
        sqlite3_bind_text(stmt, 1, wildcard.c_str(), -1, SQLITE_STATIC);

        if (sqlite3_step(stmt) == SQLITE_ROW) {
            do {
                cout << "ID: " << sqlite3_column_text(stmt, 0) << std::endl;
                cout << "NAME: " << sqlite3_column_text(stmt, 1) << std::endl;
                cout << "BALANCE :" << sqlite3_column_text(stmt, 3) << "$" << endl << endl;
            } while (sqlite3_step(stmt) == SQLITE_ROW);
        } else {
            cout << "No Data found." << std::endl;
        }

        DataBase::closeConnection(db);
    }

    void findClient(const int& id, sqlite3* db, const string& fileName = "DB.db") {
        DataBase::openConnection(fileName,db);

        sqlite3_stmt *stmt;
        const string sql = "SELECT * FROM clients WHERE id = "+ to_string(id)+";";

        int rc = sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr);

        if (sqlite3_step(stmt) == SQLITE_ROW) {
            do {
                cout << "ID: " << sqlite3_column_text(stmt, 0) << std::endl;
                cout << "NAME: " << sqlite3_column_text(stmt, 1) << std::endl;
                cout << "BALANCE :" << sqlite3_column_text(stmt, 3) << "$" << endl << endl;
            } while (sqlite3_step(stmt) == SQLITE_ROW);
        } else {
            cout << "No Data found." << std::endl;
        }

        DataBase::closeConnection(db);
    }


};


#endif //FINAL_PROJECT_EMPLOYEE_H

