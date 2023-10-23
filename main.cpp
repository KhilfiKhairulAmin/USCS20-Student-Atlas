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
 *  ✅ Store accounts data (CREATE)
 *  ✅ Load students data (READ)
 *  ✅ Store students data (CREATE)
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
    string firstName;
    string lastName;
    unsigned short int age;
    string icNumber;
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

    vector<Student> students = loadStudents();

    Student stud;
    stud.studentId = "2"; stud.firstName = "Fusuna"; stud.lastName = "Ahumadu Fuadu"; stud.age = 18; stud.icNumber = "051101020000"; stud.programme = "Japan"; stud.numOfSubjects = 10; stud.cgpa = 4.0;
    students.push_back(stud);

    saveStudents(students);
    
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
    string beforeDec = s.substr(0, lenDigitBeforeDecPoint), afterDec = s.substr(lenDigitBeforeDecPoint + 1);

    // Handles digit before decimal point
    for (int i = 0; i < beforeDec.size(); i++)
    {
        float digit = beforeDec[i] - '0';
        result += digit * pow(10, beforeDec.size() - 1 - i);
    }

    // Handles digit after decimal point
    for (int i = 0; i < afterDec.size(); i++)
    {
        float digit = afterDec[i] - '0';
        result += digit / pow(10, i + 1);
    }

    return result;
}

/**
 * Loads all student data
*/
vector<Student> loadStudents()
{
    ifstream readStudentsData("students.txt");
    string curLine;
    vector<Student> students;

    while (getline(readStudentsData, curLine))
    {
        vector<string> parsed = parseData(curLine);
        Student student;
        student.studentId = parsed.at(0);
        student.firstName = parsed.at(1);
        student.lastName = parsed.at(2);
        student.age = stringToUint(parsed.at(3));
        student.icNumber = parsed.at(4);
        student.programme = parsed.at(5);
        student.numOfSubjects = stringToUint(parsed.at(6));
        student.cgpa = stringToPositiveFloat(parsed.at(7));
        students.push_back(student);
    }

    readStudentsData.close();

    return students;
}

/**
 * Convert student to string representation
*/
string studentToString(Student student)
{
    stringstream age, numSubjects, cgpa;
    age << student.age;
    numSubjects << student.numOfSubjects;
    cgpa << student.cgpa;

    return student.studentId + ',' + student.firstName + ',' + student.lastName + ',' + age.str()
           + ',' + student.icNumber + ',' + student.programme + ',' + numSubjects.str() + ','
           + cgpa.str() + '\n';
}

/**
 * Save all students in this session
*/
void saveStudents(vector<Student> students)
{
    string save = "";
    for (int i = 0; i < students.size(); i++)
    {
        save += studentToString(students.at(i));
    }

    ofstream writeStudents("students.txt");
    writeStudents << save;
    writeStudents.close();
}
