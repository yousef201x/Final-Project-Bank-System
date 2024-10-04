#include <iostream>
#include "headerFiles/Client.h"
#include "headerFiles/Employee.h"
#include "headerFiles/Admin.h"
#include "headerFiles/DataBaseManager.h"
#include "startDB.h"
#include "headerFiles/Schema.h"
using namespace std;

int main(){
    DataBaseManager cursor  = startDB();

    Client c("yousef","12345677",1500);
    cursor.insertTo("clients",c);

    Employee e("yousef","12345677",5000);
    cursor.insertTo("employees",e);

    Admin a("yousef","12345677",5000);
    cursor.insertTo("admins",a);

    // Fetch all clients data
    cursor.all("clients");

    // Search By id
    cursor.findById("clients",150);

    // Fetch all employees data
    cursor.all("employees");

    // Fetch all admins data
    cursor.all("admins");

    // Remove all clients data
    cursor.clear("clients");

    // Remove all employees data
    cursor.clear("employees");

    // Remove all admins data
    cursor.clear("admins");

    cout << cursor.isFound("clients",150);

    cursor.update("clients",150,"1","yousef",10000000);

    cursor.update("clients",150,"Joeseeff","joeeee201x");

    cursor.destroy("clients",150);

    cursor.findById("clients",151);


    Schema::insertTo("clients",c);
    Schema::updateColumn("clients","name",186,"aaaaaaaaa");
    Schema::destroy("clients",190);
    Schema::findById("clients",186);
    Schema::all("clients");

    // Close Database Connection
    cursor.close();

}
