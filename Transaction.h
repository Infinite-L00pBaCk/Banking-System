// ============================================================================
// Transaction.h — Transaction Record Structure
// Banking System | Pinnacle Labs Internship
// ============================================================================

#ifndef TRANSACTION_H
#define TRANSACTION_H

#include <string>
#include <ctime>
#include <sstream>
#include <iomanip>

/**
 * @enum TransactionType
 * @brief Categorizes the different types of banking transactions.
 */
enum class TransactionType {
    DEPOSIT,          ///< Money added to the account
    WITHDRAWAL,       ///< Money taken out of the account
    TRANSFER_IN,      ///< Money received from another account
    TRANSFER_OUT,     ///< Money sent to another account
    ACCOUNT_CREATION  ///< Initial deposit during account setup
};

/**
 * @struct Transaction
 * @brief Represents a single financial transaction.
 *
 * Stores all relevant details for an audit trail including type,
 * amount, timestamps, and the resulting balance.
 */
struct Transaction {
    std::string accountNumber;  ///< Account associated with this transaction
    TransactionType type;       ///< Type of transaction performed
    double amount;              ///< Monetary amount involved
    double balanceAfter;        ///< Account balance after the transaction
    std::string timestamp;      ///< Exact time the transaction occurred
    std::string description;    ///< Human-readable context or note

    /**
     * @brief Default constructor for Transaction.
     */
    Transaction();

    /**
     * @brief Parameterized constructor.
     * @param accNo The account number.
     * @param t The transaction type.
     * @param amt The transaction amount.
     * @param balAfter Balance remaining after this transaction.
     * @param desc A short description or note.
     */
    Transaction(const std::string& accNo, TransactionType t, double amt,
                double balAfter, const std::string& desc);

    /**
     * @brief Generates the current timestamp.
     * @return Formatted timestamp string (YYYY-MM-DD HH:MM:SS).
     */
    static std::string getCurrentTimestamp();

    /**
     * @brief Converts a TransactionType enum to a string.
     * @param t The transaction type.
     * @return String representation of the type.
     */
    static std::string typeToString(TransactionType t);

    /**
     * @brief Parses a string into a TransactionType enum.
     * @param s The string representation.
     * @return The corresponding TransactionType enum.
     */
    static TransactionType stringToType(const std::string& s);

    /**
     * @brief Serializes the transaction to a pipe-delimited string.
     * @return Serialized string for file storage.
     */
    std::string serialize() const;

    /**
     * @brief Deserializes a pipe-delimited string into a Transaction.
     * @param line The string to deserialize.
     * @return A populated Transaction object.
     */
    static Transaction deserialize(const std::string& line);

    /**
     * @brief Formats the transaction for console display.
     * @return A formatted, human-readable string.
     */
    std::string display() const;
};

#endif // TRANSACTION_H
