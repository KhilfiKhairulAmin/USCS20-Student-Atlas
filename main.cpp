#include <iostream> // For user input and output
#include <fstream> // For file operations
#include <cmath> // For complicated mathematical operations
#include <algorithm> // for string processing
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
        refStudentId = refStudentId_;
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
    double cgpa;

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

// Global variable storing the latest Error message
string ErrMsg = "";


// MAIN FUNCTION PROTOTYPES (USED BY main() FUNCTION)

void load();
void signUp();
void login();
int createAccount(string, string, string);
int updateAccount(int, string, string);
void printAccounts();
int createStudent(int, string, string, int, string, string, int, float);
int updateStudent(int, string, string, int, string, string, int, float);
void printStudents();
bool deleteAccountAndStudent(int);
void save();


// THIS IS WHERE THE PROGRAM STARTS EXECUTING
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


// UTILITY FUNCTION PROTOTYPES (USED BY FUNCTIONS OTHER THAN main())

string parseName(string);
string unparseName(string);
template<class T> int generateId(T [MAX_SIZE]);
template<class T> int getEmptyPosition(T [MAX_SIZE]);
template<class T> int findId(T [MAX_SIZE], int);
template<class T> bool deleteAtIndex(T [MAX_SIZE], int);
template<class T> int len(T [MAX_SIZE]);


// PROGRAM & UTILITY FUNCTIONS DEFINITION

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

/**
 * Retrieve all accounts and students data from text file into the global array
*/
void load()
{
    // Open the text file
    ifstream readAccountsData("accounts.txt");

    // Variables to store Account data
    int accountId, refStudentId;
    string username, password, role;

    // Read the data on first line
    readAccountsData >> accountId >> username >> password >> role >> refStudentId;

    int i = 0;
    // Read each data row by row
    do
    {
        // Assign each data into an Account and store in the global array
        Accounts[i++] = Account(
            accountId,
            username,
            password,
            role,
            refStudentId
        );

        // Read the next row
        readAccountsData >> accountId >> username >> password >> role >> refStudentId;
    } while (readAccountsData.good());
    
    // Close the text file
    readAccountsData.close();

    // Open student text file
    ifstream readStudentsData("students.txt");

    // Variables to store Student data
    int studentId, age, numOfSubjects;
    double cgpa;
    string firstName, lastName, icNumber, programme;

    // Read data on the first row
    readStudentsData >> studentId >> firstName >> lastName >> age >> icNumber
                     >> programme >> numOfSubjects >> cgpa;

    int j = 0;
    // Read data row by row
    do
    {
        // Assign each `Student` into the global array
        Students[j++] = Student(
            studentId,
            parseName(firstName),
            parseName(lastName),
            age,
            icNumber,
            programme,
            numOfSubjects,
            cgpa
        );

        // Read next row
        readStudentsData >> studentId >> firstName >> lastName >> age >> icNumber
                         >> programme >> numOfSubjects >> cgpa;
    } while (readStudentsData.good());

    // Close the file
    readStudentsData.close();

    return;
}

// Create a new `Account`
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

// Display all `Account` data. Use for debugging purpose.
void printAccounts()
{
    cout << "Id,Username,Password,Role,RefStudentId" << endl;

    for (int i = 0; i < len(Accounts); i++)
    {
        Account a = Accounts[i];
        cout << a.id << ',' << a.username << ',' << a.password << ',' << a.role << ',' << a.refStudentId << endl;
    }

    return;
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
        // ErrMsg = "Account with id of " + numToString(accountId) + " does not exist.";
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
bool deleteAccountAndStudent(int accountId)
{
    int accountIndex = findId(Accounts, accountId);

    if (accountIndex == -1)
    {
        // ErrMsg = "Account with id of " + numToString(accountId) + " does not exist.";
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
 * Create a new `Student`. Return the `id` of student.
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
    cout << "Id,First_Name,Last_Name,Age,IcNumber,Programme,NumOfSubj,Cgpa" << endl;
    for (int i = 0; i < len(Students); i++)
    {
        Student s = Students[i];
        cout << s.id << ',' << s.firstName << ',' << s.lastName << ',' << s.age << ','
             << s.icNumber << ',' << s.programme << ',' << s.numOfSubjects << ',' << s.cgpa << endl;
    }

    return;
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
        // ErrMsg = "Student with id of " + numToString(studentId) + " does not exist.";
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

/**
 * Save all accounts and students into text file
*/
void save()
{
    ofstream writeAccounts("accounts.txt");

    for (int i = 0; i < len(Accounts); i++)
    {
        Account a = Accounts[i];
        writeAccounts << a.id << ' ' << a.username << ' ' << a.password << ' ' << a.role << ' ' << a.refStudentId << endl;
    }

    writeAccounts.close();

    ofstream writeStudents("students.txt");

    for (int i = 0; i < len(Students); i++)
    {
        Student s = Students[i];
        writeStudents << s.id << ' ' << unparseName(s.firstName) << ' ' << unparseName(s.lastName) << ' '
                      << s.age << ' ' << s.icNumber << ' ' << s.programme << ' '
                      << s.numOfSubjects << ' ' << s.cgpa << endl;
    }

    writeStudents.close();

    return;
}


// ALL UTILITY FUNCTIONS
string parseName(string name)
{
    replace(name.begin(), name.end(), '_', ' ');
    return name;
}

string unparseName(string name)
{
    replace(name.begin(), name.end(), ' ', '_');
    return name;
}

/**
 * Generate a unique ID for new `Account` or new `Student`
*/
template<class T> int generateId(T array[MAX_SIZE])
{
    int maxId = array[0].id;
    // Search for highest id in the array
    for (int i = 0; i < len(array); i++)
    {
        if (array[i].id > maxId)
            maxId = array[i].id;
    }


    // Return the next highest id
    maxId++;
    return maxId;
}

/**
 * Get the number of elements in the array
*/
template<class T> int len(T array[MAX_SIZE])
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
 * Find index of `targetId`. Return `-1` if not found.
*/
template<class T> int findId(T array[MAX_SIZE], int targetId)
{
    // Search for index of target id
    for (int i = 0; i < len(array); i++)
    {
        if (array[i].id == targetId)
            return i;
    }
    return -1;
}

/**
 * Find an index in the array which is empty. Return `-1` if array is full.
*/
template<class T> int getEmptyPosition(T array[MAX_SIZE])
{
    int length = len(array);
    if (length == MAX_SIZE)
        return -1;
    return length;
}

/**
 * Delete an element at specified `index` and move other elements forward to fill empty space. Return `false` if an error occurred, else `true`.
*/
template<class T> bool deleteAtIndex(T array[MAX_SIZE], int index)
{
    // Invalid index
    if (index >= MAX_SIZE || index < 0)
    {
        // ErrMsg = "Index at position " + numToString(index) + " is invalid.";
        return false;
    }

    // Reset element at `index`
    array[index] = T();

    // Move other elements forward to fill empty spaces
    for (int i = index; i < len(array) - 1; i++)
    {
        array[i] = array[i+1];
    }
    return true;
}
