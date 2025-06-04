#include <iostream>
#include <fstream>
#include <string>
#include <filesystem>
#include <cctype>

using namespace std;
namespace fs = std::filesystem;

const string USERS_DIR = "./users/";

// Functions Prototypes
bool is_valid_username(const string &username);
bool is_valid_password(const string &password);
bool user_exists(const string &username);
void register_user();
void login_user();

int main()
{
    int choice;

    cout << "=======================================\n";
    cout << "     Login and Registration System     \n";
    cout << "=======================================\n";

    do
    {
        cout << "\n1. Register\n2. Login\n3. Exit\nChoose an option: ";
        cin >> choice;

        switch (choice)
        {
            case 1: register_user(); break;
            case 2: login_user(); break;
            case 3: cout << "GoodBye!\n";
            default: cout << "Invalid option. Try again.\n";
        }
    } while (choice != 3);

    cout << "=======================================\n";
    return 0;
}

// Utility function to check if a username exists
bool user_exists(const string &username)
{
    return fs::exists(USERS_DIR + username + ".txt");
}

// Funciton to check if the username has at least a number
bool is_valid_username(const string &username)
{
    bool has_digit = false;

    for (char c : username)
        if (isdigit(c))
            has_digit = true;
    
    return has_digit;
}

// Function to check if the password >= 8 chars and has a symbol and a digit
bool is_valid_password(const string &password)
{
    if (password.length() < 8)
        return false;

    bool has_letter = false, has_digit = false, has_symbol = false;
    
    for (char c : password)
    {
        if (isalpha(c))
            has_letter = true;
        else if (isdigit(c))
            has_digit = true;
        else
            has_symbol = true;
    }

    return has_letter && has_digit && has_symbol;
}

// Registration function
void register_user()
{
    string username, password;

    cout << "=== User Registration ===\n";
    
    // prompt for the username
    while (true)
    {
        cout << "Enter username\n(must contain at least one number)\n>> ";
        cin >> username;

        if (!is_valid_username(username))
        {
            cout << "Invalid username. It must contain at least one number.\n";
            continue;
        }
        if (user_exists(username))
        {
            cout << "Username already exists. Try another one.\n";
            continue;
        }

        break;
    }

    // prompt for the password
    while (true)
    {
        cout << "Enter password\n(min 8 characters, must include letters, numbers, and symbols)\n>> ";
        cin >> password;

        if (!is_valid_password(password))
        {
            cout << "Weak password. Try again.\n";
            continue;
        }

        break;
    }


    // Create users directory if not exists
    fs::create_directory(USERS_DIR);

    ofstream file(USERS_DIR + username + ".txt");
    file << username << "\n" << password << endl;
    file.close();
    
    cout << "Registration successful. You can now log in.\n";
}

// Login Function
void login_user()
{
    string username, password;

    cout << "=== User Login ===\n";
    cout << "Enter username: ";
    cin >> username;

    if (!user_exists(username))
    {
        cout << "User not found. Please register first.\n";
        return;
    }

    cout << "Enter password: ";
    cin >> password;

    ifstream file(USERS_DIR + username + ".txt");
    string stored_username, stored_password;
    getline(file, stored_username);
    getline(file, stored_password);
    file.close();

    if (password == stored_password)
        cout << "Login successful. Welcome, " << stored_username << "!\n";
    else
        cout << "Incorrect password. Access denied.\n";
}