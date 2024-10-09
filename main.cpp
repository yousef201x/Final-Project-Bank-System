#include <iostream>
#include "headerFiles/Schema.h"
#include "headerFiles/Client.h"
#include "headerFiles/Employee.h"
#include "headerFiles/Admin.h"
#include "headerFiles/CLI.h"

using namespace std;

template <typename Ty>
char handleUser(Ty* user) {
    if constexpr (is_same_v<Ty, Client>) {
        return 'c';
    } else if constexpr (is_same_v<Ty, Employee>) {
        return 'e';
    } else if constexpr (is_same_v<Ty, Admin>) {
        return 'a';
    }
}

int main() {
    char userType{};
    CLI::welcome();
    Person* user = CLI::login();

    if (Client* clientUser = dynamic_cast<Client*>(user)) {
        userType  = handleUser(clientUser);
    } else if (Employee* employeeUser = dynamic_cast<Employee*>(user)) {
        userType  = handleUser(employeeUser);
    } else if (Admin* adminUser = dynamic_cast<Admin*>(user)) {
        userType  = handleUser(adminUser);
    }

    delete user;
    return 0;
}
