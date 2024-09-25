//
// Created by yousef on 9/15/2024.
//

#ifndef FINAL_PROJECT_EMPLOYEE_H
#define FINAL_PROJECT_EMPLOYEE_H

#include "Person.h"

class Employee : public Person {
protected:
    double salary{};
public:
    class invalidSalaryException : public exception {
    public:
        const char* what() const noexcept override {
            return "Error: Salary cannot be less than 5000";
        }
    };

    Employee(string name, string password, double salary, char type = 'e')
            : Person(name, password, type) {
        try {
            if (Validate::isMinBalance(salary, 5000)) {
                this->salary = salary;
            } else {
                throw invalidSalaryException();
            }
        } catch (const invalidSalaryException& e) {
            cerr << e.what() << endl;
        }
    }

    const double& getSalary() {
        return salary;
    }

    void displayInfo() override {
        Person::displayInfo();
        cout << this->salary;
    }
};

#endif //FINAL_PROJECT_EMPLOYEE_H
