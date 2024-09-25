//
// Created by yousef on 9/13/2024.
//

#ifndef FINAL_PROJECT_CLIENT_H
#define FINAL_PROJECT_CLIENT_H

#include "Person.h"
#include "Validate.h"

class Client : public Person {
private:
    bool canWithdraw(double value){
        return (this->balance >= value);
    }

    bool isValuePositive(double value){
        return (value >= 0);
    }

    void checkValue(double value){
        if (!isValuePositive(value)){
            throw negativeValueException();
        }
    }

protected:
    double balance{};
public:
    class invalidBalanceException : public exception {
    public:
        const char* what() const noexcept override {
            return "Error: Balance cannot be less than 1500";
        }
    };

    class withdrawException : public exception {
    public:
        const char* what() const noexcept override {
            return "Error: Not enough balance";
        }
    };

    class negativeValueException : public exception {
    public:
        const char* what() const noexcept override {
            return "Error: Cannot use negative values";
        }
    };

    Client(string name, string password, double balance)
            : Person(name, password, 'c') {
        try {
            if (Validate::isMinBalance(balance)) {
                this->balance = balance;
            } else {
                throw invalidBalanceException();
            }
        } catch (const invalidBalanceException& e) {
            cerr << e.what() << endl;
        }
    }

    void setBalance(const double& balance) {
        this->balance = balance;
    }

    const double& getBalance() {
        return balance;
    }

    void deposit(const double& value) {
        try {
            checkValue(value);
            this->balance += value;
        } catch (const negativeValueException& e) {
            cerr << e.what() << endl;
        }
    }

    void withdraw(const double& value) {
        try {
            checkValue(value);

            if (this->canWithdraw(value)) {
                this->balance -= value;
            } else {
                throw withdrawException();
            }
        } catch (const negativeValueException& e) {
            cerr << e.what() << endl;
        } catch (const withdrawException& e) {
            cerr << e.what() << endl;
        }
    }

    void transferTo(const double& value, Client& c) {
        try {
            checkValue(value);

            if (canWithdraw(value)) {
                c.deposit(value);
                this->withdraw(value);
            } else {
                throw withdrawException();
            }
        } catch (const negativeValueException& e) {
            cerr << e.what() << endl;
        } catch (const withdrawException& e) {
            cerr << e.what() << endl;
        }
    }

    void displayInfo() {
        Person::displayInfo();
        cout << this->balance;
    }
};

#endif //FINAL_PROJECT_CLIENT_H
