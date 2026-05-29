# Banking System — C++ Console Application

![Visitor Count](https://komarev.com/ghpvc/?username=Infinite-L00pBaCk&repo=Banking-System&label=Visitors&color=0e75b6&style=flat)

## Overview
A fully-featured **C++-based Banking System** developed as an internship task for **Pinnacle Labs**.  
This console application simulates core banking operations with persistent file-based storage.

## Features
- **User Account Management** — Create, view, and close accounts
- **Balance Management** — Check balances in real-time
- **Deposits** — Add funds to any account
- **Withdrawals** — Withdraw funds with insufficient balance protection
- **Fund Transfers** — Transfer money between accounts
- **Transaction History** — Full audit trail for every account
- **File Persistence** — Account data and transactions are saved to files
- **PIN Security** — 4-digit PIN authentication for account access

## File Structure
```
banking System/
├── main.cpp              # Entry point & menu system
├── BankAccount.h         # BankAccount class declaration
├── BankAccount.cpp       # BankAccount class implementation
├── Bank.h                # Bank (manager) class declaration
├── Bank.cpp              # Bank (manager) class implementation
├── Transaction.h         # Transaction struct declaration
├── Transaction.cpp       # Transaction implementation
├── FileManager.h         # File I/O handler declaration
├── FileManager.cpp       # File I/O handler implementation
├── accounts.dat          # (auto-generated) Account data store
├── transactions.dat      # (auto-generated) Transaction log
└── README.md             # This file
```

## How to Compile & Run

### Using g++ (MinGW / GCC)
```bash
g++ -std=c++17 -o banking_system main.cpp BankAccount.cpp Bank.cpp Transaction.cpp FileManager.cpp
./banking_system
```

### Using Visual Studio Developer Command Prompt
```bash
cl /EHsc /std:c++17 main.cpp BankAccount.cpp Bank.cpp Transaction.cpp FileManager.cpp /Fe:banking_system.exe
banking_system.exe
```

## Author
Priyam Prakash — Pinnacle Labs Internship Task
