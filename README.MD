 <h3 align="LockIT Password Manager"</h3>


## Table Of Contents

* [About the Project](#about-the-project)
* [Built With](#built-with)
* [Getting Started](#getting-started)
  * [Prerequisites](#prerequisites)
  * [Installation](#installation)
* [Usage](#usage)
* [Authors](#authors)


## About The Project
This is a simple password manager, "LockIT," implemented in C. LockIT allows users to securely store and manage their passwords in a file called vault.txt. The program provides functionalities such as listing passwords, getting a password, editing passwords, deleting passwords, and generating random passwords.
Features
Listing Passwords: View a list of stored passwords in the vault.txt file.

Getting a Password: Retrieve a specific password based on its ID.

Editing Passwords: Modify an existing password by providing its ID.

Deleting Passwords: Remove a password from the vault by specifying its ID.

Generating Passwords: Create random passwords of user-defined length and store them in the vault.

Encryption
LockIT uses a simple encryption mechanism based on XOR operations with a predefined key (THE_KEY). This key is essential for encrypting and decrypting passwords.

## Built With

c language

### Prerequisites

Ensure you have a C compiler installed on your system (e.g., GCC).
Compile the code using a command like 'gcc password_manager.c -o lockit'.
Run the executable with './lockit'.

## Usage

1-Initialization:
When you run the program for the first time, it initializes the vault.txt file with an initial password (ID -1). You need to choose a username and password during this setup.

2-Login:
To access the password manager, you need to log in with your username and password.

3-Main Menu:
Once logged in, you are presented with a menu offering various options for managing passwords.

4-Functionality:
Choose options from the menu to list passwords, get a password, edit passwords, delete passwords, or generate a new password.

5-Exit:
To exit the program, select option 6.

## Authors

Nazim AZZOUZ
