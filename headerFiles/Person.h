//
// Created by yousef on 9/12/2024.
//

#pragma once

#include <iostream>
#include <string>
#include "Validate.h"
#include "exception"

using namespace std;
class Person
{
protected:
    string name, password ;
    int id;
public:
    class invalidNameException : public exception{
    public:
        const char * what() const noexcept override {
            return "Error: Name cannot contain any numbers or spaces or symbols and must be between 5 and 20 chars";
        }
    };

    class invalidPasswordException : public exception{
    public:
        const char * what() const noexcept override {
            return "Error: Password must be between 8 and 20 chars";
        }
    };

    Person(int id, string name, string password)
            : id(id), name(name), password(password)
    {}

    Person(const Person& other)
            : id(other.getId()), name(other.getName()), password(other.getPassword()) {}

    const string &getName() const {
        return name;
    }

    const string &getPassword() const {
        return password;
    }

    const int &getId() const {
        return id;
    }

    void setName(const string &name) {
        if(Validate::isValidName(name)){
            this->name = name ;
        }
        else{
            throw invalidNameException();
        }

    }

    void setPassword(const string &password) {
        if(Validate::isStrInRange(password, 8, 20)){
            this->password = password ;
        }
        else{
            throw invalidPasswordException();
        }
    }

    virtual void displayInfo(){
        cout
                << this->id << endl
                << this->name << endl;
    }
};