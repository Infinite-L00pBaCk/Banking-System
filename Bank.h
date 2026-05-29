// ============================================================================
// Bank.h — Bank Manager Class Declaration
// Banking System | Pinnacle Labs Internship
// ============================================================================

#ifndef BANK_H
#define BANK_H

#include <string>
#include <vector>
#include "BankAccount.h"
#include "Transaction.h"
#include "FileManager.h"

class Bank {
private:
    std::string bankName;
    std::vector<BankAccount> accounts;
    FileManager fileManager;
    int nextAccountId;

    // Generate a unique account number
    std::string generateAccountNumber();

    // Find account index by account number (-1 if not found)
    int findAccountIndex(const std::string& accNo) const;

public:
    Bank(const std::string& name = "Pinnacle National Bank");

    // Account management
    void createAccount();
    void viewAccountDetails();
    void closeAccount();
    void listAllAccounts();

    // Banking operations
    void deposit();
    void withdraw();
    void transfer();
    void checkBalance();

    // Transaction history
    void viewTransactionHistory();

    // Persistence
    void saveData();
    void loadData();
};

#endif // BANK_H
