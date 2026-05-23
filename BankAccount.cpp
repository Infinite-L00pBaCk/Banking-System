// ============================================================================
// BankAccount.cpp — Bank Account Class Implementation
// Banking System | Pinnacle Labs Internship
// ============================================================================

#include "BankAccount.h"
#include <iostream>
#include <sstream>
#include <iomanip>
#include <ctime>

BankAccount::BankAccount()
    : accountNumber(""), holderName(""), pin(""), balance(0.0),
      active(false), creationDate("") {}

BankAccount::BankAccount(const std::string& accNo, const std::string& name,
                         const std::string& pinCode, double initialDeposit)
    : accountNumber(accNo), holderName(name), pin(pinCode),
      balance(initialDeposit), active(true) {
    std::time_t now = std::time(nullptr);
    std::tm* localTime = std::localtime(&now);
    std::ostringstream oss;
    oss << std::put_time(localTime, "%Y-%m-%d %H:%M:%S");
    creationDate = oss.str();
}

std::string BankAccount::getAccountNumber() const { return accountNumber; }
std::string BankAccount::getHolderName() const { return holderName; }
double BankAccount::getBalance() const { return balance; }
bool BankAccount::isActive() const { return active; }
std::string BankAccount::getCreationDate() const { return creationDate; }

bool BankAccount::verifyPin(const std::string& inputPin) const {
    return pin == inputPin;
}

bool BankAccount::deposit(double amount) {
    if (amount <= 0) { std::cout << "\n  [!] Deposit amount must be positive.\n"; return false; }
    if (!active) { std::cout << "\n  [!] Cannot deposit to a closed account.\n"; return false; }
    balance += amount;
    return true;
}

bool BankAccount::withdraw(double amount) {
    if (amount <= 0) { std::cout << "\n  [!] Withdrawal amount must be positive.\n"; return false; }
    if (!active) { std::cout << "\n  [!] Cannot withdraw from a closed account.\n"; return false; }
    if (amount > balance) {
        std::cout << "\n  [!] Insufficient balance! Available: Rs. "
                  << std::fixed << std::setprecision(2) << balance << "\n";
        return false;
    }
    balance -= amount;
    return true;
}

void BankAccount::closeAccount() { active = false; balance = 0.0; }

std::string BankAccount::serialize() const {
    std::ostringstream oss;
    oss << accountNumber << "|" << holderName << "|" << pin << "|"
        << std::fixed << std::setprecision(2) << balance << "|"
        << (active ? "1" : "0") << "|" << creationDate;
    return oss.str();
}

BankAccount BankAccount::deserialize(const std::string& line) {
    BankAccount acc;
    std::istringstream iss(line);
    std::string balStr, activeStr;
    std::getline(iss, acc.accountNumber, '|');
    std::getline(iss, acc.holderName, '|');
    std::getline(iss, acc.pin, '|');
    std::getline(iss, balStr, '|');
    std::getline(iss, activeStr, '|');
    std::getline(iss, acc.creationDate);
    acc.balance = std::stod(balStr);
    acc.active = (activeStr == "1");
    return acc;
}

void BankAccount::displayAccountInfo() const {
    std::cout << "\n  +==========================================+\n";
    std::cout << "  |          ACCOUNT INFORMATION             |\n";
    std::cout << "  +==========================================+\n";
    std::cout << "  |  Account No  : " << std::left << std::setw(25) << accountNumber << "|\n";
    std::cout << "  |  Holder Name : " << std::left << std::setw(25) << holderName << "|\n";
    std::cout << "  |  Balance     : Rs. " << std::left << std::setw(21)
              << std::fixed << std::setprecision(2) << balance << "|\n";
    std::cout << "  |  Status      : " << std::left << std::setw(25)
              << (active ? "ACTIVE" : "CLOSED") << "|\n";
    std::cout << "  |  Opened On   : " << std::left << std::setw(25) << creationDate << "|\n";
    std::cout << "  +==========================================+\n";
}
