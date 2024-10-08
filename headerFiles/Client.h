//
// Created by yousef on 9/13/2024.
//

#ifndef FINAL_PROJECT_CLIENT_H
#define FINAL_PROJECT_CLIENT_H

#include "Person.h"
#include "Validate.h"
#include "../sqlite/sqlite3.h"
#include "Schema.h"

class Client : public Person {
private:
    bool canWithdraw(double value){
        return (this->balance >= value) ;
    }

    bool isValuePositive(double value){
        return (value >= 0) ;
    }

    void checkValue(double value){
        if(!isValuePositive(value)){
            throw negativeValueException();
        }
    }

protected:
    double balance{};
public:
    class invalidBalanceException : public exception{
    public:
        const char * what() const noexcept override {
            return "Error: Balance Cannot be less than 1500";
        }
    };

    class withdrawException : public exception{
    public:
        const char * what() const noexcept override {
            return "Error: Not enough balance";
        }
    };


    class negativeValueException : public exception{
    public:
        const char * what() const noexcept override {
            return "Error: Cannot use negative values";
        }
    };

    Client(string name, string password, double balance)
            : Person(name, password)
    {
        if(Validate::isMinBalance(balance)){
            this->balance = balance ;
        }else{
            throw invalidBalanceException();
        }
    }

    void setBalance(const double& balance) {
        this->balance = balance;
    }

    const double &getBalance() {
        return balance;
    }

    void deposit(const double& value){
        checkValue(value);

        this->balance += value ;
    }

    void withdraw(const double& value){
        checkValue(value);

        if(this->canWithdraw(value)){
            this->balance -= value;
        }else{
            throw withdrawException();
        }

    }

    void transferTo(const double& value , Client& c){
        checkValue(value);

        if(canWithdraw(value)){
            c.deposit(value);
            this->withdraw(value);
        }else{
            throw withdrawException();
        }

    }

    void displayInfo(){
        Person::displayInfo();
        cout << this->balance;
    }

    pair<int, bool> login(const int& id, const string& password){
        sqlite3* db ;

        int connection = sqlite3_open("DB.db", &db);

        if (connection != SQLITE_OK) {
            cout << "Failed to connect to the database: " << sqlite3_errmsg(db) << endl;
        }

        sqlite3_stmt* stmt;

        // Prepare the SQL query to select the record where id and password match
        const string sql = "SELECT id FROM clients WHERE id = ? AND password = ?;";

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

#endif //FINAL_PROJECT_CLIENT_H