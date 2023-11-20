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

// Store Students data
Student Students[MAX_SIZE];


/*===================================================== SECTION 2: MAIN PROGRAM =====================================================*/

void authUI();
void mainUI(int);

int main()
{
    // Authorize the user by signing up or logging in
    authUI();

    // User has logged in successfully
    mainUI(1);

    return 0;
}


/*========================================= SECTION 3: PROTOTYPES AND FUNCTION DECLARATIONS =========================================*/


/*++++++++++++ SECTION 3A: PROTOTYPES ++++++++++++*/

// Prototypes for signUp and login interface
void signUp(),
     login();

// Prototypes for data manipulation functions
void readStudents(),
     writeStudents();
int  addStudent(int, string, string, int, string, string, int, float),
     editStudent(int, string, string, int, string, string, int, float);
bool deleteStudent(int);

// Prototypes for utility functions
int  findStudent(int),
     lenStudents();


/*++++++ SECTION 3A: FUNCTION DECLARATIONS ++++++*/

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

    ofstream writeAccount("accounts.txt", ios::app);

    writeAccount << username << " " << password << endl;

    writeAccount.close();

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
    cout << "_______________\n";
    cout << "|    LOG IN   |\n";
    cout << "---------------\n";

    do
    {
        string usernameIn, passwordIn, username, password;
        cout << "Please enter username: ";
        cin >> usernameIn;

        cout << "\nPlease enter password: ";
        cin >> passwordIn;

        ifstream readAccount("accounts.txt");

        readAccount >> username >> password;
        while (readAccount.good())
        {
            if(usernameIn == username && passwordIn == password)
            {
                readAccount.close();
                cout << "\nLogin successful!";
                return;
            }
            readAccount >> username >> password;
        }
        readAccount.close();
        cout << "\nLogin failed.\n";
        cout << "Please enter username and password again.\n\n";
    }
    while(true);
}

/**
 * Retrieve all student data from text file into the Students array
*/
void readStudents()
{
    // Open student text file
    ifstream readStudentsData("students.txt");

    // Variables to store Student data
    int studentId, age, numOfSubjects;
    double cgpa;
    string firstName, lastName, icNumber, programme;

    // Read data on the first row
    readStudentsData >> studentId >> firstName >> lastName >> age >> icNumber
                     >> programme >> numOfSubjects >> cgpa;

    // Parse first and last name
    replace(firstName.begin(), firstName.end(), '_', ' ');
    replace(lastName.begin(), lastName.end(), '_', ' ');

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

/**
 * Save all student data into text file
*/
void writeStudents()
{
    ofstream writeStudents("students.txt");

    for (int i = 0; i < lenStudents(); i++)
    {
        Student s = Students[i];

        // Unparse first and last name to store inside text file
        replace(s.firstName.begin(), s.firstName.end(), ' ', '_');
        replace(s.lastName.begin(), s.lastName.end(), ' ', '_');

        // Write to text file
        writeStudents << s.id << ' ' << s.firstName << ' ' << s.lastName << ' '
                      << s.age << ' ' << s.icNumber << ' ' << s.programme << ' '
                      << s.numOfSubjects << ' ' << s.cgpa << endl;
    }

    writeStudents.close();

    return;
}

/**
 * Create a new `Student`. Return the `id` of student.
*/
int addStudent(
    int accountId, string firstName, string lastName,
    int age, string icNumber, string programme,
    int numOfSubjects, float cgpa
)
{
    // Get new id
    int studentId = Students[0].id;

    // Search for highest id in the array
    for (int i = 0; i < lenStudents(); i++)
    {
        if (Students[i].id > studentId)
            studentId = Students[i].id;
    }

    // Get the next id
    studentId++;

    Student newStudent;

    newStudent.id = studentId;
    newStudent.firstName = firstName;
    newStudent.lastName = lastName;
    newStudent.age = age;
    newStudent.icNumber = icNumber;
    newStudent.programme = programme;
    newStudent.numOfSubjects = numOfSubjects;
    newStudent.cgpa = cgpa;

    // Get the position of empty index in the array
    int empty = lenStudents();

    // Array is fully used
    if (empty == MAX_SIZE)
    {
        cout << "Maximum size reached. Cannot add new Student.";
        // Return invalid id to represent error occurred
        return -1;
    }

    // Assign to empty location in `Accounts` array
    Students[empty] = newStudent;

    writeStudents();

    return studentId;
}

/**
 * Update `Student` with `id` to the new data. Return `pos` if the account exists, else return `-1`.
*/
int editStudent(
    int studentId, string firstName = "", string lastName = "",
    int age = -1, string icNumber = "", string programme = "",
    int numOfSubjects = -1, float cgpa = -1
)
{
    // Find position of this `Student` in array
    int pos = findStudent(studentId);
    
    if (pos == -1)
    {
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

    writeStudents();

    // Return position of this student in the array
    return pos;
}

/**
 * Delete a Student with `studentId`
*/
bool deleteStudent(int studentId)
{
    int studentIndex = findStudent(studentId);

    if (studentIndex == -1)
    {
        return false;
    }

    int initLen = lenStudents();
    Student reset;

    // Reset the data at index
    Students[studentIndex] = reset;

    // Move other elements forward to fill empty spaces
    for (int i = studentIndex; i < initLen - 1; i++)
    {
        swap(Students[i], Students[i+1]);
    }

    writeStudents();

    return true;
}

/**
 * Get the number of elements in the Students array
*/
int lenStudents()
{
    // Search for unused position in array (i.e. id which value is -1)
    for (int i = 0; i < MAX_SIZE; i++)
    {
        if (Students[i].id == -1)
            return i;
    }
    // Array is fully used
    return MAX_SIZE;
}

/**
 * Find index of `targetId`. Return `-1` if not found.
*/
int findStudent(int targetId)
{
    // Search for index of target id
    for (int i = 0; i < lenStudents(); i++)
    {
        if (Students[i].id == targetId)
            return i;
    }
    return -1;
}
