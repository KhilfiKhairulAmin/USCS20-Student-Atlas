#include <iostream>

using namespace std;

// Basic authorization prototype
bool authorize (string username, string password)
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

    if (!authorize(usernameIn, passwordIn))
    {
      cout << "Invalid username or password" << endl;
      continue;
    }

    cout << "Welcome " << usernameIn << "!";
    return 0;
  }
}
