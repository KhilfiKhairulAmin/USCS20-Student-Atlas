#include <iostream>
#include <string>
using namespace std;

// These codes are written by Iyasze

void login();
void signUp();

int main()
{
    int choice;

    cout << "___________________________________\n";
    cout << "| WELCOME TO INTEC STUDENT RECORD |\n";
    cout << "-----------------------------------\n";

    cout << "\nDo you have an existing record?\n";
    cout << "1. Yes\n";
    cout << "2. No\n";
    
    do
    {

        cout << "Option: ";
        cin >> choice;

        if(choice > 2 || choice < 1)
        {
            cout << "\nPlease enter option correctly.\n";
        }

    }
    while(choice > 2 || choice < 1);

    switch(choice)
    {
        case 1:
        login();
        break;
        case 2:
        signUp();
        break;
    }

    return 0;

}

void login()
{
    string user_test = "iyas";
    string pass_test = "12345";

    string username, password;

    cout << "_______________\n";
    cout << "|    LOG IN   |\n";
    cout << "---------------\n";

    do
    {
        cout << "Please enter username: ";
        cin >> username;

        cout << "\nPlease enter password: ";
        cin >> password;

        if(username == user_test && password == pass_test)
        {
            cout << "\nlogin successful!";
            break;
        }
        else
        {
            cout << "\nLogin failed.\n";
            cout << "Please enter username and password again.\n\n";

        }
    }
    while(1);

    return;
}

void signUp()
{
    string username, password, fullname, program;
    int age, nosub, studentid, year, day, month;

    cout << "________________________\n";
    cout << "| STUDENT REGISTRATION |\n";
    cout << "------------------------\n";

    cout << "Full Name:";
    getline(cin >> ws, fullname);
    cout << "Age: ";
    cin >> age;
    cout << "Birthdate: \n";
    cout << "Day(1-30): "; cin >> day; cout << "Month (1 - 12): "; cin >> month; cout << "Year (2xxx): "; cin >> year;

    return;
}