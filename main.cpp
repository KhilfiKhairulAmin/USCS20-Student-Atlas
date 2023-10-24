#include <iostream> // For user input and output
#include <vector> // For flexible array datatype
#include <fstream> // For file operations
#include <cmath> // For complicated mathematical operations
#include <sstream> // For handling numerical to string conversion
using namespace std;

/** TODO: CRUD operations for database (txt file)
 *  ✅ Account data type
 *  ✅ Student data type
 *  ✅ Load accounts data (READ)
 *  ✅ Store accounts data
 *  ✅ Load students data (READ)
 *  ✅ Store students data
 *  ⏳ Insert new account data (CREATE)
 *  ⏳ Insert new student data (CREATE)
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


// DATA STRUCTURE DEFINITION

/**
 * Account datatype
*/
struct Account
{
    int accountId;
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
    int studentId;
    string firstName;
    string lastName;
    unsigned short int age;
    string icNumber;
    string programme;
    unsigned short int numOfSubjects;
    float cgpa;
};


// GLOBAL VARIABLES

/** Global variable that holds accounts data */
vector<Account> AccountData;
/** Global variable that holds students data */
vector<Student> StudentData;


// PROGRAM FUNCTION PROTOTYPES

void loadAccounts();
void saveAccounts();
int createAccount(string, string, string);
void printAccounts();
void loadStudents();
void saveStudents();
int createStudent();
void printStudents();


int main()
{
    loadAccounts();
    printAccounts();
    createAccount("infietech", "infie123", "infie123");
    printAccounts();
    saveAccounts();
    
    return 0;
}


// UTILITY FUNCTION PROTOTYPES

vector<string> parseData(string);
string accountToString(Account);
string studentToString(Student);
int stringToUint(string);
float stringToPositiveFloat(string);
string numToString(int);
string numToString(float);


// PROGRAM FUNCTIONS IMPLEMENTATION

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
        account.accountId = stringToUint(parsed.at(0));
        account.username = parsed.at(1);
        account.password = parsed.at(2);
        account.role = parsed.at(3);
        if (account.role == "STUDENT")
            account.refStudentId = parsed.at(4);
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
        save += accountToString(AccountData.at(i));
    }

    ofstream writeAccounts("accounts.txt");
    writeAccounts << save;
    writeAccounts.close();
}

int createAccount(string username, string password, string repeatPassword)
{
    // TODO Data validation createAccount

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
    {
        cout << AccountData.at(i).accountId << " " << AccountData.at(i).username << endl;
    }
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
        student.studentId = stringToUint(parsed.at(0));
        student.firstName = parsed.at(1);
        student.lastName = parsed.at(2);
        student.age = stringToUint(parsed.at(3));
        student.icNumber = parsed.at(4);
        student.programme = parsed.at(5);
        student.numOfSubjects = stringToUint(parsed.at(6));
        student.cgpa = stringToPositiveFloat(parsed.at(7));
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
        save += studentToString(StudentData.at(i));
    }

    ofstream writeStudents("students.txt");
    writeStudents << save;
    writeStudents.close();
}

int createStudent(string firstName, string lastName, int age, string icNumber, string programme, int numOfSubjects, float cgpa)
{
    // TODO Data validation createStudent

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

    StudentData.push_back(newStudent);

    return studentId;
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
    return numToString(account.accountId) + ',' + account.username + ',' + account.password + ',' + account.role + ',' + account.refStudentId + '\n';
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

string numToString(int n)
{
    stringstream out;
    out << n;
    return out.str();
}

string numToString(float n)
{
    stringstream out;
    out << n;
    return out.str();
}
