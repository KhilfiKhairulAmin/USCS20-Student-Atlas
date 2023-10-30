#include <iostream> // For user input and output
#include <vector> // For flexible array datatype
#include <fstream> // For file operations
#include <cmath> // For complicated mathematical operations
#include <sstream> // For handling numerical to string conversion
using namespace std;


// DATA STRUCTURE DEFINITION

// Account datatype
struct Account
{
    int accountId;
    string username;
    string password;
    string role;
    int refStudentId;
};

// Student datatype
struct Student
{
    int studentId;
    string firstName;
    string lastName;
    unsigned short int age;
    string icNumber;
    string programme;
    unsigned short int numOfSubjects;
    float cgpa;
};


// GLOBAL VARIABLES DECLARATION

// Global variable that holds all account data
vector<Account> AccountData;
// Global variable that holds all student data
vector<Student> StudentData;
// Global variable that stores error message
string ErrMsg;


// PROGRAM FUNCTION PROTOTYPES

void loadAccounts();
void saveAccounts();
int createAccount(string, string, string);
bool updateAccount(int, string, string, string);
void printAccounts();
bool deleteAccount(int);
void loadStudents();
void saveStudents();
int createStudent(int, string, string, int, string, string, int, float);
void printStudents();


int main()
{
    loadAccounts(); loadStudents();
    printAccounts();
    deleteAccount(1);
    printAccounts();
    saveAccounts(); saveStudents();
    
    return 0;
}


// UTILITY FUNCTION PROTOTYPES

vector<string> parseData(string);
string accountToString(Account);
string studentToString(Student);
int stringToUint(string);
float stringToPositiveFloat(string);
template <class T>
string numToString(T);
int searchIndexAccount(int);
int searchIndexStudent(int);


// PROGRAM FUNCTIONS DEFINITION

/**
 * Retrieve all accounts from database.
 * @return All accounts
*/
void loadAccounts()
{
    ifstream readAccountsData("accounts.txt");
    string curLine;

    while (getline(readAccountsData, curLine))
    {
        vector<string> parsed = parseData(curLine);
        Account account;
        account.accountId = stringToUint(parsed[0]);
        account.username = parsed[1];
        account.password = parsed[2];
        account.role = parsed[3];
        if (account.role == "STUDENT")
            account.refStudentId = stringToUint(parsed[4]);
        AccountData.push_back(account);
    }
    
    readAccountsData.close();

    return;
}

/**
 * Save all accounts into database.
*/
void saveAccounts()
{
    string save = "";
    for (int i = 0; i < AccountData.size(); i++)
    {
        save += accountToString(AccountData[i]);
    }

    ofstream writeAccounts("accounts.txt");
    writeAccounts << save;
    writeAccounts.close();
}

int createAccount(string username, string password, string repeatPassword)
{
    // Data validation will be implemented in registerAccount

    int accountId = AccountData.size();

    Account newAccount = {
        accountId,
        username,
        password,
        "STUDENT"
    };

    AccountData.push_back(newAccount);

    return accountId;
}

void printAccounts()
{
    for (int i = 0; i < AccountData.size(); i++)
        cout << accountToString(AccountData[i]);
}

bool updateAccount(int accountId, string username, string oldPassword, string newPassword)
{
    if (oldPassword != AccountData[accountId].password)
    {
        ErrMsg = "Old password is not correct";
        return false;
    }

    Account updateAccount = {
        accountId,
        username,
        oldPassword,
        AccountData[accountId].role,
        AccountData[accountId].refStudentId
    };
    AccountData[accountId] = updateAccount;

    return true;
}

/**
 * Delete an account, and the student related to the account.
 * @param accountId Account ID
*/
bool deleteAccount(int accountId)
{
    int accountIndex = searchIndexAccount(accountId);
    Account account = AccountData[accountIndex];

    if (accountIndex == -1)
    {
        ErrMsg = "Account with accountId " + numToString(accountId) + " does not found";
        return false;
    }

    if (account.role == "ADMIN")
    {
        ErrMsg = "Admin account can't be deleted through this program";
        return false;
    }
    else if (account.role == "STUDENT")
    {
        int studentIndex = searchIndexStudent(account.refStudentId);
        StudentData.erase(StudentData.begin() + studentIndex);
    }
    
    AccountData.erase(AccountData.begin() + accountIndex);

    return true;
}

/**
 * Loads all student data
*/
void loadStudents()
{
    ifstream readStudentsData("students.txt");
    string curLine;
    vector<Student> students;

    while (getline(readStudentsData, curLine))
    {
        vector<string> parsed = parseData(curLine);
        Student student;
        student.studentId = stringToUint(parsed[0]);
        student.firstName = parsed[1];
        student.lastName = parsed[2];
        student.age = stringToUint(parsed[3]);
        student.icNumber = parsed[4];
        student.programme = parsed[5];
        student.numOfSubjects = stringToUint(parsed[6]);
        student.cgpa = stringToPositiveFloat(parsed[7]);
        StudentData.push_back(student);
    }

    readStudentsData.close();

    return;
}

/**
 * Save all students in this session
*/
void saveStudents()
{
    string save = "";
    for (int i = 0; i < StudentData.size(); i++)
    {
        save += studentToString(StudentData[i]);
    }

    ofstream writeStudents("students.txt");
    writeStudents << save;
    writeStudents.close();
}

int createStudent(int accountId, string firstName, string lastName, int age, string icNumber, string programme, int numOfSubjects, float cgpa)
{
    int studentId = StudentData.size();

    Student newStudent = {
        studentId,
        firstName,
        lastName,
        age,
        icNumber,
        programme,
        numOfSubjects,
        cgpa
    };

    // Link account with student data
    AccountData[accountId].refStudentId = studentId;

    StudentData.push_back(newStudent);

    return studentId;
}

void printStudents()
{
    for (int i = 0; i < StudentData.size(); i++)
        cout << studentToString(StudentData[i]);
}

bool updateStudent(int studentId, string firstName, string lastName, int age, string icNumber, string programme, int numOfSubjects, float cgpa)
{
    Student updateStudent = {
        studentId,
        firstName,
        lastName,
        age,
        icNumber,
        programme,
        numOfSubjects,
        cgpa
    };

    StudentData[searchIndexStudent(studentId)] = updateStudent;

    return true;
}

int searchIndexAccount(int accountId)
{
    for (int i = 0; i < AccountData.size(); i++)
    {
        if (AccountData[i].accountId == accountId)
        {
            return i;
        }
    }
    return -1;
}

int searchIndexStudent(int studentId)
{
    for (int i = 0; i < StudentData.size(); i++)
    {
        if (StudentData[i].studentId == studentId)
        {
            return i;
        }
    }
    return -1;
}


// ALL UTILITY FUNCTIONS

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
 * Parse an account into an account string
*/
string accountToString(Account account)
{
    return numToString(account.accountId) + ',' + account.username + ',' + account.password + ',' + account.role + ',' + numToString(account.refStudentId) + '\n';
}

/**
 * Convert student to string representation
*/
string studentToString(Student student)
{
    return numToString(student.studentId) + ',' + student.firstName + ',' + student.lastName + ',' + numToString(student.age)
           + ',' + student.icNumber + ',' + student.programme + ',' + numToString(student.numOfSubjects) + ','
           + numToString(student.cgpa) + '\n';
}

/**
 * Convert whole number string to positive integer
*/
int stringToUint(string s)
{
    int result;
    for(int i = 0; i < s.size(); i++)
    {
        int digit = s[i] - '0';
        result += digit * pow(10, s.size() - 1 - i);
    }
    return result;
}

/**
 * Convert numeric string to positive float
*/
float stringToPositiveFloat(string s)
{
    float result = 0.0;
    int lenDigitBeforeDecPoint = s.find_first_of('.');
    string beforeDec, afterDec;

    // Early return numerical string contains no decimal point, it represents integer!
    if (lenDigitBeforeDecPoint == s.npos)
        return stringToUint(s);
    else
    {
        beforeDec = s.substr(0, lenDigitBeforeDecPoint);
        afterDec = s.substr(lenDigitBeforeDecPoint + 1);
    }

    // Handles digit before decimal point
    result += stringToUint(beforeDec);

    // Handles digit after decimal point
    for (int i = 0; i < afterDec.size(); i++)
    {
        float digit = afterDec[i] - '0';
        result += digit / pow(10, i + 1);
    }

    return result;
}

template <class T>
string numToString(T n)
{
    stringstream out;
    out << n;
    return out.str();
}
