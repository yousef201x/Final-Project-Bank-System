//
// Created by yousef on 10/12/2024.
//

#ifndef FINAL_PROJECT_RESPONSE_H
#define FINAL_PROJECT_RESPONSE_H

class Response{
public:
    static constexpr const char* SUCCESS = "\nSUCCESS\n";
    static constexpr const char* FAILURE = "\nFAILURE\n";
    static constexpr const char* USER_NOT_FOUND = "\nUser Not found\n";

    // Database expected Responses
    static constexpr const char* DB_CONNECTION_ERROR = "\nError: Could not connect to database !\n";
    static constexpr const char* DB_FAILED_TO_BUILD_TABLE = "\nError: Filed to build table !\n";
    static constexpr const char* DB_SQL_ERROR = "\nError: SQL error !\n";
    static constexpr const char* DB_FAILED_TO_PREPARE_STMT = "\nError: Could not connect to database !\n";
    static constexpr const char* DB_BUSY = "\nError: Database is locked. Retrying...\n";
    static constexpr const char* DB_FAILURE = "\nError: Database failure\n";
    static constexpr const char* DB_NO_ROWS_RETURNED = "\nNo data found !\n";
    static constexpr const char* DB_SUCCESS = "\nSUCCESS\n";

    // Validation errors
    static constexpr const char* NOT_VALID_NAME = "\nError: Not valid name !\n";
    static constexpr const char* NOT_VALID_PASSWORD = "\nError: Not valid password !\n";
    static constexpr const char* NOT_MIN_BALANCE = "\nError: Min balance is 1500 !\n";
    static constexpr const char* NOT_MIN_SALARY = "\nError: Min salary is 5000 !\n";
    static constexpr const char* NOT_POSITIVE_AMOUNT = "\nError: Amount is not positive !\n";

    // Login
    static constexpr const char* LOGIN_FAILURE = "\nInvalid credentials !\n";

    // Client expected Responses
    static constexpr const char* INSUFFICIENT_BALANCE = "\nFailure insufficient balance !\n";
    static constexpr const char* DEPOSITE_SUCCESS = "\nAmount deposited successfully!\n";
    static constexpr const char* WITHDRAW_SUCCESS = "\nAmount deposited successfully!\n";
    static constexpr const char* TRANSFER_SUCCESS = "\nAmount transferred successfully \n";

    // CLI expected errors
    static constexpr const char* INVALID_OPTION = "\nError: Unknown OPTION !\n";

};

#endif //FINAL_PROJECT_RESPONSE_H
