#include <iostream>
#include <vector>
#include <fstream>
using namespace std;

/** TODO: CRUD operations for database (txt file)
 *  ✅ Account data type
 *  ✅ Student data type
 *  ✅ Load accounts data (READ)
 *  ✅ Store accounts data (CREATE)
 *  ⏳ Load students data (READ)
 *  ⏳ Store students data (CREATE)
 *  ⏳ Delete accounts data (DELETE) *CASCADE to STUDENT as well
 *  ⏳ Update accounts data (UPDATE)
 *  ⏳ Update students data (UPDATE)
*/

/** TODO: Data validation
 *  ⏳ Limited character input
 *  ⏳ Realistic number range
 *  ⏳ Unique identifiers/keys
 *  ⏳ Character literals formatted correctly based on context of data
*/

/**
 * Account datatype
*/
struct Account
{
    string username;
    string password;
    string role;
    string refStudentId;
};

/**
 * Student datatype
*/
struct Student
{
    string studentId;
    string icNumber;
    unsigned short int age;
    string programme;
    unsigned short int numOfSubjects;
    float cgpa;
};

vector<Account> loadAccounts();
void saveAccounts(vector<Account> accounts);


int main()
{
    cout << "Project Time";
    vector<Account> accounts = loadAccounts();

    Account newAcc; newAcc.username = "nazrin"; newAcc.password = "naz123rin"; newAcc.role = "STUDENT"; newAcc.refStudentId = "3";
    accounts.push_back(newAcc);

    for (int i = 0; i < accounts.size(); i++)
        cout << accounts.at(i).username << " " << accounts.at(i).role << endl;

    saveAccounts(accounts);

    return 0;
}

/**
 * Parse a string of account data into an account object.
 * @param rawAccountData Unparsed account string
*/
Account stringToAccount(string rawAccountData)
{
    int startI = 0, endI;
    string parsed;
    Account account;

    // Parse account username
    endI = rawAccountData.find_first_of(',', startI);
    parsed = rawAccountData.substr(startI, endI);
    account.username = parsed;
    startI = endI + 1;

    // Parse account password
    endI = rawAccountData.find_first_of(',', startI);
    parsed = rawAccountData.substr(startI, endI - startI);
    account.password = parsed;
    startI = endI + 1;

    // Parse account role
    endI = rawAccountData.find_first_of(',', startI);
    parsed = rawAccountData.substr(startI, endI - startI);
    account.role = parsed;

    // Parse account student ID reference (only for STUDENT!)
    if (account.role == "STUDENT")
    {
        parsed = rawAccountData.substr(++endI);
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
        accounts.push_back(stringToAccount(curLine));
    }
    
    readAccountsData.close();
    return accounts;
}

/**
 * Parse an account into an account string
*/
string accountToString(Account account)
{
    return account.username + ',' + account.password + ',' + account.role + ',' + account.refStudentId + '\n';
}

/**
 * Save all accounts into database.
*/
void saveAccounts(vector<Account> accounts)
{
    string save = "";
    for (int i = 0; i < accounts.size(); i++)
    {
        save += accountToString(accounts.at(i));
    }

    ofstream writeAccounts("accounts.txt");
    writeAccounts << save;
    writeAccounts.close();
}
