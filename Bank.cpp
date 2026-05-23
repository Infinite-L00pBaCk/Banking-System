// ============================================================================
// Bank.cpp — Bank Manager Class Implementation
// Banking System | Pinnacle Labs Internship
// ============================================================================

#include "Bank.h"
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <sstream>
#include <limits>

Bank::Bank(const std::string& name) : bankName(name), nextAccountId(1001) {
    loadData();
    for (const auto& acc : accounts) {
        std::string numPart = acc.getAccountNumber().substr(4);
        int id = std::stoi(numPart);
        if (id >= nextAccountId) nextAccountId = id + 1;
    }
}

std::string Bank::generateAccountNumber() {
    std::ostringstream oss;
    oss << "PNB-" << nextAccountId++;
    return oss.str();
}

int Bank::findAccountIndex(const std::string& accNo) const {
    for (int i = 0; i < static_cast<int>(accounts.size()); ++i) {
        if (accounts[i].getAccountNumber() == accNo) return i;
    }
    return -1;
}

// ============================================================================
// Account Management
// ============================================================================

void Bank::createAccount() {
    std::string name, pin, confirmPin;
    double initialDeposit;

    std::cout << "\n  +----------------------------------------+\n";
    std::cout << "  |        CREATE NEW ACCOUNT               |\n";
    std::cout << "  +----------------------------------------+\n";

    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    std::cout << "  Enter Full Name: ";
    std::getline(std::cin, name);
    if (name.empty()) { std::cout << "\n  [!] Name cannot be empty.\n"; return; }

    do {
        std::cout << "  Set 4-digit PIN: ";
        std::getline(std::cin, pin);
        if (pin.length() != 4 || pin.find_first_not_of("0123456789") != std::string::npos) {
            std::cout << "  [!] PIN must be exactly 4 digits. Try again.\n";
            continue;
        }
        std::cout << "  Confirm PIN: ";
        std::getline(std::cin, confirmPin);
        if (pin != confirmPin) std::cout << "  [!] PINs do not match. Try again.\n";
    } while (pin.length() != 4 || pin != confirmPin ||
             pin.find_first_not_of("0123456789") != std::string::npos);

    std::cout << "  Initial Deposit (min Rs. 500.00): Rs. ";
    std::cin >> initialDeposit;

    if (std::cin.fail()) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "\n  [!] Invalid amount entered.\n";
        return;
    }
    if (initialDeposit < 500.0) { std::cout << "\n  [!] Minimum initial deposit is Rs. 500.00\n"; return; }

    std::string accNo = generateAccountNumber();
    BankAccount newAccount(accNo, name, pin, initialDeposit);
    accounts.push_back(newAccount);

    Transaction txn(accNo, TransactionType::ACCOUNT_CREATION, initialDeposit,
                    initialDeposit, "Account created with initial deposit");
    fileManager.appendTransaction(txn);
    saveData();

    std::cout << "\n  +==========================================+\n";
    std::cout << "  |       ACCOUNT CREATED SUCCESSFULLY!      |\n";
    std::cout << "  +==========================================+\n";
    std::cout << "  |  Account No  : " << std::left << std::setw(25) << accNo << "|\n";
    std::cout << "  |  Holder      : " << std::left << std::setw(25) << name << "|\n";
    std::cout << "  |  Balance     : Rs. " << std::left << std::setw(21)
              << std::fixed << std::setprecision(2) << initialDeposit << "|\n";
    std::cout << "  +==========================================+\n";
    std::cout << "\n  [i] Please remember your Account Number and PIN!\n";
}

void Bank::viewAccountDetails() {
    std::string accNo, pin;
    std::cout << "\n  Enter Account Number: ";
    std::cin >> accNo;
    int idx = findAccountIndex(accNo);
    if (idx == -1) { std::cout << "\n  [!] Account not found.\n"; return; }
    std::cout << "  Enter PIN: ";
    std::cin >> pin;
    if (!accounts[idx].verifyPin(pin)) { std::cout << "\n  [!] Incorrect PIN. Access denied.\n"; return; }
    accounts[idx].displayAccountInfo();
}

void Bank::closeAccount() {
    std::string accNo, pin;
    std::cout << "\n  +----------------------------------------+\n";
    std::cout << "  |          CLOSE ACCOUNT                  |\n";
    std::cout << "  +----------------------------------------+\n";
    std::cout << "  Enter Account Number: ";
    std::cin >> accNo;
    int idx = findAccountIndex(accNo);
    if (idx == -1) { std::cout << "\n  [!] Account not found.\n"; return; }
    if (!accounts[idx].isActive()) { std::cout << "\n  [!] Account is already closed.\n"; return; }
    std::cout << "  Enter PIN: ";
    std::cin >> pin;
    if (!accounts[idx].verifyPin(pin)) { std::cout << "\n  [!] Incorrect PIN. Access denied.\n"; return; }

    char confirm;
    std::cout << "\n  [WARNING] This action is irreversible.\n";
    std::cout << "  Remaining balance Rs. " << std::fixed << std::setprecision(2)
              << accounts[idx].getBalance() << " will be returned.\n";
    std::cout << "  Are you sure? (y/n): ";
    std::cin >> confirm;

    if (confirm == 'y' || confirm == 'Y') {
        double finalBalance = accounts[idx].getBalance();
        accounts[idx].closeAccount();
        Transaction txn(accNo, TransactionType::WITHDRAWAL, finalBalance,
                        0.0, "Account closed - final balance returned");
        fileManager.appendTransaction(txn);
        saveData();
        std::cout << "\n  [OK] Account " << accNo << " has been closed successfully.\n";
        std::cout << "  [i] Rs. " << std::fixed << std::setprecision(2)
                  << finalBalance << " returned to account holder.\n";
    } else {
        std::cout << "\n  [i] Account closure cancelled.\n";
    }
}

void Bank::listAllAccounts() {
    std::cout << "\n  +----------------------------------------------------------------------+\n";
    std::cout << "  |                       ALL REGISTERED ACCOUNTS                        |\n";
    std::cout << "  +--------------+-------------------------+------------------+-----------+\n";
    std::cout << "  |  Account No  |  Holder Name            |  Balance         |  Status   |\n";
    std::cout << "  +--------------+-------------------------+------------------+-----------+\n";

    if (accounts.empty()) {
        std::cout << "  |                     No accounts registered yet.                      |\n";
    } else {
        for (const auto& acc : accounts) {
            std::cout << "  |  " << std::left << std::setw(12) << acc.getAccountNumber()
                      << "|  " << std::setw(24) << acc.getHolderName()
                      << "|  Rs. " << std::right << std::setw(11) << std::fixed
                      << std::setprecision(2) << acc.getBalance()
                      << " |  " << std::left << std::setw(8)
                      << (acc.isActive() ? "ACTIVE" : "CLOSED") << "|\n";
        }
    }
    std::cout << "  +----------------------------------------------------------------------+\n";
    std::cout << "  Total Accounts: " << accounts.size() << "\n";
}

// ============================================================================
// Banking Operations
// ============================================================================

void Bank::deposit() {
    std::string accNo;
    double amount;
    std::cout << "\n  +----------------------------------------+\n";
    std::cout << "  |            DEPOSIT FUNDS                |\n";
    std::cout << "  +----------------------------------------+\n";
    std::cout << "  Enter Account Number: ";
    std::cin >> accNo;
    int idx = findAccountIndex(accNo);
    if (idx == -1) { std::cout << "\n  [!] Account not found.\n"; return; }
    if (!accounts[idx].isActive()) { std::cout << "\n  [!] Cannot deposit to a closed account.\n"; return; }

    std::cout << "  Enter Deposit Amount: Rs. ";
    std::cin >> amount;
    if (std::cin.fail()) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "\n  [!] Invalid amount entered.\n";
        return;
    }

    if (accounts[idx].deposit(amount)) {
        Transaction txn(accNo, TransactionType::DEPOSIT, amount,
                        accounts[idx].getBalance(), "Cash deposit");
        fileManager.appendTransaction(txn);
        saveData();
        std::cout << "\n  [OK] Rs. " << std::fixed << std::setprecision(2) << amount
                  << " deposited successfully.\n";
        std::cout << "  [i] Updated Balance: Rs. " << std::fixed << std::setprecision(2)
                  << accounts[idx].getBalance() << "\n";
    }
}

void Bank::withdraw() {
    std::string accNo, pin;
    double amount;
    std::cout << "\n  +----------------------------------------+\n";
    std::cout << "  |          WITHDRAW FUNDS                 |\n";
    std::cout << "  +----------------------------------------+\n";
    std::cout << "  Enter Account Number: ";
    std::cin >> accNo;
    int idx = findAccountIndex(accNo);
    if (idx == -1) { std::cout << "\n  [!] Account not found.\n"; return; }
    if (!accounts[idx].isActive()) { std::cout << "\n  [!] Cannot withdraw from a closed account.\n"; return; }
    std::cout << "  Enter PIN: ";
    std::cin >> pin;
    if (!accounts[idx].verifyPin(pin)) { std::cout << "\n  [!] Incorrect PIN. Access denied.\n"; return; }

    std::cout << "  Available Balance: Rs. " << std::fixed << std::setprecision(2)
              << accounts[idx].getBalance() << "\n";
    std::cout << "  Enter Withdrawal Amount: Rs. ";
    std::cin >> amount;
    if (std::cin.fail()) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "\n  [!] Invalid amount entered.\n";
        return;
    }

    if (accounts[idx].withdraw(amount)) {
        Transaction txn(accNo, TransactionType::WITHDRAWAL, amount,
                        accounts[idx].getBalance(), "Cash withdrawal");
        fileManager.appendTransaction(txn);
        saveData();
        std::cout << "\n  [OK] Rs. " << std::fixed << std::setprecision(2) << amount
                  << " withdrawn successfully.\n";
        std::cout << "  [i] Remaining Balance: Rs. " << std::fixed << std::setprecision(2)
                  << accounts[idx].getBalance() << "\n";
    }
}

void Bank::transfer() {
    std::string fromAccNo, toAccNo, pin;
    double amount;
    std::cout << "\n  +----------------------------------------+\n";
    std::cout << "  |          FUND TRANSFER                  |\n";
    std::cout << "  +----------------------------------------+\n";
    std::cout << "  Enter Your Account Number: ";
    std::cin >> fromAccNo;
    int fromIdx = findAccountIndex(fromAccNo);
    if (fromIdx == -1) { std::cout << "\n  [!] Sender account not found.\n"; return; }
    if (!accounts[fromIdx].isActive()) { std::cout << "\n  [!] Sender account is closed.\n"; return; }
    std::cout << "  Enter PIN: ";
    std::cin >> pin;
    if (!accounts[fromIdx].verifyPin(pin)) { std::cout << "\n  [!] Incorrect PIN. Access denied.\n"; return; }

    std::cout << "  Enter Recipient Account Number: ";
    std::cin >> toAccNo;
    if (fromAccNo == toAccNo) { std::cout << "\n  [!] Cannot transfer to the same account.\n"; return; }
    int toIdx = findAccountIndex(toAccNo);
    if (toIdx == -1) { std::cout << "\n  [!] Recipient account not found.\n"; return; }
    if (!accounts[toIdx].isActive()) { std::cout << "\n  [!] Recipient account is closed.\n"; return; }

    std::cout << "  Available Balance: Rs. " << std::fixed << std::setprecision(2)
              << accounts[fromIdx].getBalance() << "\n";
    std::cout << "  Enter Transfer Amount: Rs. ";
    std::cin >> amount;
    if (std::cin.fail()) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "\n  [!] Invalid amount entered.\n";
        return;
    }

    if (accounts[fromIdx].withdraw(amount)) {
        accounts[toIdx].deposit(amount);
        Transaction txnOut(fromAccNo, TransactionType::TRANSFER_OUT, amount,
                           accounts[fromIdx].getBalance(), "Transfer to " + toAccNo);
        fileManager.appendTransaction(txnOut);
        Transaction txnIn(toAccNo, TransactionType::TRANSFER_IN, amount,
                          accounts[toIdx].getBalance(), "Transfer from " + fromAccNo);
        fileManager.appendTransaction(txnIn);
        saveData();
        std::cout << "\n  [OK] Rs. " << std::fixed << std::setprecision(2) << amount
                  << " transferred to " << toAccNo << " successfully.\n";
        std::cout << "  [i] Your Balance: Rs. " << std::fixed << std::setprecision(2)
                  << accounts[fromIdx].getBalance() << "\n";
    }
}

void Bank::checkBalance() {
    std::string accNo, pin;
    std::cout << "\n  Enter Account Number: ";
    std::cin >> accNo;
    int idx = findAccountIndex(accNo);
    if (idx == -1) { std::cout << "\n  [!] Account not found.\n"; return; }
    std::cout << "  Enter PIN: ";
    std::cin >> pin;
    if (!accounts[idx].verifyPin(pin)) { std::cout << "\n  [!] Incorrect PIN. Access denied.\n"; return; }

    std::cout << "\n  +==========================================+\n";
    std::cout << "  |            BALANCE ENQUIRY               |\n";
    std::cout << "  +==========================================+\n";
    std::cout << "  |  Account No  : " << std::left << std::setw(25) << accNo << "|\n";
    std::cout << "  |  Holder      : " << std::left << std::setw(25)
              << accounts[idx].getHolderName() << "|\n";
    std::cout << "  |  Balance     : Rs. " << std::left << std::setw(21)
              << std::fixed << std::setprecision(2) << accounts[idx].getBalance() << "|\n";
    std::cout << "  |  Status      : " << std::left << std::setw(25)
              << (accounts[idx].isActive() ? "ACTIVE" : "CLOSED") << "|\n";
    std::cout << "  +==========================================+\n";
}

// ============================================================================
// Transaction History
// ============================================================================

void Bank::viewTransactionHistory() {
    std::string accNo, pin;
    std::cout << "\n  Enter Account Number: ";
    std::cin >> accNo;
    int idx = findAccountIndex(accNo);
    if (idx == -1) { std::cout << "\n  [!] Account not found.\n"; return; }
    std::cout << "  Enter PIN: ";
    std::cin >> pin;
    if (!accounts[idx].verifyPin(pin)) { std::cout << "\n  [!] Incorrect PIN. Access denied.\n"; return; }

    std::vector<Transaction> txns = fileManager.getTransactionsForAccount(accNo);

    std::cout << "\n  +------------------------------------------------------------------------------------+\n";
    std::cout << "  |  TRANSACTION HISTORY -- " << std::left << std::setw(58) << accNo << "|\n";
    std::cout << "  +------------------------------------------------------------------------------------+\n";

    if (txns.empty()) {
        std::cout << "  |  No transactions found for this account.                                          |\n";
    } else {
        for (const auto& txn : txns) {
            std::cout << "  |" << txn.display() << "\n";
        }
    }
    std::cout << "  +------------------------------------------------------------------------------------+\n";
    std::cout << "  Total Transactions: " << txns.size() << "\n";
}

// ============================================================================
// Persistence
// ============================================================================

void Bank::saveData() { fileManager.saveAccounts(accounts); }
void Bank::loadData() { accounts = fileManager.loadAccounts(); }
