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

class FileManager {
private:
    std::string accountsFile;
    std::string transactionsFile;

public:
    FileManager(const std::string& accFile = "accounts.dat",
                const std::string& txnFile = "transactions.dat");

    // Account file operations
    void saveAccounts(const std::vector<BankAccount>& accounts) const;
    std::vector<BankAccount> loadAccounts() const;

    // Transaction file operations
    void appendTransaction(const Transaction& txn) const;
    std::vector<Transaction> loadTransactions() const;
    std::vector<Transaction> getTransactionsForAccount(const std::string& accNo) const;
};

#endif // FILEMANAGER_H
