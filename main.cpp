#include <iostream>
#include "headerFiles/Validate.h"
#include "headerFiles/Person.h"
#include "headerFiles/Client.h"
#include "headerFiles/Employee.h"
#include "headerFiles/Admin.h"
#include "headerFiles/DataBaseManager.h"

using namespace std;


int main(){
    string dbName = "DB.db"; // Database File Name
    DataBaseManager cursor(dbName);

    // Open connection with database
    cursor.open();

    // Build All Tables
    cursor.buildTables();


    Client c("yousef","12345677",1500);
    cursor.insertTo("clients",c);

    Employee e("yousef","12345677",5000);
    cursor.insertTo("employees",e);

    Admin a("yousef","12345677",5000);
    cursor.insertTo("admins",a);



    // Fetch all clients data
    cursor.all("clients");

    // Fetch all employees data
    cursor.all("employees");

    // Fetch all admins data
    cursor.all("admins");

    // Remove all clients data
    cursor.removeAll("clients");

    // Remove all employees data
    cursor.removeAll("employees");

    // Remove all admins data
    cursor.removeAll("admins");

    // Add new client from Employee class
    e.addClient(c,cursor.getDb(),dbName);
    // or
    e.addClient(c,cursor.getDb());

    // List all clients from Employee class
    e.listClients(cursor.getDb());
    // or
    e.listClients(cursor.getDb());

    // Search client by name
    e.findClient("y",cursor.getDb());

    // Search Client by name
    e.findClient(123,cursor.getDb());


    // Close Database Connection
    cursor.close();

}
