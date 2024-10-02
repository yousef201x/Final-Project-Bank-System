//
// Created by yousef on 10/2/2024.
//

#ifndef FINAL_PROJECT_DATABASEMANAGER_H
#define FINAL_PROJECT_DATABASEMANAGER_H

#pragma once
#include "DataBase.h"
#include "Client.h"

class DataBaseManager : public DataBase
{
public:
    // Constructor: takes the name of the database file
    DataBaseManager(const string& name) : DataBase(name) {}


    // Destructor: ensures the database is closed
    ~DataBaseManager() {
        close();
    }
};


#endif //FINAL_PROJECT_DATABASEMANAGER_H
