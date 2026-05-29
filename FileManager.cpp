// ============================================================================
// FileManager.cpp — File I/O Handler Implementation
// Banking System | Pinnacle Labs Internship
// ============================================================================

#include "FileManager.h"
#include <fstream>
#include <iostream>

FileManager::FileManager(const std::string& accFile, const std::string& txnFile)
    : accountsFile(accFile), transactionsFile(txnFile) {}

// --- Account File Operations ---

void FileManager::saveAccounts(const std::vector<BankAccount>& accounts) const {
    std::ofstream outFile(accountsFile, std::ios::trunc);
    if (!outFile.is_open()) {
        std::cerr << "  [ERROR] Could not open " << accountsFile << " for writing.\n";
        return;
    }
    for (const auto& acc : accounts) {
        outFile << acc.serialize() << "\n";
    }
    outFile.close();
}

std::vector<BankAccount> FileManager::loadAccounts() const {
    std::vector<BankAccount> accounts;
    std::ifstream inFile(accountsFile);
    if (!inFile.is_open()) {
        // File doesn't exist yet — not an error on first run
        return accounts;
    }
    std::string line;
    while (std::getline(inFile, line)) {
        if (!line.empty()) {
            accounts.push_back(BankAccount::deserialize(line));
        }
    }
    inFile.close();
    return accounts;
}

// --- Transaction File Operations ---

void FileManager::appendTransaction(const Transaction& txn) const {
    std::ofstream outFile(transactionsFile, std::ios::app);
    if (!outFile.is_open()) {
        std::cerr << "  [ERROR] Could not open " << transactionsFile << " for writing.\n";
        return;
    }
    outFile << txn.serialize() << "\n";
    outFile.close();
}

std::vector<Transaction> FileManager::loadTransactions() const {
    std::vector<Transaction> transactions;
    std::ifstream inFile(transactionsFile);
    if (!inFile.is_open()) {
        return transactions;
    }
    std::string line;
    while (std::getline(inFile, line)) {
        if (!line.empty()) {
            transactions.push_back(Transaction::deserialize(line));
        }
    }
    inFile.close();
    return transactions;
}

std::vector<Transaction> FileManager::getTransactionsForAccount(const std::string& accNo) const {
    std::vector<Transaction> allTxns = loadTransactions();
    std::vector<Transaction> filtered;
    for (const auto& txn : allTxns) {
        if (txn.accountNumber == accNo) {
            filtered.push_back(txn);
        }
    }
    return filtered;
}
