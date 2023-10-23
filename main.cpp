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
void saveAccounts(vector<Account>);
vector<Student> loadStudents();
void saveStudents(vector<Student>);


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
 * Parse data stored in string delimited by ',' (comma) into a collection of the data
 * @param unparsedData Unparsed string of data, delimited by ',' (comma)
 * @return A collection of the parsed data
*/
vector<string> parseData(string unparsedData)
{
    vector<string> data;
    string parsed;
    int startI = 0, endI;
    
    // Find index of comma (the delimiter)
    endI = unparsedData.find_first_of(',', startI);
    // When endI == npos is true, it means the comma character can't be found anymore
    while (endI != unparsedData.npos)
    {
        parsed = unparsedData.substr(startI, endI - startI); // Take the substring of the data
        data.push_back(parsed); // Store it
        startI = endI + 1;
        endI = unparsedData.find_first_of(',', startI);
    }

    // Parse the endmost data in the string
    parsed = unparsedData.substr(startI);
    data.push_back(parsed);

    return data;
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
        vector<string> parsed = parseData(curLine);
        Account account;
        account.username = parsed.at(0);
        account.password = parsed.at(1);
        account.role = parsed.at(2);
        if (account.role == "STUDENT")
            account.refStudentId = parsed.at(3);
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

Student stringToStudent(string rawStudentData)
{

}

vector<Student> loadStudents()
{
    ifstream readAccountsData("students.txt");
    string curLine;
    vector<Student> students;

    while (getline(readAccountsData, curLine))
    {
        students.push_back(stringToStudent(curLine));
    }
}
