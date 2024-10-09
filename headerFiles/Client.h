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

    Client(int id,string name, string password, double balance)
            : Person(id,name, password)
    {}

    Client(const Client& other)
            : Person(other.getId(), other.getName(), other.getPassword()),
              balance(other.balance)
    {}

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

    static Client login(int id, const string& password) {
        sqlite3* db = Schema::open();
        sqlite3_stmt *stmt;

        // Add single quotes around the password value
        const string sql = "SELECT * FROM clients WHERE id = " + to_string(id) + " AND password = '" + password + "';";

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

#endif //FINAL_PROJECT_CLIENT_H