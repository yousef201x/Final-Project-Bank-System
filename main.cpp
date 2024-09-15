#include <iostream>
#include "headerFiles/Utility.h"
#include "headerFiles/Person.h"
#include "headerFiles/Client.h"
#include "headerFiles/Employee.h"
#include "headerFiles/Admin.h"
using namespace std;

int Utility::usersCount = 0 ;

int main(){
    Client c1("Yousef","12345678",1500);
    Client c2("Yousef","12345678",1500);
    Employee e ("Yousef","12345678",5000);
    Admin a ("Yousef","12345678",5000);
}