/*
                                            WELCOME TO INTEC STUDENT DATA MANAGEMENT SYSTEM!

We (Irfan, Iyas & Khilfi) proudly present our project source code to you.

All in all, the source code is separated into three main parts from top to bottom. The sections are listed below:
1. Headers and Initializations
2. Main Program
3. Prototypes and Function Declarations

Each function and global variable have been documented to provide clarification of their existence. You can view each
function purpose on top of its function header to know its return value and meanings.

Lastly, we hope this source code serve as a prime example of what a structured and readable code should be. Lastly,
please contact khilfikhairulamin@gmail.com if you have further inquiries or bug reports on this project.

Thanks ^_^
*/


/*============================================== SECTION 1: HEADERS AND INITIALIZATIONS ==============================================*/

#include <iostream> // For user input and output
#include <fstream> // For file operations
#include <cmath> // For complicated mathematical operations
#include <algorithm> // for string processing
using namespace std;

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
    int age;
    string icNumber;
    string programme;
    int numOfSubjects;
    double cgpa;
};

// Maximum size of array
const int MAX_SIZE = 200;

// Store Accounts data
Account Accounts[MAX_SIZE];

// Store Students data
Student Students[MAX_SIZE];

// Store error message
string ErrMsg = "";

// Prototypes for main user interface
void authUI();
void mainUI(int);


/*===================================================== SECTION 2: MAIN PROGRAM =====================================================*/

int main()
{
    // Authorize the user by signing up or logging in
    authUI();

    // User has logged in successfully
    mainUI(1);

    return 0;
}


/*========================================= SECTION 3: PROTOTYPES AND FUNCTION DECLARATIONS =========================================*/


/*+++++++ SECTION 3A: PROTOTYPES +++++++*/

// Prototypes for signUp and login
void signUp(),
     login();

// Prototypes for data manipulation functions
void load(),
     save();
int  createAccount(string, string, string),
     updateAccount(int, string, string),
     createStudent(int, string, string, int, string, string, int, float),
     updateStudent(int, string, string, int, string, string, int, float);
bool deleteAccountAndStudent(int);

// Prototypes for utility functions
string parseName(string),
       unparseName(string);
template<class T> int generateId(T [MAX_SIZE]);
template<class T> int getEmptyPosition(T [MAX_SIZE]);
template<class T> int findId(T [MAX_SIZE], int);
template<class T> bool deleteAtIndex(T [MAX_SIZE], int);
template<class T> int len(T [MAX_SIZE]);


/*+ SECTION 3A: FUNCTION DECLARATIONS +*/

// Authorization user interface
void authUI()
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

    return;
}

// Main program interface
void mainUI(int x)
{
	int select;
	if(x == 1)
	{
		cout<< "========================="
			<< "\n Welcome to main menu "
			<<"\n========================="
			<<endl
			<<"1.Browse"
			<<"\n2.Edit"
			<<"\n3.Delete"
			<<"\n4.Exit";
			do {
			cout<<"\nPlease make your selection: ";
			cin>>select;
			} while (x > 4 || x < 1);
			
		switch(select)
		{
			case 1:
				
				break;
			case 2:
				
				break;
			case 3:
				
				break;
			case 4:
				break;
			
		}
	}
	else
	{
		
	}
	
	return;
}

// Register new account
void signUp()
{
    string username, password, repeatPassword, fullname, program;
    int age, nosub, studentid, year, day, month;

    cout << "________________________\n";
    cout << "| STUDENT REGISTRATION |\n";
    cout << "------------------------\n";

    cout << "Username: ";
    cin >> username;

    cout << "Password: ";
    cin >> password;

    do
    {
        cout << "Repeat password: ";
        cin >> repeatPassword;

        if (password == repeatPassword)
            break;

        cout << "The repeated password is not correct. Please re-enter." << endl;
    }
    while (1);

    int studentId = createAccount(username, password, "STUDENT");
    save();

    // cout << "Full Name:";
    // getline(cin >> ws, fullname);
    // cout << "Age: ";
    // cin >> age;
    // cout << "Birthdate: \n";
    // cout << "Day(1-30): "; cin >> day; cout << "Month (1 - 12): "; cin >> month; cout << "Year (2xxx): "; cin >> year;

    // return;
}

/**
 * Login account
*/
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
        Account account;
        account.id = accountId;
        account.username = username;
        account.password = password;
        account.role = role;
        account.refStudentId = refStudentId;

        Accounts[i++] = account;

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
        Student student;
        student.id = studentId;
        student.firstName = firstName;
        student.lastName = lastName;
        student.age = age;
        student.icNumber = icNumber;
        student.programme = programme;
        student.numOfSubjects = numOfSubjects;
        student.cgpa = cgpa;

        Students[j++] = student;

        // Read next row
        readStudentsData >> studentId >> firstName >> lastName >> age >> icNumber
                         >> programme >> numOfSubjects >> cgpa;
    } while (readStudentsData.good());

    // Close the file
    readStudentsData.close();

    return;
}

// Create a new `Account`. Return `studentId`.
int createAccount(string username, string password, string role)
{
    // Get new id
    int accountId = generateId(Accounts);

    // Create new account
    Account newAccount;
    newAccount.id = accountId;
    newAccount.username = username;
    newAccount.password = password;
    newAccount.role = role;

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
int updateAccount(int accountId, string username = "", string newPassword = "")
{
    // Find position of this `Account` in array
    int pos = findId(Accounts, accountId);

    // If Account is not found
    if (pos == -1)
    {
        // ErrMsg = "Account with id of " + numToString(accountId) + " does not exist.";
        return -1;
    }

    // Overwrite with new data if provided, else keep the old data
    if (username != "")
        Accounts[pos].username = username;
    if (newPassword != "")
        Accounts[pos].password = newPassword;

    save();

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

    if (account.refStudentId != -1)
    {
        int studentIndex = findId(Students, account.refStudentId);
        deleteAtIndex(Students, studentIndex);
    }

    deleteAtIndex(Accounts, accountIndex);

    save();

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

    Student newStudent;

    newStudent.id = studentId;
    newStudent.firstName = firstName;
    newStudent.lastName = lastName;
    newStudent.age = age;
    newStudent.icNumber = icNumber;
    newStudent.programme = programme;
    newStudent.numOfSubjects = numOfSubjects;
    newStudent.cgpa = cgpa;

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
    int studentId, string firstName = "", string lastName = "",
    int age = -1, string icNumber = "", string programme = "",
    int numOfSubjects = -1, float cgpa = -1
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

    // Only update the data if provided
    if (firstName != "")
        Students[pos].firstName = firstName;
    if (lastName != "")
        Students[pos].lastName = lastName;
    if (age != -1)
        Students[pos].age = age;
    if (icNumber != "")
        Students[pos].icNumber = icNumber;
    if (programme != "")
        Students[pos].programme = programme;
    if (numOfSubjects != -1)
        Students[pos].numOfSubjects = numOfSubjects;
    if (cgpa != -1)
        Students[pos].cgpa = cgpa;

    save();

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

    int initLen = len(array);
    array[index] = T();

    // Move other elements forward to fill empty spaces
    for (int i = index; i < initLen - 1; i++)
    {
        swap(array[i], array[i+1]);
    }

    return true;
}
