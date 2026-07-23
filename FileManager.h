// ============================================================================
// FileManager.h — File I/O Handler Declaration
// Banking System | Pinnacle Labs Internship
// ============================================================================

#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include <string>
#include <vector>
#include "BankAccount.h"
#include "Transaction.h"

/**
 * @class FileManager
 * @brief Handles file persistence for accounts and transactions.
 *
 * This class abstracts the file operations required to save and load
 * data, ensuring that banking records survive across program restarts.
 */
class FileManager {
private:
    std::string accountsFile;      ///< Path to the accounts data file
    std::string transactionsFile;  ///< Path to the transactions data file

public:
    /**
     * @brief Constructor for FileManager.
     * @param accFile Filename for storing account records (default: accounts.dat).
     * @param txnFile Filename for storing transaction records (default: transactions.dat).
     */
    FileManager(const std::string& accFile = "accounts.dat",
                const std::string& txnFile = "transactions.dat");

    // Account file operations
    
    /**
     * @brief Saves a list of bank accounts to the filesystem.
     * @param accounts Vector of BankAccount objects to save.
     */
    void saveAccounts(const std::vector<BankAccount>& accounts) const;

    /**
     * @brief Loads bank accounts from the filesystem.
     * @return Vector of populated BankAccount objects.
     */
    std::vector<BankAccount> loadAccounts() const;

    // Transaction file operations
    
    /**
     * @brief Appends a single transaction to the transaction log file.
     * @param txn The transaction record to append.
     */
    void appendTransaction(const Transaction& txn) const;

    /**
     * @brief Loads all transaction records from the filesystem.
     * @return Vector of all Transaction objects.
     */
    std::vector<Transaction> loadTransactions() const;

    /**
     * @brief Retrieves transaction history for a specific account.
     * @param accNo The account number to filter by.
     * @return Vector of transactions related to the account.
     */
    std::vector<Transaction> getTransactionsForAccount(const std::string& accNo) const;
};

#endif // FILEMANAGER_H
