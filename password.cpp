#include <iostream>
#include <unordered_map>
#include <string>
#include <cstdlib>
#include <ctime>
#include <regex>
#include <iomanip>

using namespace std;

// Global unordered_map to store passwords (key: account, value: password)
unordered_map<string, string> passwordDatabase;

// Function to generate a random password
string generatePassword(int length = 12) {
    const string chars = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!@#$%^&*";
    string password;
    srand(time(0));
    for (int i = 0; i < length; ++i) {
        password += chars[rand() % chars.size()];
    }
    return password;
}

// Function to check password strength
bool checkPasswordStrength(const string& password) {
    regex strongPasswordRegex("^(?=.*[a-z])(?=.*[A-Z])(?=.*\\d)(?=.*[@$!%*?&])[A-Za-z\\d@$!%*?&]{8,}$");
    return regex_match(password, strongPasswordRegex);
}

// Function to add a new password
void addPassword() {
    string account, password;
    cout << "Enter account name: ";
    cin >> account;

    if (passwordDatabase.find(account) != passwordDatabase.end()) {
        cout << "Account already exists. Use edit to change the password.\n";
        return;
    }

    cout << "Enter password: ";
    cin >> password;

    if (!checkPasswordStrength(password)) {
        cout << "Weak password! Must contain at least 8 characters, including uppercase, lowercase, digit, and special character.\n";
        return;
    }

    passwordDatabase[account] = password;
    cout << "Password added successfully.\n";
}

// Function to edit an existing password
void editPassword() {
    string account, password;
    cout << "Enter account name: ";
    cin >> account;

    if (passwordDatabase.find(account) == passwordDatabase.end()) {
        cout << "Account not found.\n";
        return;
    }

    cout << "Enter new password: ";
    cin >> password;

    if (!checkPasswordStrength(password)) {
        cout << "Weak password! Must contain at least 8 characters, including uppercase, lowercase, digit, and special character.\n";
        return;
    }

    passwordDatabase[account] = password;
    cout << "Password updated successfully.\n";
}

// Function to delete a password
void deletePassword() {
    string account;
    cout << "Enter account name to delete: ";
    cin >> account;

    if (passwordDatabase.erase(account)) {
        cout << "Password deleted successfully.\n";
    } else {
        cout << "Account not found.\n";
    }
}

// Function to search for a password
void searchPassword() {
    string account;
    cout << "Enter account name to search: ";
    cin >> account;

    if (passwordDatabase.find(account) != passwordDatabase.end()) {
        cout << "Password for account " << account << ": " << passwordDatabase[account] << "\n";
    } else {
        cout << "Account not found.\n";
    }
}

// Function to list all accounts
void listAccounts() {
    if (passwordDatabase.empty()) {
        cout << "No accounts stored.\n";
        return;
    }

    cout << "Stored accounts:\n";
    for (const auto& entry : passwordDatabase) {
        cout << "- " << entry.first << "\n";
    }
}

// Main menu
void menu() {
    while (true) {
        cout << "\n--- Secure Password Management System ---\n";
        cout << "1. Add Password\n";
        cout << "2. Edit Password\n";
        cout << "3. Delete Password\n";
        cout << "4. Search Password\n";
        cout << "5. List Accounts\n";
        cout << "6. Generate Password\n";
        cout << "7. Exit\n";
        cout << "Choose an option: ";

        int choice;
        cin >> choice;

        switch (choice) {
            case 1:
                addPassword();
                break;
            case 2:
                editPassword();
                break;
            case 3:
                deletePassword();
                break;
            case 4:
                searchPassword();
                break;
            case 5:
                listAccounts();
                break;
            case 6: {
                int length;
                cout << "Enter desired password length: ";
                cin >> length;
                cout << "Generated Password: " << generatePassword(length) << "\n";
                break;
            }
            case 7:
                cout << "Exiting...\n";
                return;
            default:
                cout << "Invalid option. Try again.\n";
        }
    }
}

int main() {
    menu();
    return 0;
}
