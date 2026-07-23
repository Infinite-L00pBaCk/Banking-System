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

/**
 * @class Bank
 * @brief Manages the overall banking system operations.
 *
 * This class coordinates the creation of accounts, banking operations
 * (deposit, withdrawal, transfer), and interaction with the file system
 * for persistence.
 */
class Bank {
private:
    std::string bankName;              ///< Name of the bank
    std::vector<BankAccount> accounts; ///< List of all bank accounts
    FileManager fileManager;           ///< Handles file storage
    int nextAccountId;                 ///< Counter for assigning unique IDs

    /**
     * @brief Generates a unique account number.
     * @return A string representing the new account number.
     */
    std::string generateAccountNumber();

    /**
     * @brief Finds the index of an account in the accounts vector.
     * @param accNo The account number to search for.
     * @return Index of the account, or -1 if not found.
     */
    int findAccountIndex(const std::string& accNo) const;

public:
    /**
     * @brief Constructor for the Bank class.
     * @param name Name of the bank. Defaults to "Pinnacle National Bank".
     */
    Bank(const std::string& name = "Pinnacle National Bank");

    // Account management
    
    /**
     * @brief Prompts user to create a new bank account.
     */
    void createAccount();

    /**
     * @brief Displays details of an account after PIN verification.
     */
    void viewAccountDetails();

    /**
     * @brief Closes an existing account.
     */
    void closeAccount();

    /**
     * @brief Lists all accounts in the bank.
     */
    void listAllAccounts();

    // Banking operations
    
    /**
     * @brief Handles the deposit of funds into an account.
     */
    void deposit();

    /**
     * @brief Handles the withdrawal of funds from an account.
     */
    void withdraw();

    /**
     * @brief Transfers funds between two accounts.
     */
    void transfer();

    /**
     * @brief Checks and displays the balance of an account.
     */
    void checkBalance();

    // Transaction history
    
    /**
     * @brief Displays the transaction history for an account.
     */
    void viewTransactionHistory();

    // Persistence
    
    /**
     * @brief Saves all bank data (accounts and transactions) to files.
     */
    void saveData();

    /**
     * @brief Loads all bank data from files into memory.
     */
    void loadData();
};

#endif // BANK_H
