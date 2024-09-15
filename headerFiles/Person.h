//
// Created by yousef on 9/12/2024.
//

#pragma once

#include <iostream>
#include <string>
#include "Utility.h"
#include "exception"
using namespace std;

class Person
{
private:
    string generateID(char type)
    {
        string id{};
        string strUserCount = to_string(Utility::usersCount);
        switch(type)
        {
            case 'c' :
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
    string name, password , id;
public:
    class invalidNameException : public exception{
    public:
        const char * what() const noexcept override {
            return "Error: Name cannot contain any numbers or symbols and must be between 5 and 20 chars";
        }
    };

    class invalidPasswordException : public exception{
    public:
        const char * what() const noexcept override {
            return "Error: Password must be between 8 and 20 chars";
        }
    };

    Person(string name, string password , char type )
    {
        Utility::usersCount += 1;
        this->id = generateID(type);

        if(Utility::isValidName(name)){
            this->name = name ;
        }
        else{
            throw invalidNameException();
        }

        if(Utility::isStrInRange(password,8,20)){
            this->password = password ;
        }
        else{
            throw invalidPasswordException();
        }
    }

    const string &getName() const {
        return name;
    }

    const string &getPassword() const {
        return password;
    }

    const string &getId() const {
        return id;
    }

    void setName(const string &name) {
        if(Utility::isValidName(name)){
            this->name = name ;
        }
        else{
            throw invalidNameException();
        }

    }

    void setPassword(const string &password) {
        if(Utility::isStrInRange(password,8,20)){
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



