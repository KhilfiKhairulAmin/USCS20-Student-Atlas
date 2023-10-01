#include <iostream>

using namespace std;

// Basic register prototype
bool registerAccount (string username, string password, string repeatPassword)
{
  // Username validation
  if (username.size() == 0 || username.find_first_of(' ') == username.size())
  {
    cout << "Username cannot be empty & cannot contain blanks (' ').";
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
  cout << "Password: " << '*' * password.size() << endl;

  return true;
}

// Basic authorization prototype
bool loginAuth (string username, string password)
{
  // Using preset value to mock functionality
  if (username == "khilfi" && password == "1234")
  {
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
    cout << "Please enter your username and password to login." << endl;

    string usernameIn, passwordIn;

    cout << "Username: ";
    cin >> usernameIn;
    cout << "Password: ";
    cin >> passwordIn;

    if (!loginAuth(usernameIn, passwordIn))
    {
      cout << "Invalid username or password" << endl;
      continue;
    }

    cout << "Welcome " << usernameIn << "!";
    return 0;
  }
}
