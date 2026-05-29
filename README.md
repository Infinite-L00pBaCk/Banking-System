<div align="center">

<!-- Visitor Counter -->
![Visitor Count](https://profile-counter.glitch.me/Infinite-L00pBaCk-Banking-System/count.svg)

<br/>

```
██████╗  █████╗ ███╗   ██╗██╗  ██╗    ██████╗ ██████╗  ██████╗
██╔══██╗██╔══██╗████╗  ██║██║ ██╔╝    ██╔══██╗██╔══██╗██╔═══██╗
██████╔╝███████║██╔██╗ ██║█████╔╝     ██████╔╝██████╔╝██║   ██║
██╔══██╗██╔══██║██║╚██╗██║██╔═██╗     ██╔═══╝ ██╔══██╗██║   ██║
██████╔╝██║  ██║██║ ╚████║██║  ██╗    ██║     ██║  ██║╚██████╔╝
╚═════╝ ╚═╝  ╚═╝╚═╝  ╚═══╝╚═╝  ╚═╝   ╚═╝     ╚═╝  ╚═╝ ╚═════╝
```

# 🏦 Banking Management System

**A fully-featured C++ console banking application with persistent storage, PIN authentication & complete transaction history.**

<br/>

[![C++](https://img.shields.io/badge/Language-C%2B%2B11-00599C?style=for-the-badge&logo=c%2B%2B&logoColor=white)](https://isocpp.org/)
[![Platform](https://img.shields.io/badge/Platform-Windows%20%7C%20Linux%20%7C%20macOS-lightgrey?style=for-the-badge&logo=windows&logoColor=white)](https://github.com/Infinite-L00pBaCk/Banking-System)
[![Status](https://img.shields.io/badge/Status-Complete-brightgreen?style=for-the-badge&logo=checkmarx&logoColor=white)](https://github.com/Infinite-L00pBaCk/Banking-System)
[![License](https://img.shields.io/badge/License-MIT-yellow?style=for-the-badge&logo=open-source-initiative&logoColor=white)](./LICENSE)
[![Internship](https://img.shields.io/badge/Pinnacle%20Labs-Internship%20Task-blueviolet?style=for-the-badge&logo=briefcase&logoColor=white)](https://github.com/Infinite-L00pBaCk/Banking-System)

</div>

---

## 📌 Table of Contents

- [✨ Overview](#-overview)
- [🚀 Features](#-features)
- [🏗️ Architecture](#️-architecture)
- [🧠 OOP Concepts](#-oop-concepts)
- [📁 File Structure](#-file-structure)
- [💾 Data Storage](#-data-storage)
- [⚙️ Build & Run](#️-build--run)
- [🖥️ Usage Guide](#️-usage-guide)
- [🔮 Future Enhancements](#-future-enhancements)
- [👨‍💻 Author](#-author)

---

## ✨ Overview

> *"Not just a project — a fully working bank in your terminal."*

The **Banking Management System** simulates real-world banking operations through an interactive console interface. Every feature you'd expect from a bank — account creation, deposits, withdrawals, fund transfers, and full transaction history — all backed by **persistent file storage** that survives program restarts.

Built with pure **C++11**, zero external dependencies, and clean object-oriented architecture. Developed as an internship task for **Pinnacle Labs — May 2026**.

---

## 🚀 Features

| # | Feature | Description |
|---|---------|-------------|
| 1 | 🆕 **Create Account** | Register with full name, 4-digit PIN (with confirmation), minimum ₹500 initial deposit. Auto-generates `PNB-XXXX` account numbers. |
| 2 | 👤 **View Account Details** | PIN-authenticated display of complete account info. |
| 3 | 💰 **Deposit Funds** | Add money to any active account with full input validation. |
| 4 | 💸 **Withdraw Funds** | PIN-authenticated withdrawal with insufficient balance protection. |
| 5 | 🔄 **Fund Transfer** | Transfer between two accounts with **dual transaction logging** for both parties. |
| 6 | 📊 **Check Balance** | Instant PIN-secured balance enquiry. |
| 7 | 🧾 **Transaction History** | Full timestamped audit trail — deposits, withdrawals, transfers. |
| 8 | 📋 **List All Accounts** | Tabular overview of every registered account. |
| 9 | ❌ **Close Account** | Deactivate with PIN confirmation; remaining balance is returned. |
| 10 | 💾 **File Persistence** | Data survives restarts via `.dat` flat-file storage — no database needed. |

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

### Layer Breakdown

```
┌─────────────────────────────────────────────────────┐
│                  UI Layer (main.cpp)                 │  ← Menu, input, display
├─────────────────────────────────────────────────────┤
│             Business Logic Layer (Bank)              │  ← Validation, coordination
├──────────────┬──────────────────┬───────────────────┤
│ BankAccount  │   Transaction    │   FileManager      │  ← Domain objects + I/O
├──────────────┴──────────────────┴───────────────────┤
│          Persistence Layer (accounts.dat /.dat)      │  ← Flat-file storage
└─────────────────────────────────────────────────────┘
```

---

## 🧠 OOP Concepts

<details>
<summary><b>🔒 Encapsulation</b></summary>

All data members are `private`. Balance, PIN, and active status are only accessible through validated public methods — you can never set a negative balance or bypass PIN checks from outside the class.

</details>

<details>
<summary><b>🎭 Abstraction</b></summary>

`main.cpp` calls `bank.deposit()` — it has no idea about file I/O, account lookup, or transaction logging. The entire persistence layer is invisible to the UI.

</details>

<details>
<summary><b>🧩 Separation of Concerns</b></summary>

| Class | Knows about |
|-------|-------------|
| `BankAccount` | One account's data and operations |
| `Transaction` | One transaction record |
| `FileManager` | All file reads and writes |
| `Bank` | Coordination and business rules |
| `main.cpp` | User interface only |

</details>

<details>
<summary><b>🏷️ Type-Safe Enumerations</b></summary>

```cpp
enum class TransactionType {
    DEPOSIT, WITHDRAWAL, TRANSFER_IN, TRANSFER_OUT, ACCOUNT_CREATION
};
```

Scoped `enum class` prevents accidental integer comparisons and implicit conversions.

</details>

---

## 📁 File Structure

```
banking-system/
│
├── 📄 main.cpp               # Entry point — ASCII banner & interactive menu
├── 📄 Bank.h / Bank.cpp      # Bank manager class (~370 lines of business logic)
├── 📄 BankAccount.h / .cpp   # Account data model + validated operations
├── 📄 Transaction.h / .cpp   # Transaction record representation
├── 📄 FileManager.h / .cpp   # Flat-file persistence layer
│
├── 💾 accounts.dat           # (auto-generated) Account data store
├── 💾 transactions.dat       # (auto-generated) Transaction log
│
├── 📦 banking_system.exe     # Pre-compiled Windows executable
├── 📖 walkthrough.md         # Step-by-step usage guide
└── 📝 README.md              # This file
```

> **Language breakdown:** C++ `68.2%` · HTML `31.8%`

---

## 💾 Data Storage

No SQL, no external libraries — just human-readable pipe-delimited `.dat` files.

**`accounts.dat`**
```
AccountNo | Name | PIN | Balance | Active(1/0) | CreationDate
PNB-1001|Priyam Prakash|1234|5000.00|1|2026-05-07 19:08:00
```

**`transactions.dat`**
```
AccountNo | Type | Amount | BalanceAfter | Timestamp | Description
PNB-1001|DEPOSIT|2000.00|7000.00|2026-05-07 19:10:00|Cash deposit
PNB-1001|TRANSFER_OUT|500.00|6500.00|2026-05-07 19:15:00|Transfer to PNB-1002
PNB-1002|TRANSFER_IN|500.00|1000.00|2026-05-07 19:15:00|Transfer from PNB-1001
```

> Fund transfers write **two records** — one `TRANSFER_OUT` for sender, one `TRANSFER_IN` for recipient. Complete audit trail for both accounts.

---

## ⚙️ Build & Run

### Prerequisites
- GCC / MinGW with C++11 support **or** Visual Studio 2019+

### 🐧 Linux / macOS / MinGW
```bash
g++ -std=c++11 -o banking_system \
    main.cpp BankAccount.cpp Bank.cpp Transaction.cpp FileManager.cpp

./banking_system          # Linux / macOS
banking_system.exe        # Windows
```

### 🖥️ Visual Studio Developer Command Prompt
```bash
cl /EHsc /std:c++17 main.cpp BankAccount.cpp Bank.cpp ^
   Transaction.cpp FileManager.cpp /Fe:banking_system.exe

banking_system.exe
```

### ⚡ Quick Run (Windows)
A pre-compiled `banking_system.exe` is included — just double-click or run it from the terminal. No compilation needed.

---

## 🖥️ Usage Guide

```
╔══════════════════════════════════════════╗
║              MAIN MENU                   ║
╠══════════════════════════════════════════╣
║   [1]  Create New Account                ║
║   [2]  View Account Details              ║
║   [3]  Deposit Funds                     ║
║   [4]  Withdraw Funds                    ║
║   [5]  Transfer Funds                    ║
║   [6]  Check Balance                     ║
║   [7]  Transaction History               ║
║   [8]  List All Accounts                 ║
║   [9]  Close Account                     ║
║   [0]  Exit                              ║
╚══════════════════════════════════════════╝
```

**Creating your first account:**
1. Select `[1]` → Enter your full name
2. Set a 4-digit PIN → Confirm it (re-prompts on mismatch)
3. Make an initial deposit of at least **₹500**
4. Receive your auto-generated account number — e.g. `PNB-1001`
5. Done! Your data is instantly saved to `accounts.dat` 🎉

---

## 🔮 Future Enhancements

- [ ] 🔐 PIN hashing (bcrypt / SHA-256) — no plain-text storage
- [ ] 🗄️ SQLite database integration — scalable & ACID-compliant
- [ ] 💹 Interest calculation on savings accounts
- [ ] 🏦 Multiple account types — Savings, Current, Fixed Deposit
- [ ] 👑 Admin module with elevated access
- [ ] 💳 Loan management & EMI tracking
- [ ] 🎨 GUI interface — Qt or SFML frontend

---

## 👨‍💻 Author

<div align="center">

<img src="https://avatars.githubusercontent.com/Infinite-L00pBaCk" width="100" style="border-radius:50%" alt="Priyam Prakash"/>

### Priyam Prakash

[![GitHub](https://img.shields.io/badge/GitHub-Infinite--L00pBaCk-181717?style=for-the-badge&logo=github&logoColor=white)](https://github.com/Infinite-L00pBaCk)

*Pinnacle Labs Internship Task — May 2026*

</div>

---

<div align="center">

**⭐ If you found this useful, drop a star — it means a lot!**

*Banking System v1.0 · Built with ❤️ and C++11*

</div>
