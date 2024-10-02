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
    cout << boolalpha << cursor.addClient(c) << endl;

    Employee e("yousef","12345677",5000);
    cout << boolalpha << cursor.addEmployee(e) << endl;

    Admin a("yousef","12345677",5000);
    cout << boolalpha << cursor.addAdmin(a) << endl;

    // Close Database Connection
    cursor.close();



}
