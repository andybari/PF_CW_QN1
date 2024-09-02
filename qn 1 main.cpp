#include <iostream>
#include <unordered_map>
#include <string>

using namespace std;

// Global variables to store user data
unordered_map<string, string> userAccounts; // userID -> password
unordered_map<string, double> userBalances; // userID -> balance
string currentUser; // To keep track of the logged-in user

// Function prototypes
void displayIntroMenu();
void displayMainMenu();
void createAccount();
bool login();
void depositMoney();
void withdrawMoney();
void requestBalance();

int main() {
    char choice;

    // Introduction Menu
    do {
        displayIntroMenu();
        cin >> choice;
        cin.ignore(); // To ignore the newline character left in the input buffer

        switch (choice) {
            case 'c':
                createAccount();
                break;
            case 'l':
                if (login()) {
                    // Main Menu
                    char mainChoice;
                    do {
                        displayMainMenu();
                        cin >> mainChoice;
                        cin.ignore(); // To ignore the newline character left in the input buffer

                        switch (mainChoice) {
                            case 'd':
                                depositMoney();
                                break;
                            case 'w':
                                withdrawMoney();
                                break;
                            case 'r':
                                requestBalance();
                                break;
                            case 'q':
                                cout << "Thank you for using the ATM. Goodbye!" << endl;
                                break;
                            default:
                                cout << "Invalid choice, please try again." << endl;
                        }
                    } while (mainChoice != 'q');
                }
                break;
            case 'q':
                cout << "Thank you for using the ATM. Goodbye!" << endl;
                break;
            default:
                cout << "Invalid choice, please try again." << endl;
        }
    } while (choice != 'q');

    return 0;
}

// Function to display the introduction menu
void displayIntroMenu() {
    cout << "Hi! Welcome to the ATM Machine!" << endl;
    cout << "Please select an option from the menu below:" << endl;
    cout << "l -> Login" << endl;
    cout << "c -> Create New Account" << endl;
    cout << "q -> Quit" << endl;
}

// Function to display the main menu
void displayMainMenu() {
    cout << "Access Granted!" << endl;
    cout << "d -> Deposit Money" << endl;
    cout << "w -> Withdraw Money" << endl;
    cout << "r -> Request Balance" << endl;
    cout << "q -> Quit" << endl;
}

// Function to create a new account
void createAccount() {
    string userId, password;
    cout << "Please enter your user ID: ";
    getline(cin, userId);
    cout << "Please enter your password: ";
    getline(cin, password);

    // Check if the user ID already exists
    if (userAccounts.find(userId) != userAccounts.end()) {
        cout << "Account with this user ID already exists!" << endl;
    } else {
        userAccounts[userId] = password;
        userBalances[userId] = 20.0; // Initialize balance to 0
        cout << "Thank You! Your account has been created!" << endl;
    }
}

// Function to log in
bool login() {
    string userId, password;
    cout << "Please enter your user ID: ";
    getline(cin, userId);
    cout << "Please enter your password: ";
    getline(cin, password);

    // Check if the user ID and password match
    auto it = userAccounts.find(userId);
    if (it != userAccounts.end() && it->second == password) {
        currentUser = userId;
        return true;
    } else {
        cout << "*** LOGIN FAILED! ***" << endl;
        return false;
    }
}

// Function to deposit money
void depositMoney() {
    double amount;
    cout << "Amount of deposit: $";
    cin >> amount;
    cin.ignore(); // Ignore the newline character

    if (amount > 0) {
        userBalances[currentUser] += amount;
        cout << "Deposit successful. Your new balance is: $" << userBalances[currentUser] << endl;
    } else {
        cout << "Invalid amount. Please enter a positive number." << endl;
    }
}

// Function to withdraw money
void withdrawMoney() {
    double amount;
    cout << "Amount of withdrawal: $";
    cin >> amount;
    cin.ignore(); // Ignore the newline character

    if (amount > 0 && amount <= userBalances[currentUser]) {
        userBalances[currentUser] -= amount;
        cout << "Withdrawal successful. Your new balance is: $" << userBalances[currentUser] << endl;
    } else if (amount > userBalances[currentUser]) {
        cout << "Insufficient funds." << endl;
    } else {
        cout << "Invalid amount. Please enter a positive number." << endl;
    }
}

// Function to request balance
void requestBalance() {
    cout << "Your balance is: $" << userBalances[currentUser] << endl;
}
