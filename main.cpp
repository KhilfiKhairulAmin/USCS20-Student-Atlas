#include <iostream> // For user input and output
#include <fstream> // For file operations
#include <cmath> // For complicated mathematical operations
#include <sstream> // For handling numerical to string conversion
using namespace std;


// DATA STRUCTURE DEFINITION

// Account datatype
struct Account
{
    int id;
    string username;
    string password;
    string role;
    int refStudentId;

    Account(int id_ = -1, string username_ = "", string password_ = "", string role_ = "STUDENT", int refStudentId_ = -1)
    : id(id_), username(username_), password(password_), refStudentId(refStudentId_)
    {
        id = id_;
        username = username_;
        password = password_;
        role = role_;
        refStudentId = -1;
    }

};

// Student datatype
struct Student
{
    int id;
    string firstName;
    string lastName;
    int age;
    string icNumber;
    string programme;
    int numOfSubjects;
    float cgpa;

    Student(
        int id_ = -1, string firstName_ = "", string lastName_ = "",
        int age_ = -1, string icNumber_ = "", string programme_ = "",
        int numOfSubjects_ = 0, float cgpa_ = -1)
        : id(id_), firstName(firstName_), lastName(lastName_),
        age(age_), icNumber(icNumber_), programme(programme_),
        numOfSubjects(numOfSubjects_), cgpa(cgpa_)
        {
            id = id_;
            firstName = firstName_;
            lastName = lastName_;
            age = age_;
            icNumber = icNumber_;
            programme = programme_;
            numOfSubjects = numOfSubjects_;
            cgpa = cgpa_;
        }

};


// GLOBAL VARIABLES DECLARATION

// Constant to control the maximum number of data an array can hold
const int MAX_SIZE = 200;

// Global array storing all `Account` data
Account Accounts[MAX_SIZE];

// Global array storing all `Student` data
Student Students[MAX_SIZE];

// Global variable storing the latest Error m6essage
string ErrMsg = "";


// MAIN FUNCTION PROTOTYPES (USED BY main() FUNCTION)

void loadAccounts();
void saveAccounts();
int createAccount(string, string, string);
int updateAccount(int, string, string);
void printAccounts();
bool deleteAccountCascade(int);
void loadStudents();
void saveStudents();
int createStudent(int, string, string, int, string, string, int, float);
int updateStudent(int, string, string, int, string, string, int, float);
void printStudents();


// THIS IS WHERE THE PROGRAM STARTS EXECUTING
int main()
{
    loadAccounts();
    printAccounts();
    saveAccounts();
    return 0;
}


// UTILITY FUNCTION PROTOTYPES (USED BY FUNCTIONS OTHER THAN main())

Account parseAccount(string);
Student parseStudent(string);
string parseName(string);
string unparseName(string);
template<class T> int generateId(T [MAX_SIZE]);
template<class T> int getEmptyPosition(T [MAX_SIZE]);
template<class T> int findId(T [MAX_SIZE], int);
template<class T> bool deleteAtIndex(T [MAX_SIZE], int);
template<class T> int len(T [MAX_SIZE]);
string accountToString(Account);
string studentToString(Student);
int stringToUint(string);
float stringToPositiveFloat(string);
template <class T>
string numToString(T);


// PROGRAM & UTILITY FUNCTIONS DEFINITION

/**
 * Retrieve all accounts from database.
*/
void loadAccounts()
{
    // Open the text file
    ifstream readAccountsData("accounts.txt");

    // Variables to store Account data
    int id, refStudentId;
    string username, password, role;

    // Read the first line
    readAccountsData >> id >> username >> password >> role >> refStudentId;

    int i = 0;
    // Read each data line by line
    while (readAccountsData.good())
    {
        // Assign each data into a new Account in the global array
        Accounts[i++] = Account(
            id,
            username,
            password,
            role
        );

        // Read the next line
        readAccountsData >> id >> username >> password >> role >> refStudentId;
    };
    
    // Close the text file
    readAccountsData.close();

    return;
}

/**
 * Save all accounts into text file
*/
void saveAccounts()
{
    ofstream writeAccounts("accounts.txt");

    Account account;

    // If i does not exceed max array size AND accountId is valid, continue loop
    for (int i = 0; i < len(Accounts); i++)
    {
        account = Accounts[i];
        writeAccounts << account.id << ' ' << account.username << ' ' << account.password << ' ' << account.role << ' ' << account.refStudentId << endl;
    }

    writeAccounts.close();

    return;
}

/**
 * Create a new `Account`
*/
int createAccount(string username, string password, string role)
{
    // Get new id
    int accountId = generateId(Accounts);

    // Create new account
    Account newAccount(accountId, username, password, role);

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
    for (int i = 0; i < len(Accounts); i++)
        cout << accountToString(Accounts[i]);
}

/**
 * Update `Account` with `id` to the new data. Return `pos` if the account exists, else return `-1`.
*/
int updateAccount(int accountId, string username, string newPassword)
{
    // Find position of this `Account` in array
    // TODO Keep current data if `null` is entered.
    int pos = findId(Accounts, accountId);

    if (pos == -1)
    {
        // Account is not found
        ErrMsg = "Account with id of " + numToString(accountId) + " does not exist.";
        return -1;
    }

    // Overwrite old username and password
    Accounts[pos].username = username;
    Accounts[pos].password = newPassword;

    // Return position of this account in the array
    return pos;
}

/**
 * Delete an `Account` with `id` and the `Student` related to the account.
*/
bool deleteAccountCascade(int accountId)
{
    int accountIndex = findId(Accounts, accountId);

    if (accountIndex == -1)
    {
        ErrMsg = "Account with id of " + numToString(accountId) + " does not exist.";
        return false;
    }

    Account account = Accounts[accountIndex];

    if (account.role == "ADMIN")
    {
        ErrMsg = "Admin account can't be deleted.";
        return false;
    }
    
    // int studentIndex = findId(Students, account.refStudentId);

    // if (account.role == "STUDENT")
    // {
    //     if (studentIndex == -1)
    //     {
    //         ErrMsg = "Student with id of " + numToString(account.refStudentId) + " does not exist.";
    //         return false;
    //     }
    //     deleteAtIndex(Students, studentIndex);
    // }
    
    // if (account.role == "ADMIN" && !deleteAtIndex(Accounts, accountIndex))
    // {
    //     ErrMsg = "Something went wrong.";
    //     return false;
    // }

    deleteAtIndex(Accounts, 0);

    return true;
}

/**
 * Loads all student data
*/
void loadStudents()
{
    // Open student file
    ifstream readStudentsData("students.txt");
    string currentLine;

    int i = 0;
    while (getline(readStudentsData, currentLine))
    {
        // Assign each `Student` into the global array
        Students[i++] = parseStudent(currentLine);
    }

    // Close the file
    readStudentsData.close();

    return;
}

/**
 * Save all students into text file
*/
void saveStudents()
{
    string save = "";

    int i = 0;
    // If i does not exceed max array size AND accountId is valid, continue loop
    while (i < MAX_SIZE && Students[i].id != -1)
    {
        // Convert to string form to be saved in .txt file
        save += studentToString(Students[i++]);
    }

    ofstream writeStudents("students.txt");
    writeStudents << save;
    writeStudents.close();
}

/**
 * Create a new `Student`
*/
int createStudent(
    int accountId, string firstName, string lastName,
    int age, string icNumber, string programme,
    int numOfSubjects, float cgpa
)
{
    // Get new id
    int studentId = generateId(Students);

    Student newStudent(
        studentId,
        firstName,
        lastName,
        age,
        icNumber,
        programme,
        numOfSubjects,
        cgpa
    );

    // Find the position of empty space in the array
    int empty = getEmptyPosition(Students);

    // Array is fully used
    if (empty == -1)
    {
        ErrMsg = "Maximum size reached. Cannot add new Student.";
        // Return invalid id to represent error occurred
        return -1;
    }

    // Assign to empty location in `Accounts` array
    Students[empty] = newStudent;

    // Store reference in the specified `Account` with studentId
    int accountIndex = findId(Accounts, accountId);
    Accounts[accountIndex].refStudentId = studentId;

    return studentId;
}

/**
 * Display all `Student` data
*/
void printStudents()
{
    for (int i = 0; i < len(Students); i++)
        cout << studentToString(Students[i]);
}

/**
 * Update `Student` with `id` to the new data. Return `pos` if the account exists, else return `-1`.
*/
int updateStudent(
    int studentId, string firstName, string lastName,
    int age, string icNumber, string programme,
    int numOfSubjects, float cgpa
)
{
    // Find position of this `Student` in array
    int pos = findId(Students, studentId);

    
    if (pos == -1)
    {
        // Student is not found
        ErrMsg = "Student with id of " + numToString(studentId) + " does not exist.";
        return -1;
    }

    // Overwrite old student data
    Students[pos] = Student(
        studentId,
        firstName,
        lastName,
        age,
        icNumber,
        programme,
        numOfSubjects,
        cgpa
    );

    // Return position of this student in the array
    return pos;
}

// ALL UTILITY FUNCTIONS
string parseName(string name)
{
    return name.replace(name.begin(), name.end(), '_', ' ');
}

string unparseName(string name)
{
    return name.replace(name.begin(), name.end(), ' ', '_');
}

Account parseAccount(string unparsedText)
{
    string parsedString, parsedData[5];

    // Index used to parse string from startIndex to endIndex
    // Initial start is at index 0 and end is at the position of first delimiter (,)
    int startIndex = 0, endIndex = unparsedText.find_first_of(',');

    int i = 0;
    // If endIndex == string.npos, then it means no more delimiter is found, thus ending the loop
    while (endIndex != unparsedText.npos);
    {
        // Parse the data point
        parsedString = unparsedText.substr(startIndex, endIndex - startIndex);

        // Add the data point in this array
        parsedData[i++] = parsedString;

        // Update the start and end index
        startIndex = endIndex + 1;
        endIndex = unparsedText.find_first_of(',', startIndex);
    }
    
    // Get the final data point
    parsedString = unparsedText.substr(startIndex);
    parsedData[4] = parsedString;

    Account account;
    account.id = stringToUint(parsedData[0]);
    account.username = parsedData[1];
    account.password = parsedData[2];
    account.role = parsedData[3];
    if (account.role == "STUDENT")
        account.refStudentId = stringToUint(parsedData[4]);

    return account;
}

Student parseStudent(string unparsedText)
{
    string parsedString, parsedData[7];

    // Index used to parse string from startIndex to endIndex
    // Initial start is at index 0 and end is at the position of first delimiter (,)
    int startIndex = 0, endIndex = unparsedText.find_first_of(',', 0);

    // If endIndex == string.npos, then it means no more delimiter is found, thus ending the loop
    while (endIndex != unparsedText.npos)
    {
        // Parse the data point
        parsedString = unparsedText.substr(startIndex, endIndex - startIndex);

        // Add the data point in this array
        parsedData->append(parsedString);

        // Update the start and end index
        startIndex = endIndex + 1;
        endIndex = unparsedText.find_first_of(',', startIndex);
    }

    // Get the final data point
    parsedString = unparsedText.substr(startIndex);
    parsedData->append(parsedString);

    Student student;
    student.id = stringToUint(parsedData[0]);
    student.firstName = parsedData[1];
    student.lastName = parsedData[2];
    student.age = stringToUint(parsedData[3]);
    student.icNumber = parsedData[4];
    student.programme = parsedData[5];
    student.numOfSubjects = stringToUint(parsedData[6]);
    student.cgpa = stringToPositiveFloat(parsedData[7]);

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
    for (int i = 0; i < len(array); i++)
    {
        if (array[i].id > maxId)
            maxId = array[i].id;
    }

    maxId++;

    // Return the next highest id
    return maxId;
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
            return i;
    }
    // Array is fully used
    return MAX_SIZE;
}

/**
 * Find index of target id. Return `-1` if not found.
*/
template<class T>
int findId(T array[MAX_SIZE], int targetId)
{
    // Search for index of target id
    for (int i = 0; i < MAX_SIZE; i++)
    {
        if (array[i].id == -1)
            break;
        if (array[i].id == targetId)
            return i;
    }
    return -1;
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
 * Delete an element in array and move other elements to fill the empty space. Return `false` if an error occurred, else `True`.
*/
template<class T>
bool deleteAtIndex(T array[MAX_SIZE], int index)
{
    if (index >= MAX_SIZE || index < 0)
    {
        ErrMsg = "Index at position " + numToString(index) + " is invalid.";
        return false;
    }
    array[index] = T();

    for (int i = index; i < MAX_SIZE - 1; i++)
    {
        if (array[i].id == -1)
            break;
        array[i] = array[i+1];
    }
    return true;
}

/**
 * Parse an account into an account string
*/
string accountToString(Account account)
{
    string ref = "";
    if (account.refStudentId >= 0)
    {   
        ref = numToString(account.refStudentId);
    }

    return numToString(account.id) + ',' + account.username + ',' + account.password + ',' + account.role + ',' + ref + '\n';
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
