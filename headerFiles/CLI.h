#ifndef FINAL_PROJECT_CLI_H
#define FINAL_PROJECT_CLI_H
#include <iostream>
using namespace std;


class CLI{
public:
    static void welcome(){

        cout << "\n\n";
        cout << "    @@       @@  @@@@@@@  @@      @@@@@@@  @@@@@@@@  @@@@    @@@@  @@@@@@@   \n";
        cout << "    @@   @   @@  @@       @@      @@       @@    @@  @@  @  @  @@  @@		  \n";
        cout << "    @@  @@@  @@  @@@@@@   @@      @@       @@    @@  @@   @@   @@  @@@@@@	  \n";
        cout << "    @@ @@ @@ @@  @@       @@      @@       @@    @@  @@        @@  @@         \n";
        cout << "    @@@     @@@  @@@@@@@  @@@@@@  @@@@@@@  @@@@@@@@  @@        @@  @@@@@@@     \n";
    }

    static Person* login() {
        int choice;
        char confirm;
        bool confirmed = false;

        while (!confirmed) {
            cout << "\n\nSelect a role to log in:\n";
            cout << "1. Client\n";
            cout << "2. Employee\n";
            cout << "3. Admin\n";
            cout << "Enter your choice (1-3): ";

            cin >> choice;

            switch (choice) {
                case 1: {
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
                            confirmed = true;
                            return user; // Return the logged-in Client
                        } else {
                            delete user; // Clean up if login failed
                        }
                    } else {
                        cout << "\nLogin canceled. Returning to the menu...\n";
                    }
                    break;
                }
                case 2: {
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
                            confirmed = true;
                            return user; // Return the logged-in Employee
                        } else {
                            delete user; // Clean up if login failed
                        }
                    } else {
                        cout << "\nLogin canceled. Returning to the menu...\n";
                    }
                    break;
                }
                case 3: {
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
                            confirmed = true;
                            return user; // Return the logged-in Admin
                        } else {
                            delete user; // Clean up if login failed
                        }
                    } else {
                        cout << "\nLogin canceled. Returning to the menu...\n";
                    }
                    break;
                }
                default:
                    cout << "\nInvalid choice. Please select a valid option.\n";
                    break;
            }
        }

        return nullptr; // Return nullptr if login fails or user cancels
    }




};

#endif //FINAL_PROJECT_CLI_H
