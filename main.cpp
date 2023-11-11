#include <iostream> // For user input and output
#include <fstream> // For file operations
#include <cmath> // For complicated mathematical operations
#include <sstream> // For handling numerical to string conversion
using namespace std;


// DATA STRUCTURE DEFINITION

// Account datatype
struct Account
{
    int id = -1;
    string username;
    string password;
    string role;
    int refStudentId;
};

// Student datatype
struct Student
{
    int id = -1;
    string firstName;
    string lastName;
    unsigned short int age;
    string icNumber;
    string programme;
    unsigned short int numOfSubjects;
    float cgpa;
};


// GLOBAL VARIABLES DECLARATION

// Constant to control the maximum number of data an array can hold
const int MAX_SIZE = 200;

// Global array storing all `Account` data
Account Accounts[MAX_SIZE] = {Account()};

// Global array storing all `Student` data
Student Students[MAX_SIZE];

// Global variable storing the latest Error m6essage
string ErrMsg = "";


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

Account parseAccount(string);
Student parseStudent(string);
template<class T> int generateId(T [MAX_SIZE]);
template<class T> int getEmptyPosition(T [MAX_SIZE]);
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
*/
void loadAccounts()
{
    // Open the file
    ifstream readAccountsData("accounts.txt");
    string currentLine;

    int i = 0;
    // Read the file line by line
    while (getline(readAccountsData, currentLine))
    {
        Account account = parseAccount(currentLine);
        // Assign each account into the global array
        Accounts[i++] = account;
    }
    
    readAccountsData.close();

    return;
}

/**
 * Save all accounts into text file
*/
void saveAccounts()
{
    string save = "";
    int i = 0;

    // If i does not exceed max array size AND accountId is valid, continue loop
    while (i < MAX_SIZE && Accounts[i].id != -1)
    {
        // Convert to string form to be saved in .txt file
        save += accountToString(Accounts[i++]);
    }

    // Write string into text file
    ofstream writeAccounts("accounts.txt");
    writeAccounts << save;
    writeAccounts.close();

    return;
}

/**
 * Create a new `Account`
*/
int createAccount(string username, string password, string repeatPassword)
{
    // Get new id
    int accountId = generateId(Accounts);

    // Create new account
    Account newAccount = {
        accountId,
        username,
        password,
        "STUDENT"
    };

    // Find the position of empty space in the array
    int empty = getEmptyPosition(Accounts);

    // Array is fully used
    if (empty == -1)
    {
        ErrMsg = "Maximum size reached. Cannot add new Account.";
        // Return invalid id to represent error occurred
        return -1;
    }

    // Assign to empty location in `Accounts` array
    Accounts[empty] = newAccount;

    return accountId;
}

/**
 * Display all `Account` data
*/
void printAccounts()
{
    for (int i = 0; i <; i++)
        cout << accountToString(Accounts[i]);
}

bool updateAccount(int accountId, string username, string oldPassword, string newPassword)
{
    if (oldPassword != Accounts[accountId].password)
    {
        ErrMsg = "Old password is not correct";
        return false;
    }

    Account updateAccount = {
        accountId,
        username,
        oldPassword,
        Accounts[accountId].role,
        Accounts[accountId].refStudentId
    };
    Accounts[accountId] = updateAccount;

    return true;
}

/**
 * Delete an account, and the student related to the account.
 * @param accountId Account ID
*/
bool deleteAccount(int accountId)
{
    int accountIndex = searchIndexAccount(accountId);
    Account account = Accounts[accountIndex];

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
        Students.erase(Students.begin() + studentIndex);
    }
    
    Accounts.erase(Accounts.begin() + accountIndex);

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
        student.id = stringToUint(parsed[0]);
        student.firstName = parsed[1];
        student.lastName = parsed[2];
        student.age = stringToUint(parsed[3]);
        student.icNumber = parsed[4];
        student.programme = parsed[5];
        student.numOfSubjects = stringToUint(parsed[6]);
        student.cgpa = stringToPositiveFloat(parsed[7]);
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
    for (int i = 0; i < Students.size(); i++)
    {
        save += studentToString(Students[i]);
    }

    ofstream writeStudents("students.txt");
    writeStudents << save;
    writeStudents.close();
}

int createStudent(int accountId, string firstName, string lastName, int age, string icNumber, string programme, int numOfSubjects, float cgpa)
{
    int studentId = Students.size();

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
    Accounts[accountId].refStudentId = studentId;

    Students.push_back(newStudent);

    return studentId;
}

void printStudents()
{
    for (int i = 0; i < Students.size(); i++)
        cout << studentToString(Students[i]);
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

    Students[searchIndexStudent(studentId)] = updateStudent;

    return true;
}

int searchIndexAccount(int accountId)
{
    for (int i = 0; i < Accounts.size(); i++)
    {
        if (Accounts[i].id == accountId)
        {
            return i;
        }
    }
    return -1;
}

int searchIndexStudent(int studentId)
{
    for (int i = 0; i < Students.size(); i++)
    {
        if (Students[i].id == studentId)
        {
            return i;
        }
    }
    return -1;
}


// ALL UTILITY FUNCTIONS

Account parseAccount(string unparsedText)
{
    string parsedString, parsedData[5];

    // Index used to parse string from startIndex to endIndex
    // Initial start is at index 0 and end is at the position of first delimiter (,)
    int startIndex = 0, endIndex = unparsedText.find_first_of(',');

    do
    {
        // Parse the data point
        parsedString = unparsedText.substr(startIndex, endIndex - startIndex);

        // Add the data point in this array
        parsedData->append(parsedString);

        // Update the start and end index
        startIndex = endIndex + 1;
        endIndex = unparsedText.find_first_of(',', startIndex);
    } // If endIndex == string.npos, then it means no more delimiter is found, thus ending the loop
    while (endIndex != unparsedText.npos);
    
    // Get the final data point
    parsedString = unparsedText.substr(startIndex);
    parsedData->append(parsedString);

    Account account;
    account.id = stringToUint(parsedData[0]);
    account.username = parsedData[1];
    account.password = parsedData[2];
    account.role = parsedData[3];
    if (account.role == "STUDENT")
        account.refStudentId = stringToUint(parsedData[4]);

    return account;
}

Student parseStudent(string rawString)
{
    string data[7], parsed;

    int startI = 0, endI;
    endI = rawString.find_first_of(',', startI);

    // When endI == npos is true, it means the comma character can't be found anymore
    while (endI != rawString.npos)
    {
        parsed = rawString.substr(startI, endI - startI); // Take the substring of the data
        data->append(parsed); // Store it
        startI = endI + 1;
        endI = rawString.find_first_of(',', startI);
    }

    // Parse the endmost data in the string
    parsed = rawString.substr(startI);
    data->append(parsed);

    Student student;
    student.id = stringToUint(data[0]);
    student.firstName = data[1];
    student.lastName = data[2];
    student.age = stringToUint(data[3]);
    student.icNumber = data[4];
    student.programme = data[5];
    student.numOfSubjects = stringToUint(data[6]);
    student.cgpa = stringToPositiveFloat(data[7]);

    return student;
}

/**
 * Generate a unique ID for new `Account` and new `Student`
*/
template<class T> 
int generateId(T array[MAX_SIZE])
{
    int maxId = array[0].id;
    // Search for highest index in the array (i.e. id which value is -1)
    for (int i = 0; i < MAX_SIZE; i++)
    {
        if (array[i].id == -1)
            break;
        else if (array[i].id > maxId)
            maxId = array[id].id
    }

    // Return the next highest id
    return ++maxId;
}

/**
 * Get the number of elements in the array
*/
template<class T>
int len(T array[MAX_SIZE])
{
    // Search for unused position in array (i.e. id which value is -1)
    for (int i = 0; i < MAX_SIZE; i++)
    {
        if (array[i].id == -1)
            return i + 1
    }
    // Array is fully used
    return MAX_SIZE
}

/**
 * Find an index in the array which is empty. Return `-1` if array is full.
*/
template<class T>
int getEmptyPosition(T array[MAX_SIZE])
{
    int length = len(array);
    if (length == MAX_SIZE)
        return -1;
    return length;
}

/**
 * Parse an account into an account string
*/
string accountToString(Account account)
{
    return numToString(account.id) + ',' + account.username + ',' + account.password + ',' + account.role + ',' + numToString(account.refStudentId) + '\n';
}

/**
 * Convert student to string representation
*/
string studentToString(Student student)
{
    return numToString(student.id) + ',' + student.firstName + ',' + student.lastName + ',' + numToString(student.age)
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
