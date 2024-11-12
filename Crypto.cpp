#include <iostream>
#include <vector>
#include <string>
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
    Account() {
        balance = 50000;
        ethereum = 0;
        bitcoin = 0;
    }

    void DisplayAccountInformation() {
        cout << "\033[36m\n=================== ACCOUNT INFORMATION ===================\033[0m\n";
        cout << "Balance: $" << balance << endl;
        cout << "Ethereum: " << ethereum << endl;
        cout << "Bitcoin: " << bitcoin << endl;
        cout << "\033[36m==========================================================\033[0m\n\n";
    }

    void Deposit(int money) {
        balance += money;
        transactions.push_back("Deposited: $" + to_string(money));
        cout << "\033[32mDeposit successful!\033[0m\n";
    }

    void Withdraw(int money) {
        if (money <= balance) {
            balance -= money;
            transactions.push_back("Withdrew: $" + to_string(money));
            cout << "\033[32mWithdrawal successful!\033[0m\n";
        } else {
            cout << "\033[31mInsufficient balance.\033[0m\n";
        }
    }

    void BuyCrypto() {
        int option;
        cout << "\033[36m\n=========== BUY CRYPTOCURRENCY ===========\033[0m\n";
        cout << "1: Buy Ethereum\n";
        cout << "2: Buy Bitcoin\n";
        cout << "Enter your choice: ";
        cin >> option;

        if (option == 1 && balance >= ethereum_value) {
            ethereum++;
            balance -= ethereum_value;
            transactions.push_back("+ 1 Ethereum");
            cout << "\033[32m+ 1 Ethereum purchased!\033[0m\n";
        } else if (option == 2 && balance >= bitcoin_value) {
            bitcoin++;
            balance -= bitcoin_value;
            transactions.push_back("+ 1 Bitcoin");
            cout << "\033[32m+ 1 Bitcoin purchased!\033[0m\n";
        } else {
            cout << "\033[31mNot enough balance to buy the selected cryptocurrency.\033[0m\n";
        }
        cout << "\033[36m==========================================\033[0m\n\n";
    }

    void SellCrypto() {
        int option;
        cout << "\033[36m\n=========== SELL CRYPTOCURRENCY ===========\033[0m\n";
        cout << "1: Sell Ethereum\n";
        cout << "2: Sell Bitcoin\n";
        cout << "Enter your choice: ";
        cin >> option;

        if (option == 1 && ethereum > 0) {
            ethereum--;
            balance += ethereum_value;
            transactions.push_back("Sold 1 Ethereum");
            cout << "\033[32mSold 1 Ethereum!\033[0m\n";
        } else if (option == 2 && bitcoin > 0) {
            bitcoin--;
            balance += bitcoin_value;
            transactions.push_back("Sold 1 Bitcoin");
            cout << "\033[32mSold 1 Bitcoin!\033[0m\n";
        } else {
            cout << "\033[31mYou don't have enough cryptocurrency to sell.\033[0m\n";
        }
        cout << "\033[36m===========================================\033[0m\n\n";
    }

    void TransactionHistory() {
        cout << "\033[36m\n=========== TRANSACTION HISTORY ===========\033[0m\n";
        for (const string& transaction : transactions) {
            cout << transaction << endl;
        }
        cout << "\033[36m===========================================\033[0m\n\n";
    }
};

class User {
private:
    string username;
    string password;
    Account userAccount;

public:
    User(string user, string pass) : username(user), password(pass) {}

    bool validatePassword(string pass) {
        return password == pass;
    }

    Account& getAccount() {
        return userAccount;
    }

    string getUserName() const { // Add 'const' here
        return username;
    }
};

vector<User> users;

void Register() {
    string username, password;
    cout << "\033[36m\n============== REGISTER ==============\033[0m\n";
    cout << "Enter a username: ";
    cin >> username;

    for (const User &user : users) {
        if (username == user.getUserName()) {
            cout << "\033[31mUsername already taken. Try again.\033[0m" << endl;
            return;
        }
    }

    cout << "Enter a password: ";
    cin >> password;

    users.push_back(User(username, password));
    cout << "\033[32mRegistration successful!\033[0m" << endl;
    cout << "\033[36m======================================\033[0m\n\n";
}

Account* Login() {
    string username, password;
    cout << "\033[36m\n============== LOGIN ==============\033[0m\n";
    cout << "Enter username: ";
    cin >> username;
    cout << "Enter password: ";
    cin >> password;

    for (User &user : users) {
        if (username == user.getUserName() && user.validatePassword(password)) {
            cout << "\033[32mLogin successful!\033[0m\n";
            cout << "\033[36m===================================\033[0m\n\n";
            return &user.getAccount();
        }
    }

    cout << "\033[31mInvalid username or password.\033[0m\n";
    cout << "\033[36m===================================\033[0m\n\n";
    return nullptr;
}

void displayWelcomeMessage() {
    cout << "\033[34m====================================\033[0m\n";  // Blue
    cout << "\033[33m         WELCOME TO CRYPTO APP      \033[0m\n";  // Yellow
    cout << "\033[34m====================================\033[0m\n\n"; // Blue
}

void displayMainMenu() {
    cout << "\033[36m========== MAIN MENU ==========\033[0m\n";  // Cyan
    cout << "\033[32m  1: Register\033[0m\n";                   // Green
    cout << "\033[32m  2: Login\033[0m\n";                      // Green
    cout << "\033[32m  3: Exit\033[0m\n";                       // Green
    cout << "\033[36m===============================\033[0m\n"; // Cyan
    cout << "Enter a choice: ";
}

int main() {
    int choice;
    Account* activeAccount = nullptr;
    displayWelcomeMessage();

    while (true) {
        displayMainMenu();
        cin >> choice;

        if (choice == 1) {
            Register();
        } else if (choice == 2) {
            activeAccount = Login();
            if (activeAccount) {
                int innerChoice;
                do {
                    cout << "\033[36m\n============= ACCOUNT MENU =============\033[0m\n";
                    cout << "1: Display Account Info\n";
                    cout << "2: Deposit Money\n";
                    cout << "3: Withdraw Money\n";
                    cout << "4: Buy Cryptocurrency\n";
                    cout << "5: Sell Cryptocurrency\n";
                    cout << "6: View Transaction History\n";
                    cout << "7: Logout\n";
                    cout << "\033[36m========================================\033[0m\n";
                    cout << "Enter a choice: ";
                    cin >> innerChoice;

                    switch (innerChoice) {
                        case 1:
                            activeAccount->DisplayAccountInformation();
                            break;
                        case 2:
                            cout << "Enter deposit amount: $";
                            int depositAmount;
                            cin >> depositAmount;
                            activeAccount->Deposit(depositAmount);
                            break;
                        case 3:
                            cout << "Enter withdrawal amount: $";
                            int withdrawAmount;
                            cin >> withdrawAmount;
                            activeAccount->Withdraw(withdrawAmount);
                            break;
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
                            cout << "\033[32mLogged out successfully!\033[0m\n";
                            break;
                        default:
                            cout << "\033[31mInvalid choice, try again.\033[0m\n";
                    }
                } while (innerChoice != 7);
            }
        } else if (choice == 3) {
            cout << "\033[31mGoodbye!\033[0m\n";
            return 0;
        } else {
            cout << "\033[31mInvalid choice, try again.\033[0m\n";
        }
    }
    return 0;
}
