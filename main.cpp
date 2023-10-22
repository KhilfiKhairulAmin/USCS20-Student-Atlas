#include <iostream>
#include <vector>
#include <fstream>
using namespace std;

/** TODO
 * 1. CRUD operations for database (txt file)
 *      - Account data
 *      - Student data
 * 2. Parser for txt file
*/

/**
 * Account datatype
*/
struct Account
{
    string username;
    string password;
    string authority;
    string refStudentId;
};

/**
 * Student datatype
*/
struct Student
{
    string studentId;
    string icNumber;
    int age;
    string programme;
    int numOfSubjects;
    float cgpa;
};

vector<Account> loadAccounts();


int main ()
{
    cout << "Project Time";
    vector<Account> accounts = loadAccounts();

    cout << accounts.at(0).username << accounts.at(0).authority;

    return 0;
}

/**
 * Parse a string of account data into an account object.
 * @param rawAccountData Unparsed account string
*/
Account accountParser (string rawAccountData)
{
    int startI = 0, endI;
    string parsed;
    Account account;

    endI = rawAccountData.find_first_of(',', startI);
    parsed = rawAccountData.substr(startI, endI);
    account.username = parsed;
    startI = endI + 1;

    endI = rawAccountData.find_first_of(',', startI);
    parsed = rawAccountData.substr(startI, endI);
    account.password = parsed;
    startI = endI + 1;

    endI = rawAccountData.find_first_of(',');
    parsed = rawAccountData.substr(startI, endI);
    account.authority = parsed;

    if (account.authority == "STUDENT")
    {
        startI = endI + 1;
        endI = rawAccountData.find_first_of(',');
        parsed = rawAccountData.substr(startI, endI);
        account.refStudentId = parsed;
    }

    return account;

}

/**
 * Retrieve all accounts from database.
 * @return All accounts
*/
vector<Account> loadAccounts()
{
    ifstream readAccountsData("accounts.txt");
    string curLine;
    vector<Account> accounts;

    while (getline(readAccountsData, curLine))
    {
        cout << curLine << endl;
        accounts.push_back(accountParser(curLine));
    }
    
    readAccountsData.close();
    return accounts;
}
