//
// Created by yousef on 9/13/2024.
//

#ifndef FINAL_PROJECT_CLIENT_H
#define FINAL_PROJECT_CLIENT_H

#include "Person.h"
#include "Validate.h"
#include "../sqlite/sqlite3.h"
#include "Schema.h"
#include "Response.h"

class Client : public Person {
private:
    double balance{};

    bool canWithdraw(double value) const {
        return (this->balance >= value);
    }

    bool isValuePositive(double value) const {
        return (value >= 0);
    }

    const char* checkValue(double value) const {
        if (!isValuePositive(value)) {
            return Response::NOT_POSITIVE_AMOUNT;
        }
        return Response::SUCCESS; // Return success message if the value is valid
    }

public:
    Client(int id, const string& name, const string& password, double balance)
            : Person(id, name, password), balance(balance) {}

    Client(const Client& other)
            : Person(other.getId(), other.getName(), other.getPassword()), balance(other.balance) {}

    void setBalance(const double& balance) {
        this->balance = balance;
    }

    const double& getBalance() const {
        return balance;
    }

    static pair<bool, Client> returnById(int id) {
        sqlite3* db = Schema::open();
        sqlite3_stmt *stmt;

        const string sql = "SELECT * FROM clients WHERE id = " + to_string(id) + ";";

        int connection = sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr);
        if (connection != SQLITE_OK) {
            sqlite3_finalize(stmt);
            Schema::close(db);
            return {false, {-1, "", "", -1}}; // Return an invalid Client
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
            sqlite3_finalize(stmt);
            Schema::close(db);
            return {false, {-1, "", "", -1}}; // Return an invalid Client
        }

        sqlite3_finalize(stmt);
        Schema::close(db);
        return {true, {userId, username, userPassword, balance}};
    }

    pair<bool, const char*> deposit(const double& value) {
        const char* validationResult = checkValue(value);
        if (validationResult != Response::SUCCESS) {
            return {false, validationResult}; // Return failure status if validation fails
        }
        balance += value;
        Schema::updateColumn("clients", "balance", id, balance);
        return {true, Response::SUCCESS};
    }

    pair<bool, const char*> withdraw(const double& value) {
        const char* validationResult = checkValue(value);
        if (validationResult != Response::SUCCESS) {
            return {false, validationResult}; // Return failure status if validation fails
        }
        if (canWithdraw(value)) {
            this->balance -= value;
            Schema::updateColumn("clients", "balance", id, balance);
            return {true, Response::SUCCESS};
        } else {
            return {false, Response::INSUFFICIENT_BALANCE};
        }
    }

    pair<bool, const char*> transferTo(const double& value, int userId) {
        const char* validationResult = checkValue(value);
        if (validationResult != Response::SUCCESS) {
            return {false, validationResult}; // Return failure status if validation fails
        }

        pair<bool, Client> isFound = returnById(userId); // Use userId to find the target client

        if (isFound.first) {
            if (canWithdraw(value)) {
                Client c = isFound.second;
                c.deposit(value);
                this->withdraw(value);
            } else {
                return {false, Response::INSUFFICIENT_BALANCE};
            }
        } else {
            return {false, Response::USER_NOT_FOUND};
        }

        return {true, Response::SUCCESS};
    }

    void displayInfo() {
        Person::displayInfo();
        cout << "Balance: " << this->balance << endl;
    }

    static Client login(int id, const string& password) {
        sqlite3* db = Schema::open();
        sqlite3_stmt *stmt;

        const string sql = "SELECT * FROM clients WHERE id = " + to_string(id) + " AND password = '" + password + "';";

        int rc = sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr);
        if (rc != SQLITE_OK) {
            sqlite3_finalize(stmt);
            Schema::close(db);
            return  {-1, "", "", -1};
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
            sqlite3_finalize(stmt);
            Schema::close(db);
            return {-1, "", "", -1}; // Return an invalid Client if no matching record
        }

        sqlite3_finalize(stmt);
        Schema::close(db);
        return  {userId, username, userPassword, balance};
    }
};

#endif //FINAL_PROJECT_CLIENT_H
