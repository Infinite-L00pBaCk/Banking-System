// ============================================================================
// BankAccount.h — Bank Account Class Declaration
// Banking System | Pinnacle Labs Internship
// ============================================================================

#ifndef BANKACCOUNT_H
#define BANKACCOUNT_H

#include <string>
#include <vector>
#include "Transaction.h"

/**
 * @class BankAccount
 * @brief Represents a single bank account with basic banking operations.
 *
 * This class handles individual account details such as balance, PIN,
 * and active status. It provides methods for depositing, withdrawing,
 * and verifying the account's PIN.
 */
class BankAccount {
private:
    std::string accountNumber; ///< Unique identifier for the account
    std::string holderName;    ///< Full name of the account holder
    std::string pin;           ///< 4-digit PIN for authentication
    double balance;            ///< Current account balance
    bool active;               ///< Whether the account is open/active
    std::string creationDate;  ///< Timestamp of account creation

public:
    /**
     * @brief Default constructor for BankAccount.
     */
    BankAccount();

    /**
     * @brief Parameterized constructor to create a new BankAccount.
     * @param accNo Unique account number.
     * @param name Full name of the account holder.
     * @param pin 4-digit security PIN.
     * @param initialDeposit Starting balance for the account.
     */
    BankAccount(const std::string& accNo, const std::string& name,
                const std::string& pin, double initialDeposit);

    // Getters
    std::string getAccountNumber() const;
    std::string getHolderName() const;
    double getBalance() const;
    bool isActive() const;
    std::string getCreationDate() const;

    // Account operations
    
    /**
     * @brief Verifies if the provided PIN matches the account's PIN.
     * @param inputPin The PIN to verify.
     * @return True if the PIN matches, false otherwise.
     */
    bool verifyPin(const std::string& inputPin) const;

    /**
     * @brief Deposits a specified amount into the account.
     * @param amount The amount to deposit (must be positive).
     * @return True if successful, false otherwise.
     */
    bool deposit(double amount);

    /**
     * @brief Withdraws a specified amount from the account.
     * @param amount The amount to withdraw (must be positive and <= balance).
     * @return True if successful, false otherwise.
     */
    bool withdraw(double amount);

    /**
     * @brief Closes the account by setting its active status to false.
     */
    void closeAccount();

    // Serialization for file storage
    
    /**
     * @brief Serializes the account data to a pipe-delimited string.
     * @return A string representing the account data.
     */
    std::string serialize() const;

    /**
     * @brief Deserializes a pipe-delimited string into a BankAccount object.
     * @param line The string to deserialize.
     * @return A BankAccount object populated with the data.
     */
    static BankAccount deserialize(const std::string& line);

    // Display
    
    /**
     * @brief Displays the account's details to the console.
     */
    void displayAccountInfo() const;
};

#endif // BANKACCOUNT_H
