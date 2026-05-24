# 🏦 Banking Management System

<div align="center">

![C++](https://img.shields.io/badge/Language-C%2B%2B11-blue?style=for-the-badge&logo=c%2B%2B)
![Platform](https://img.shields.io/badge/Platform-Windows%20%7C%20Linux-lightgrey?style=for-the-badge)
![Status](https://img.shields.io/badge/Status-Complete-success?style=for-the-badge)
![License](https://img.shields.io/badge/License-MIT-yellow?style=for-the-badge)

**A fully-featured C++ console-based Banking System with persistent file storage, PIN authentication, and complete transaction history.**

*Developed as an internship task for Pinnacle Labs — May 2026*

</div>

------------

## 📋 Table of Contents

- [Overview](#-overview)
- [Features](#-features)
- [Architecture](#-architecture)
- [File Structure](#-file-structure)
- [OOP Concepts Used](#-oop-concepts-used)
- [How to Compile & Run](#-how-to-compile--run)
- [Usage Guide](#-usage-guide)
- [Data Storage Format](#-data-storage-format)
- [Future Enhancements](#-future-enhancements)
- [Author](#-author)

---

## 🌟 Overview

This project simulates core real-world banking operations through an interactive console interface. It allows users to **create accounts**, **manage balances**, **perform deposits/withdrawals/transfers**, and **view complete transaction history** — all with data persisted between sessions using flat file storage.

---

## ✅ Features

| # | Feature | Description |
|---|---------|-------------|
| 1 | **Create Account** | Register with full name, 4-digit PIN (with confirmation), minimum Rs. 500 initial deposit |
| 2 | **View Account Details** | PIN-authenticated display of account information |
| 3 | **Deposit Funds** | Add money to any active account with validation |
| 4 | **Withdraw Funds** | PIN-authenticated withdrawal with insufficient balance protection |
| 5 | **Fund Transfer** | Transfer money between two accounts with dual transaction logging |
| 6 | **Check Balance** | Quick PIN-secured balance enquiry |
| 7 | **Transaction History** | Full timestamped audit trail per account |
| 8 | **List All Accounts** | Tabular overview of all registered accounts |
| 9 | **Close Account** | Deactivate account with confirmation prompt |
| 10 | **File Persistence** | Data survives program restarts via `.dat` file storage |

---

## 🏗️ Architecture

```
main.cpp  ──────────────────►  Bank (Orchestrator)
                                    │
                    ┌───────────────┼───────────────┐
                    │               │               │
             BankAccount      Transaction       FileManager
             (.h / .cpp)      (.h / .cpp)       (.h / .cpp)
             Account data     Txn records       File I/O
                                                    │
                                         ┌──────────┴──────────┐
                                    accounts.dat        transactions.dat
```

---

## 📁 File Structure

```
banking-system/
├── main.cpp              # Entry point, ASCII banner & interactive menu
├── Bank.h                # Bank manager class declaration
├── Bank.cpp              # Bank manager class implementation (~370 lines)
├── BankAccount.h         # BankAccount class declaration
├── BankAccount.cpp       # BankAccount class implementation
├── Transaction.h         # Transaction struct declaration
├── Transaction.cpp       # Transaction struct implementation
├── FileManager.h         # File I/O handler declaration
├── FileManager.cpp       # File I/O handler implementation
├── accounts.dat          # (auto-generated) Persistent account data store
├── transactions.dat      # (auto-generated) Persistent transaction log
└── README.md             # This file
```

---

## 🧠 OOP Concepts Used

### Encapsulation
All class data members are `private`. Access is strictly controlled through `public` getter methods and validated operations — external code can never directly modify a balance or bypass PIN checks.

### Abstraction
The `Bank` class hides all complexity (file I/O, account lookup, transaction logging). The `main.cpp` simply calls `bank.deposit()` without needing to know any internal details.

### Separation of Concerns
| Class | Responsibility |
|-------|---------------|
| `BankAccount` | Manages one account's data and operations |
| `Transaction` | Represents and formats a single transaction record |
| `FileManager` | Handles all file reads and writes (persistence layer) |
| `Bank` | Orchestrates all operations (business logic layer) |
| `main.cpp` | User interface layer — menu display and input handling |

### Enum Class (Type Safety)
```cpp
enum class TransactionType {
    DEPOSIT, WITHDRAWAL, TRANSFER_IN, TRANSFER_OUT, ACCOUNT_CREATION
};
```
Scoped `enum class` is used instead of plain `enum` to prevent accidental integer comparisons.

---

## 🚀 How to Compile & Run

### Prerequisites
- GCC / MinGW with C++11 support (or Visual Studio)

### Using g++ (Linux / MinGW on Windows)
```bash
g++ -std=c++11 -o banking_system main.cpp BankAccount.cpp Bank.cpp Transaction.cpp FileManager.cpp
./banking_system        # Linux/Mac
banking_system.exe      # Windows
```

### Using Visual Studio Developer Command Prompt
```bash
cl /EHsc /std:c++17 main.cpp BankAccount.cpp Bank.cpp Transaction.cpp FileManager.cpp /Fe:banking_system.exe
banking_system.exe
```

---

## 🖥️ Usage Guide

When you launch the program, you'll see an interactive menu:

```
  +----------------------------------------+
  |            MAIN MENU                   |
  +----------------------------------------+
  |   [1]  Create New Account              |
  |   [2]  View Account Details            |
  |   [3]  Deposit Funds                   |
  |   [4]  Withdraw Funds                  |
  |   [5]  Transfer Funds                  |
  |   [6]  Check Balance                   |
  |   [7]  Transaction History             |
  |   [8]  List All Accounts               |
  |   [9]  Close Account                   |
  |   [0]  Exit                            |
  +----------------------------------------+
```

**Creating your first account:**
1. Select option `[1]`
2. Enter your full name
3. Set a 4-digit PIN and confirm it
4. Make an initial deposit of at least Rs. 500
5. Your account number (e.g., `PNB-1001`) is generated automatically

---

## 💾 Data Storage Format

Data is stored as pipe-delimited (`|`) text in `.dat` files — human-readable and parseable without any external libraries.

**accounts.dat**
```
PNB-1001|Priyam Prakash|1234|5000.00|1|2026-05-07 19:08:00
```
`AccountNo | Name | PIN | Balance | Active(1/0) | CreationDate`

**transactions.dat**
```
PNB-1001|DEPOSIT|2000.00|7000.00|2026-05-07 19:10:00|Cash deposit
```
`AccountNo | Type | Amount | BalanceAfter | Timestamp | Description`

---

## 🔮 Future Enhancements

- [ ] Password hashing instead of storing plain PINs
- [ ] SQLite database integration instead of flat files
- [ ] Interest calculation on savings accounts
- [ ] Multiple account types (Savings, Current, Fixed Deposit)
- [ ] Admin login with elevated privileges
- [ ] Loan management module
- [ ] GUI interface using Qt or SFML

---

## 👨‍💻 Author

**Priyam Prakash**
Pinnacle Labs Internship Task — May 2026

---

<div align="center">
<i>Banking System v1.0 — Built with C++11</i>
</div>
