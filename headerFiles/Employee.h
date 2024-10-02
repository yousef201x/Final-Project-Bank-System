//
// Created by yousef on 9/15/2024.
//

#ifndef FINAL_PROJECT_EMPLOYEE_H
#define FINAL_PROJECT_EMPLOYEE_H

#include "Person.h"

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
};


#endif //FINAL_PROJECT_EMPLOYEE_H

