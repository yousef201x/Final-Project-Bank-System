#include <iostream>
#include "headerFiles/Schema.h"
#include "headerFiles/Client.h"
#include "headerFiles/Employee.h"
#include "headerFiles/Admin.h"
using namespace std;
int main(){
    Client c("yousef","123456789",1500);
    Employee e("yousef","123456789",5000);
    Admin a("yousef","123456789",5000);

    // Insert data

    Schema::insertTo<Client>("clients",c);
    Schema::insertTo<Admin>("admins",a);
    Schema::insertTo<Employee>("employees",e);

    // Update data

    Schema::updateColumn("clients","name",273,"updatename");
    Schema::updateColumn("clients","balance",273,6000);
    Schema::updateColumn("admins","name",74,"updatename");

    // Delete record

    Schema::destroy("clients",274);

    // Clear table

    Schema::clear("employees");
}
