// ============================================================================
// BankAccount.h — Bank Account Class Declaration
// Banking System | Pinnacle Labs Internship
// ============================================================================

#ifndef BANKACCOUNT_H
#define BANKACCOUNT_H

#include <string>
#include <vector>
#include "Transaction.h"

class BankAccount {
private:
    std::string accountNumber;
    std::string holderName;
    std::string pin;           // 4-digit PIN for authentication
    double balance;
    bool active;               // Whether the account is open/active
    std::string creationDate;

public:
    // Constructors
    BankAccount();
    BankAccount(const std::string& accNo, const std::string& name,
                const std::string& pin, double initialDeposit);

    // Getters
    std::string getAccountNumber() const;
    std::string getHolderName() const;
    double getBalance() const;
    bool isActive() const;
    std::string getCreationDate() const;

    // Account operations
    bool verifyPin(const std::string& inputPin) const;
    bool deposit(double amount);
    bool withdraw(double amount);
    void closeAccount();

    // Serialization for file storage
    std::string serialize() const;
    static BankAccount deserialize(const std::string& line);

    // Display
    void displayAccountInfo() const;
};

#endif // BANKACCOUNT_H
