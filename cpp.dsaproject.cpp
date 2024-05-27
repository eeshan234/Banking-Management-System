#include <iostream>
#include <string>
using namespace std;
struct Account {
    string username;
    string password;
    double balance;
};

struct Transaction {
    string type; 
    double amount;
    string date;
    Transaction* next; 
};
void login(Account* accounts, int numAccounts, Transaction*& history);
void deposit(Account* account, Transaction*& history);
void withdraw(Account* account, Transaction*& history);
void checkBalance(Account* account);
void displayHistory(Transaction* history);
void exitProgram();

int main() {
    const int MAX_ACC = 10;
    Account accounts[MAX_ACC] = {{"zee", "2133", 1000.0}, {"ali", "2132", 500.0}};
    Transaction* history = nullptr;

    int choice;
    do {
        cout << "1. Login\n2. Exit\nEnter your choice: ";
        cin >> choice;
        switch (choice) {
            case 1:
                login(accounts, MAX_ACC, history);
                break;
            case 2:
                exitProgram();
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
                break;
        }
    } while (choice != 2);

    return 0;
}

void login(Account* accounts, int numAccounts, Transaction*& history) {
    string username, password;
    cout << "Enter username: ";
    cin >> username;
    cout << "Enter password: ";
    cin >> password;
    bool loggedIn = false;
    Account* loggedInAccount = nullptr;
    for (int i = 0; i < numAccounts; ++i) {
        if (username == accounts[i].username && password == accounts[i].password) {
            loggedIn = true;
            loggedInAccount = &accounts[i];
            break;
        }
    }

    if (loggedIn) {
        cout << "Login successful!\n";
        int choice;
        do {
            cout << "1. Deposit\n2. Withdraw\n3. Check Balance\n4. Transaction History\n5. Logout\nEnter your choice: ";
            cin >> choice;
            switch (choice) {
                case 1:
                    deposit(loggedInAccount, history);
                    break;
                case 2:
                    withdraw(loggedInAccount, history);
                    break;
                case 3:
                    checkBalance(loggedInAccount);
                    break;
                case 4:
                    displayHistory(history);
                    break;
                case 5:
                    cout << "Logging out...\n";
                    break;
                default:
                    cout << "Invalid choice. Please try again.\n";
                    break;
            }
        } while (choice != 5);
    } else {
        cout << "Login failed. Incorrect username or password.\n";
    }
}

void deposit(Account* account, Transaction*& history) {
    double amount;
    cout << "Enter deposit amount: ";
    cin >> amount;
    if (amount > 0) {
        account->balance += amount;
        Transaction* depositTransaction = new Transaction{"Deposit", amount, "2024-05-27", history};
        history = depositTransaction;
        cout << "Deposit successful.\n";
    } else {
        cout << "Invalid amount. Deposit failed.\n";
    }
}

void withdraw(Account* account, Transaction*& history) {
    double amount;
    cout << "Enter withdrawal amount: ";
    cin >> amount;
    if (amount > 0 && amount <= account->balance) {
        account->balance -= amount;
        Transaction* withdrawalTransaction = new Transaction{"Withdrawal", amount, "2024-05-27", history};
        history = withdrawalTransaction;
        cout << "Withdrawal successful.\n";
    } else {
        cout << "Invalid amount or insufficient balance. Withdrawal failed.\n";
    }
}

void checkBalance(Account* account) {
    cout << "Your current balance is: $" << account->balance << endl;
}

void displayHistory(Transaction* history) {
    cout << "Transaction History:\n";
    while (history != nullptr) {
        cout << "Type: " << history->type << ", Amount: $" << history->amount << ", Date: " << history->date << endl;
        history = history->next;
    }
}

void exitProgram() {
    cout << "Exiting program...\n";
    exit(0);
}