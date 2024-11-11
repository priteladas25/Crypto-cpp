#include <iostream>
#include <vector>
#include <string>
#include <iomanip> // For setting width and formatting

using namespace std;

class Account {
private:
    int ethereum;
    int bitcoin;
    int balance;
    int ethereum_value = 1647.47;
    int bitcoin_value = 27979.40;
    vector<string> transactions;

public:
    Account() : balance(50000), ethereum(0), bitcoin(0) {}

    void DisplayAccountInformation() {
        cout << "\n------------------- ACCOUNT INFORMATION -------------------\n";
        cout << "Balance: $" << balance << endl;
        cout << "Ethereum: " << ethereum << endl;
        cout << "Bitcoin: " << bitcoin << endl;
        cout << "----------------------------------------------------------\n\n";
    }

    void Deposit(int money) {
        balance += money;
        transactions.push_back("Deposited: $" + to_string(money));
        cout << "Deposit successful!\n";
    }

    void Withdraw(int money) {
        if (money <= balance) {
            balance -= money;
            transactions.push_back("Withdrew: $" + to_string(money));
            cout << "Withdrawal successful!\n";
        } else {
            cout << "Insufficient balance.\n";
        }
    }

    void BuyCrypto() {
        int option;
        cout << "\n----------- BUY CRYPTOCURRENCY -----------\n";
        cout << "1: Buy Ethereum\n";
        cout << "2: Buy Bitcoin\n";
        cout << "Enter your choice: ";
        cin >> option;

        if (option == 1 && balance >= ethereum_value) {
            ethereum++;
            balance -= ethereum_value;
            transactions.push_back("+ 1 Ethereum");
            cout << "+ 1 Ethereum purchased!\n";
        } else if (option == 2 && balance >= bitcoin_value) {
            bitcoin++;
            balance -= bitcoin_value;
            transactions.push_back("+ 1 Bitcoin");
            cout << "+ 1 Bitcoin purchased!\n";
        } else {
            cout << "Not enough balance to buy the selected cryptocurrency.\n";
        }
        cout << "------------------------------------------\n\n";
    }

    void SellCrypto() {
        int option;
        cout << "\n----------- SELL CRYPTOCURRENCY -----------\n";
        cout << "1: Sell Ethereum\n";
        cout << "2: Sell Bitcoin\n";
        cout << "Enter your choice: ";
        cin >> option;

        if (option == 1 && ethereum > 0) {
            ethereum--;
            balance += ethereum_value;
            transactions.push_back("Sold 1 Ethereum");
            cout << "Sold 1 Ethereum!\n";
        } else if (option == 2 && bitcoin > 0) {
            bitcoin--;
            balance += bitcoin_value;
            transactions.push_back("Sold 1 Bitcoin");
            cout << "Sold 1 Bitcoin!\n";
        } else {
            cout << "You don't have enough cryptocurrency to sell.\n";
        }
        cout << "-------------------------------------------\n\n";
    }

    void TransactionHistory() {
        cout << "\n----------- TRANSACTION HISTORY -----------\n";
        if (transactions.empty()) {
            cout << "No transactions yet.\n";
        } else {
            for (const string &transaction : transactions) {
                cout << transaction << endl;
            }
        }
        cout << "-------------------------------------------\n\n";
    }
};

class User {
private:
    string username;
    string password;
    Account userAccount;

public:
    User(string user, string pass) : username(user), password(pass) {}

    bool validatePassword(const string &pass) const {
        return password == pass;
    }

    Account& getAccount() {
        return userAccount;
    }

    string getUserName() const {
        return username;
    }
};

vector<User> users;

void Register() {
    string username, password;
    cout << "\n-------------- REGISTER --------------\n";
    cout << "Enter a username: ";
    cin >> username;

    for (const User &user : users) {
        if (username == user.getUserName()) {
            cout << "Username already taken. Try again.\n";
            return;
        }
    }

    cout << "Enter a password: ";
    cin >> password;

    users.emplace_back(username, password);
    cout << "Registration successful!\n";
    cout << "--------------------------------------\n\n";
}

Account* Login() {
    string username, password;
    cout << "\n-------------- LOGIN --------------\n";
    cout << "Enter username: ";
    cin >> username;
    cout << "Enter password: ";
    cin >> password;

    for (User &user : users) {
        if (username == user.getUserName() && user.validatePassword(password)) {
            cout << "Login successful!\n";
            cout << "----------------------------------\n\n";
            return &user.getAccount();
        }
    }

    cout << "Invalid username or password.\n";
    cout << "----------------------------------\n\n";
    return nullptr;
}

int main() {
    int choice;
    Account* activeAccount = nullptr;
    cout << "------------------------------------\n";
    cout << "         WELCOME TO CRYPTO APP      \n";
    cout << "------------------------------------\n\n";

    while (true) {
        cout << "\n---------- MAIN MENU ----------\n";
        cout << "  1: Register\n";
        cout << "  2: Login\n";
        cout << "  3: Exit\n";
        cout << "-------------------------------\n";
        cout << "Enter a choice: ";
        cin >> choice;

        if (choice == 1) {
            Register();
        } else if (choice == 2) {
            activeAccount = Login();
            if (activeAccount) {
                int innerChoice;
                do {
                    cout << "\n------------- ACCOUNT MENU -------------\n";
                    cout << "1: Display Account Info\n";
                    cout << "2: Deposit Money\n";
                    cout << "3: Withdraw Money\n";
                    cout << "4: Buy Cryptocurrency\n";
                    cout << "5: Sell Cryptocurrency\n";
                    cout << "6: View Transaction History\n";
                    cout << "7: Logout\n";
                    cout << "----------------------------------------\n";
                    cout << "Enter a choice: ";
                    cin >> innerChoice;

                    switch (innerChoice) {
                        case 1:
                            activeAccount->DisplayAccountInformation();
                            break;
                        case 2: {
                            cout << "Enter deposit amount: $";
                            int depositAmount;
                            cin >> depositAmount;
                            activeAccount->Deposit(depositAmount);
                            break;
                        }
                        case 3: {
                            cout << "Enter withdrawal amount: $";
                            int withdrawAmount;
                            cin >> withdrawAmount;
                            activeAccount->Withdraw(withdrawAmount);
                            break;
                        }
                        case 4:
                            activeAccount->BuyCrypto();
                            break;
                        case 5:
                            activeAccount->SellCrypto();
                            break;
                        case 6:
                            activeAccount->TransactionHistory();
                            break;
                        case 7:
                            cout << "Logged out successfully!\n";
                            break;
                        default:
                            cout << "Invalid choice, try again.\n";
                    }
                } while (innerChoice != 7);
            }
        } else if (choice == 3) {
            cout << "Goodbye!\n";
            break;
        } else {
            cout << "Invalid choice, try again.\n";
        }
    }
    return 0;
}
