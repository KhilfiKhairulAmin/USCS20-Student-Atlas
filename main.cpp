#include <iostream>

using namespace std;

// Basic register prototype
bool registerAccount (string username, string password, string repeatPassword)
{
  // Username validation
  int usernameSize = username.size();
  if (usernameSize == 0 || username.find_first_of(' ') < usernameSize)
  {
    cout << "Username cannot be empty & cannot contain blanks (' ').";
    return false;
  }

  int firstChar = username.at(0);
  cout << firstChar;
  if (firstChar >= 48 && firstChar <= 57)
  {
    cout << "Username cannot begin with a number.";
    return false;
  }

  // Password validations
  if (password.size() == 0)
  {
    cout << "Password can't be empty.";
    return false;
  }
  
  if (password != repeatPassword)
  {
    cout << "The re-entered password does not match the provided password.";
    return false;
  }

  cout << "Account created successfully!" << endl;
  cout << "Username: " << username << endl;
  cout << "Password: " << "********" << endl;

  return true;
}

// Basic authorization prototype
bool loginAuth (string username, string password)
{
  // Using preset value to mock functionality
  if (username == "khilfi" && password == "1234")
  {
    cout << "Invalid username or password" << endl;
    return true;
  }
  return false;
}

// This is where program starts executing
int main ()
{
  cout << "Welcome to INTEC Student Management System" << endl;
  
  while (1)
  {
    // cout << "Please enter your username and password to login." << endl;

    // string usernameIn, passwordIn;

    // cout << "Username: ";
    // cin >> usernameIn;
    // cout << "Password: ";
    // cin >> passwordIn;

    // if (!loginAuth(usernameIn, passwordIn))
    // {
    //   continue;
    // }

    // cout << "Welcome " << usernameIn << "!";

    string usernameIn, passwordIn, repeatPasswordIn;

    cout << "Register" << endl;
    cout << "Username: ";
    getline(cin, usernameIn);
    
    cout << "Password: ";
    getline(cin, passwordIn);

    cout << "Repeat password: ";
    getline(cin, repeatPasswordIn);

    if (registerAccount(usernameIn, passwordIn, repeatPasswordIn))
      break;
  }
  return 0;
}
