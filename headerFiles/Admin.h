//
// Created by yousef on 9/15/2024.
//

#ifndef FINAL_PROJECT_ADMIN_H
#define FINAL_PROJECT_ADMIN_H

#include "Employee.h"


class Admin : public Employee{
public:
    Admin(string name, string password, double salary)
    : Employee(name, password,salary)
    {}
};

#endif //FINAL_PROJECT_ADMIN_H