// ============================================================================
//  main.cpp — Entry Point & Menu System
//  Banking System | Pinnacle Labs Internship
//  Author: Priyam Prakash
// ============================================================================

#include <iostream>
#include <limits>
#include "Bank.h"

// Clear the console screen (cross-platform)
void clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

// Display the main banner
void displayBanner() {
    std::cout << "\n";
    std::cout << "  +============================================================+\n";
    std::cout << "  |                                                            |\n";
    std::cout << "  |          PINNACLE NATIONAL BANK                            |\n";
    std::cout << "  |          Banking Management System v1.0                    |\n";
    std::cout << "  |                                                            |\n";
    std::cout << "  |          Developed by: Priyam Prakash                      |\n";
    std::cout << "  |          Pinnacle Labs Internship                          |\n";
    std::cout << "  |                                                            |\n";
    std::cout << "  +============================================================+\n";
}

// Display the main menu
void displayMenu() {
    std::cout << "\n";
    std::cout << "  +----------------------------------------+\n";
    std::cout << "  |            MAIN MENU                   |\n";
    std::cout << "  +----------------------------------------+\n";
    std::cout << "  |                                        |\n";
    std::cout << "  |   [1]  Create New Account              |\n";
    std::cout << "  |   [2]  View Account Details            |\n";
    std::cout << "  |   [3]  Deposit Funds                   |\n";
    std::cout << "  |   [4]  Withdraw Funds                  |\n";
    std::cout << "  |   [5]  Transfer Funds                  |\n";
    std::cout << "  |   [6]  Check Balance                   |\n";
    std::cout << "  |   [7]  Transaction History             |\n";
    std::cout << "  |   [8]  List All Accounts               |\n";
    std::cout << "  |   [9]  Close Account                   |\n";
    std::cout << "  |   [0]  Exit                            |\n";
    std::cout << "  |                                        |\n";
    std::cout << "  +----------------------------------------+\n";
    std::cout << "\n  Enter your choice: ";
}

int main() {
    Bank bank("Pinnacle National Bank");
    int choice;

    clearScreen();
    displayBanner();

    do {
        displayMenu();
        std::cin >> choice;

        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "\n  [!] Invalid input. Please enter a number (0-9).\n";
            continue;
        }

        switch (choice) {
            case 1:
                bank.createAccount();
                break;
            case 2:
                bank.viewAccountDetails();
                break;
            case 3:
                bank.deposit();
                break;
            case 4:
                bank.withdraw();
                break;
            case 5:
                bank.transfer();
                break;
            case 6:
                bank.checkBalance();
                break;
            case 7:
                bank.viewTransactionHistory();
                break;
            case 8:
                bank.listAllAccounts();
                break;
            case 9:
                bank.closeAccount();
                break;
            case 0:
                std::cout << "\n  +==========================================+\n";
                std::cout << "  |  Thank you for using Pinnacle National   |\n";
                std::cout << "  |  Bank. Have a great day!                 |\n";
                std::cout << "  +==========================================+\n\n";
                break;
            default:
                std::cout << "\n  [!] Invalid choice. Please select 0-9.\n";
        }

    } while (choice != 0);

    return 0;
}
