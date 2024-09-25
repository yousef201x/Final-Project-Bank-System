//
// Created by yousef on 9/12/2024.
//

#pragma once

#include <iostream>
#include <string>
#include "Validate.h"
#include "exception"
using namespace std;

class Person {
private:
    string generateID(char type) {
        string id{};
        string strUserCount = to_string(Validate::usersCount);
        switch(type) {
            case 'c':
                id = "C-" + strUserCount;
                break;
            case 'e':
                id = "E-" + strUserCount;
                break;
            case 'a':
                id = "A-" + strUserCount;
                break;
        }
        return id;
    }

protected:
    string name, password, id;

public:
    class invalidNameException : public exception {
    public:
        const char* what() const noexcept override {
            return "Error: Name cannot contain any numbers, spaces, or symbols and must be between 5 and 20 chars.";
        }
    };

    class invalidPasswordException : public exception {
    public:
        const char* what() const noexcept override {
            return "Error: Password must be between 8 and 20 characters.";
        }
    };

    Person(string name, string password, char type) {
        Validate::usersCount += 1;
        this->id = generateID(type);

        try {
            if (Validate::isValidName(name)) {
                this->name = name;
            } else {
                throw invalidNameException();
            }

            if (Validate::isStrInRange(password, 8, 20)) {
                this->password = password;
            } else {
                throw invalidPasswordException();
            }
        } catch (const invalidNameException& e) {
            cerr << e.what() << endl;
        } catch (const invalidPasswordException& e) {
            cerr << e.what() << endl;
        }
    }

    const string& getName() const {
        return name;
    }

    const string& getPassword() const {
        return password;
    }

    const string& getId() const {
        return id;
    }

    void setName(const string& name) {
        try {
            if (Validate::isValidName(name)) {
                this->name = name;
            } else {
                throw invalidNameException();
            }
        } catch (const invalidNameException& e) {
            cerr << e.what() << endl;
        }
    }

    void setPassword(const string& password) {
        try {
            if (Validate::isStrInRange(password, 8, 20)) {
                this->password = password;
            } else {
                throw invalidPasswordException();
            }
        } catch (const invalidPasswordException& e) {
            cerr << e.what() << endl;
        }
    }

    virtual void displayInfo() {
        cout << this->id << endl
             << this->name << endl;
    }
};

