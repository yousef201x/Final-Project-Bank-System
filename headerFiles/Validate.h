//
// Created by yousef on 9/12/2024.
//

#ifndef FINAL_PROJECT_VALIDATE_H
#define FINAL_PROJECT_VALIDATE_H


#pragma once

#include <iostream>
#include <string>
using namespace std;

class Validate
{
public:
    static bool isValidName(const string& value, int min = 5, int max = 20)
    {
        // Check length of the string
        if (!(value.length() >= min && value.length() <= max))
        {
            return false;
        }

        // Check if all characters are alphabetic
        for (int i = 0; i < value.length(); i++)
        {
            if (!isalpha(value[i]) || isspace(value[i]))
            {
                return false;
            }
        }

        return true;
    }


    static bool isStrInRange(const string& value, int min = 5, int max = 20)
    {
        return value.length() >= min && value.length() <= max;
    }


    static bool isMinBalance(double& value , double min = 1500){
        return (value >= min);
    }

};


#endif //FINAL_PROJECT_VALIDATE_H
