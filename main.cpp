#include <iostream>
#include <string>
#include "headerFiles/Schema.h"
#include "headerFiles/Client.h"
#include "headerFiles/Employee.h"
#include "headerFiles/Admin.h"
#include "headerFiles/Response.h"
#include "headerFiles/Validate.h"

using namespace std;

void welcome(){

    cout << "\n\n";
    cout << "    @@       @@  @@@@@@@  @@      @@@@@@@  @@@@@@@@  @@@@    @@@@  @@@@@@@   \n";
    cout << "    @@   @   @@  @@       @@      @@       @@    @@  @@  @  @  @@  @@		  \n";
    cout << "    @@  @@@  @@  @@@@@@   @@      @@       @@    @@  @@   @@   @@  @@@@@@	  \n";
    cout << "    @@ @@ @@ @@  @@       @@      @@       @@    @@  @@        @@  @@         \n";
    cout << "    @@@     @@@  @@@@@@@  @@@@@@  @@@@@@@  @@@@@@@@  @@        @@  @@@@@@@     \n";
}

// Function to handle client options
void handleClientOptions(Client* clientUser) {
    double amount;
    int userId;

    while (true) {
        cout << "\nClient Options:\n";
        cout << "1. View Balance\n";
        cout << "2. Deposit\n";
        cout << "3. Withdraw\n";
        cout << "4. Transfer to another Client\n";
        cout << "5. Logout\n";
        cout << "Enter your choice: ";

        int choice;
        cin >> choice;

        switch (choice) {
            case 1: {
                // Handle viewing balance
                cout << "Your balance is: " << Client::returnById(clientUser->getId()).second.getBalance() << endl;
                break;
            }
            case 2: {
                // Handle deposit
                cout << "Enter amount to deposit: ";
                cin >> amount;
                if (Validate::isAmountPositive(amount)) {
                    clientUser->deposit(amount);
                    cout << Response::DEPOSITE_SUCCESS;
                } else {
                    cout << Response::NOT_POSITIVE_AMOUNT;
                }
                break;
            }
            case 3: {
                // Handle withdraw
                cout << "Enter amount to withdraw: ";
                cin >> amount;
                if (Validate::isAmountPositive(amount)) {
                    if (clientUser->withdraw(amount).first) {
                        cout << Response::WITHDRAW_SUCCESS;
                    } else {
                        cout << Response::INSUFFICIENT_BALANCE;
                    }
                } else {
                    cout << Response::NOT_POSITIVE_AMOUNT;
                }
                break;
            }
            case 4: {
                // Handle transfer to another client
                cout << "Enter amount to transfer: ";
                cin >> amount;
                cout << "Enter User ID: ";
                cin >> userId;

                if (Validate::isAmountPositive(amount)) {
                    if (clientUser->transferTo(amount, userId).first) {
                        cout << Response::TRANSFER_SUCCESS;
                    } else {
                        cout << Response::INSUFFICIENT_BALANCE;
                    }
                } else {
                    cout << Response::NOT_POSITIVE_AMOUNT;
                }
                break;
            }
            case 5: {
                cout << "Logging out...\n";
                return; // Exit to main menu
            }
            default:
                cout << Response::INVALID_OPTION;
        }
    }
}

// Function to handle employee options
void handleEmployeeOptions(Employee* employeeUser) {
    while (true) {
        cout << "\nEmployee Options:\n";
        cout << "1. List Clients\n";
        cout << "2. Search Client\n";
        cout << "3. Edit Client Name\n";
        cout << "4. Edit Client Password\n";
        cout << "5. Logout\n";
        cout << "Enter your choice: ";

        int choice;
        cin >> choice;

        switch (choice) {
            case 1: {
                employeeUser->listClients();
                break;
            }
            case 2: {
                int id;
                cout << "Enter Client ID to search: ";
                cin >> id;
                employeeUser->searchClient(id);
                break;
            }
            case 3: {
                int id;
                string name;
                cout << "Enter Client ID: ";
                cin >> id;
                cout << "Enter new name: ";
                cin >> name;
                employeeUser->editClientName(id, name);
                break;
            }
            case 4: {
                int id;
                string password;
                cout << "Enter Client ID: ";
                cin >> id;
                cout << "Enter new password: ";
                cin >> password;
                employeeUser->editClientPassword(id, password);
                break;
            }
            case 5: {
                cout << "Logging out...\n";
                return; // Exit to main menu
            }
            default:
                cout << Response::INVALID_OPTION;
        }
    }
}

// Function to handle admin options
void handleAdminOptions(Admin* adminUser) {
    while (true) {
        cout << "\nAdmin Options:\n";
        cout << "1. Add Employee\n";
        cout << "2. Search Employee\n";
        cout << "3. List Employees\n";
        cout << "4. Edit Employee Name\n";
        cout << "5. Edit Employee Password\n";
        cout << "6. Edit Employee Salary\n";
        cout << "7. Logout\n";
        cout << "Enter your choice: ";

        int choice;
        cin >> choice;

        switch (choice) {
            case 1: {
                int id = 0;
                string name, password;
                double salary;

                cout << "Enter Employee Name: ";
                cin >> name;
                cout << "Enter Employee Password: ";
                cin >> password;
                cout << "Enter Employee Salary: ";
                cin >> salary;

                Employee newEmployee(id, name, password, salary);

                if(adminUser->addEmployee(newEmployee).first){
                    cout << "Employee added successfully!\n";
                }else{
                    cout << Response::FAILURE;
                }

                break;
            }
            case 2: {
                int id;
                cout << "Enter Employee ID to search: ";
                cin >> id;
                adminUser->searchEmployee(id);
                break;
            }
            case 3: {
                adminUser->listEmployees();
                break;
            }
            case 4: {
                int id;
                string name;
                cout << "Enter Employee ID: ";
                cin >> id;
                cout << "Enter new name: ";
                cin >> name;
                adminUser->editEmployeeName(id, name);
                break;
            }
            case 5: {
                int id;
                string password;
                cout << "Enter Employee ID: ";
                cin >> id;
                cout << "Enter new password: ";
                cin >> password;
                adminUser->editEmployeePassword(id, password);
                break;
            }
            case 6: {
                int id;
                double salary;
                cout << "Enter Employee ID: ";
                cin >> id;
                cout << "Enter new salary: ";
                cin >> salary;
                adminUser->editEmployeeSalary(id, salary);
                break;
            }
            case 7: {
                cout << "Logging out...\n";
                return; // Exit to main menu
            }
            default:
                cout << Response::INVALID_OPTION;
        }
    }
}

int main() {
    welcome();

    int choice;
    char confirm;
    Person* loggedInUser = nullptr;  // Unified pointer for any logged-in user

    while (true) {
        cout << "\nSelect a role to log in:\n";
        cout << "1. Client\n";
        cout << "2. Employee\n";
        cout << "3. Admin\n";
        cout << "4. Exit\n";
        cout << "Enter your choice (1-4): ";

        cin >> choice;

        switch (choice) {
            case 1: {  // Client login
                cout << "\nYou selected: Client. Are you sure you want to login as Client? (y/n): ";
                cin >> confirm;
                if (confirm == 'y' || confirm == 'Y') {
                    int id;
                    string password;

                    cout << "Enter Client ID: ";
                    cin >> id;
                    cout << "Enter Password: ";
                    cin >> password;

                    Client* user = new Client(Client::login(id, password));

                    if (user->getId() != -1) {
                        cout << "\nLogged in successfully as Client: " << user->getName() << endl;
                        loggedInUser = user;  // Store the logged-in user
                        handleClientOptions(user);
                    } else {
                        delete user;
                        cout << "\nLogin failed. Please try again.\n";
                    }
                } else {
                    cout << "\nLogin canceled. Returning to the menu...\n";
                }
                break;
            }
            case 2: {  // Employee login
                cout << "\nYou selected: Employee. Are you sure you want to login as Employee? (y/n): ";
                cin >> confirm;
                if (confirm == 'y' || confirm == 'Y') {
                    int id;
                    string password;

                    cout << "Enter Employee ID: ";
                    cin >> id;
                    cout << "Enter Password: ";
                    cin >> password;

                    Employee* user = new Employee(Employee::login(id, password));

                    if (user->getId() != -1) {
                        cout << "\nLogged in successfully as Employee: " << user->getName() << endl;
                        loggedInUser = user;  // Store the logged-in user
                        handleEmployeeOptions(user);
                    } else {
                        delete user;
                        cout << "\nLogin failed. Please try again.\n";
                    }
                } else {
                    cout << "\nLogin canceled. Returning to the menu...\n";
                }
                break;
            }
            case 3: {  // Admin login
                cout << "\nYou selected: Admin. Are you sure you want to login as Admin? (y/n): ";
                cin >> confirm;
                if (confirm == 'y' || confirm == 'Y') {
                    int id;
                    string password;

                    cout << "Enter Admin ID: ";
                    cin >> id;
                    cout << "Enter Password: ";
                    cin >> password;

                    Admin* user = new Admin(Admin::login(id, password));

                    if (user->getId() != -1) {
                        cout << "\nLogged in successfully as Admin: " << user->getName() << endl;
                        loggedInUser = user;  // Store the logged-in user
                        handleAdminOptions(user);
                    } else {
                        delete user;
                        cout << "\nLogin failed. Please try again.\n";
                    }
                } else {
                    cout << "\nLogin canceled. Returning to the menu...\n";
                }
                break;
            }
            case 4: {
                cout << "Exiting program...\n";
                return 0;
            }
            default:
                cout << Response::INVALID_OPTION;
        }

        // Cleanup after each user session
        delete loggedInUser;
        loggedInUser = nullptr;
    }

    return 0;
}
