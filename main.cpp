/*
                                WELCOME TO INTEC STUDENT DATA MANAGEMENT SYSTEM!

We (Irfan, Iyas & Khilfi) proudly present our project source code to you.

All in all, the source code is separated into three main parts from top to bottom. The sections are listed below:
1. Headers and Initializations
2. Main Program
3. Prototypes and Function Declarations

Each function and global variable have been documented to provide clarification of their existence. You can view each
function purpose on top of its function header to know its purpose and return value.

Lastly, we hope this source code serve as a prime example of what a structured and readable code should be. Please
contact us if you have further inquiries or bug reports on this project.

Thanks ^_^
*/


/*============================================== SECTION 1: HEADERS AND INITIALIZATIONS ==============================================*/

#include <iostream> // For user input and output
#include <fstream> // For file operations
#include <algorithm> // For string processing
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

// Store the current user's username
string globalUsername;


/*===================================================== SECTION 2: MAIN PROGRAM =====================================================*/

void authUI();
void mainUI();

int main()
{
    cout << "___________________________________\n"
         << "| WELCOME TO INTEC STUDENT RECORD |\n"
         << "-----------------------------------\n";

    // Authorize the user by signing up or logging in
    authUI();

    // User has logged in successfully
    // Go to the main menu
    mainUI();

    return 0;
}


/*========================================= SECTION 3: PROTOTYPES AND FUNCTION DECLARATIONS =========================================*/


/*++++++++++++ SECTION 3A: PROTOTYPES ++++++++++++*/

// Prototypes for sign up and login functionality
void signUp(),
     login();

// Prototypes for file operation functionality
void readStudents(),
     writeStudents();

// Prototypes for student data management functionality
void viewStudents(),
     addStudent(),
     editStudent(),
     deleteStudent(),
     searchStudents();

// Prototypes for utility functionality
int findStudent(int),
    lenStudents();
void pressEnterToContinue(string = "Press Enter to continue... ");


/*++++++ SECTION 3A: FUNCTION DECLARATIONS ++++++*/

/**
 * Authorization user interface
*/
void authUI()
{
    char choice;
    
    do
    {
        cout << "\nDo you have an existing account? [Y/n]: ";
        cin >> choice;
        choice = tolower(choice);

        if (choice == 'y')
        {
            login();
            break;
        }
        else if (choice == 'n')
        {
            signUp();
            break;
        }
        else
            cout << "Hint: Please enter 'y' for yes or 'n' for no.\n";
    }
    while(true);

    return;
}

/**
 * Main program interface
*/
void mainUI()
{
    readStudents();
    while (true)
    {
        // Clear the terminal on each loop
        system("cls");

        char select;
        cout << "================================\n"
             << " Welcome to main menu " + globalUsername + "!\n"
             << "================================\n"
             << "1.View \n"
             << "2.Search \n"
             << "3.Add \n"
             << "4.Edit \n"
             << "5.Delete \n"
             << "6.Exit \n";

        cout << "Please make your selection: ";
        cin >> select;
        cin.ignore(); // Ignore '\n' character

        switch(select)
        {
            case '1':
                viewStudents();
                break;
            case '2':
                searchStudents();
                break;
            case '3':
                addStudent();
                break;
            case '4':
                editStudent();
                break;
            case '5':
                deleteStudent();
                break;
            case '6':
                cout << "Thank you for using this system ^_^ ! See you later... \n";
                return;
            default:
                cout << "Invalid selection. \n";
        }
    }
}

/**
 * Register new account
*/
void signUp()
{
    // Clear the terminal
    system("cls");

    string username, password, repeatPassword, fullname, program;
    int age, nosub, studentid, year, day, month;

    cout << "________________________\n";
    cout << "| ACCOUNT REGISTRATION |\n";
    cout << "------------------------\n";

    bool validUsername = false;
    // Username input and validation
    do 
    {
        // Begin with assumption that username is valid
        validUsername = true;

        cout << "Username: ";
        cin >> username;

        // Read the username already registered
        ifstream readAccount("accounts.txt");
        string usernameRegistered;
        
        readAccount >> usernameRegistered;
        while (readAccount.good())
        {
            // Checks if username is already taken
            if(username == usernameRegistered)
            {
                // Username is not valid because it already used by other user
                validUsername = false;
                readAccount.close();
                cout << "The username is already taken. Please choose other username.\n";
                break;
            }
            readAccount >> usernameRegistered;
        }
    } while (!validUsername);

    globalUsername = username;

    // Password input and validation
    do
    {
        // Password input
        cout << "Password: ";
        cin >> password;

        system("cls");

        // Repeat the same password
        cout << "Repeat password: ";
        cin >> repeatPassword;

        if (password == repeatPassword)
            break;

        system("cls");
        cout << "The repeated password is not correct. \n";
    }
    while (true);

    // Write this account at the end of the text file
    ofstream writeAccount("accounts.txt", ios::app);

    writeAccount << username << " " << password << endl;
    writeAccount.close();

    return;
}

/**
 * Login account
*/
void login()
{
    // Clear the terminal
    system("cls");

    cout << "_______________\n";
    cout << "|    LOG IN   |\n";
    cout << "---------------\n";

    do
    {
        string usernameIn, passwordIn, username, password;
        cout << "Please enter username: ";
        cin >> usernameIn;

        cout << "Please enter password: ";
        cin >> passwordIn;

        ifstream readAccount("accounts.txt");

        readAccount >> username >> password;
        while (readAccount.good())
        {
            if(usernameIn == username && passwordIn == password)
            {
                globalUsername = username;
                readAccount.close();
                return;
            }
            readAccount >> username >> password;
        }
        readAccount.close();
        cout << "\nFail: Username or password is incorrect.\n\n";
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

    int j = 0;

    // Read next line
    readStudentsData >> studentId >> firstName >> lastName >> age >> icNumber
                     >> programme >> numOfSubjects >> cgpa;
    
    // No student exists in file
    if (studentId <= 0)
        return;

    do
    {
        // Parse the first and last name
        replace(firstName.begin(), firstName.end(), '_', ' ');
        replace(lastName.begin(), lastName.end(), '_', ' ');

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

        // Read next line
        readStudentsData >> studentId >> firstName >> lastName >> age >> icNumber
                         >> programme >> numOfSubjects >> cgpa;
    } while(readStudentsData.good());

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

    // Close the file
    writeStudents.close();
    return;
}

/**
 * Print all student data
*/
void viewStudents()
{
    system("cls");

    cout << lenStudents() << endl;
    cout << "INTEC STUDENTS DATA VIEW" << endl;
    cout << "ID, First Name, Last Name, Age, IC Number, Programme, Number Of Subjects, CGPA" << endl;

    for (int i = 0; i < lenStudents(); i++)
    {
        Student s = Students[i];
        cout << s.id << ", " << s.firstName << ", " << s.lastName << ", "
             << s.age << ", " << s.icNumber << ", " << s.programme << ", "
             << s.numOfSubjects << ", " << s.cgpa << endl;
    }
    
    pressEnterToContinue();
}

/**
 * Search student based on an attribute. Display the student data if found.
*/
void searchStudents()
{
    system("cls");
    char searchKey;

    cout << "Please choose attribute to search for:\n"
         << "1.Student ID\n"
         << "2.Name\n"
         << "3.Programme\n";
    
    cin >> searchKey;
    cin.ignore();

    switch (searchKey)
    {
        case '1':
        {
            int idIn;
            cout << "Student ID to search for: ";
            
            cin >> idIn;
            cin.ignore();

            for (int i = 0; i < lenStudents(); i++)
            {
                if (idIn == Students[i].id)
                {
                    Student s = Students[i];
                    cout << s.id << ", " << s.firstName << ", " << s.lastName << ", "
                        << s.age << ", " << s.icNumber << ", " << s.programme << ", "
                        << s.numOfSubjects << ", " << s.cgpa << endl;
                    break;
                }
            }
            break;
        }
        case '2':
        {
            string nameIn;
    
            cout << "Name to search: ";
            getline(cin, nameIn);

            string fullName;

            for (int i = 0; i < lenStudents(); i++)
            {
                fullName = Students[i].firstName + ' ' + Students[i].lastName;

                // Convert nameIn and fullName to lowercase for better search results
                for (int k = 0; k < fullName.length(); k++)
                {
                    fullName[k] = (char)tolower(fullName[k]);
                }
                for (int j = 0; j < nameIn.length(); j++)
                {
                    nameIn[j] = (char)tolower(nameIn[j]);
                }

                if (fullName.find(nameIn) != fullName.npos)
                {
                    Student s = Students[i];
                    cout << s.id << ", " << s.firstName << ", " << s.lastName << ", "
                        << s.age << ", " << s.icNumber << ", " << s.programme << ", "
                        << s.numOfSubjects << ", " << s.cgpa << endl;
                }
            }
            break;
        }
        case '3':
        {
            string programmeIn;

            cout << "Programme to search: ";
            getline(cin, programmeIn);

            string programme;

            for (int i = 0; i < lenStudents(); i++)
            {
                programme = Students[i].programme;

                // Convert programmeIn and programme to lowercase for better search results
                for (int j = 0; j < programmeIn.length(); j++)
                {
                    programmeIn[j] = (char)tolower(programmeIn[j]);
                }
                for (int k = 0; k < programme.length(); k++)
                {
                    programme[k] = (char)tolower(programme[k]);
                }

                if (programmeIn.find(programme) != programmeIn.npos)
                {
                    Student s = Students[i];
                    cout << s.id << ", " << s.firstName << ", " << s.lastName << ", "
                         << s.age << ", " << s.icNumber << ", " << s.programme << ", "
                         << s.numOfSubjects << ", " << s.cgpa << endl;
                }
            }
            break;
        }
        default:
            cout << "Invalid option. Search operation aborted.\n";
            return;
    }

    pressEnterToContinue();
}

/**
 * Create a new student
*/
void addStudent()
{
    string firstName, lastName, icNumber, programme;
    int age, numOfSubjects;
    double cgpa;

    // Get the position of empty index in the array
    int empty = lenStudents();

    // Array is fully used
    if (empty == MAX_SIZE)
    {
        cout << "Maximum size of " << MAX_SIZE << " students is reached.";
        return;
    }

    cout << "Add new Student" << endl;
    cout << "First Name: ";
    getline(cin, firstName);

    cout << "Last Name: ";
    getline(cin, lastName);

    cout << "Age: ";
    cin >> age;

    cout << "IC Number: ";
    cin >> icNumber;

    cout << "Programme: ";
    cin >> programme;

    cout << "Number of Subjects: ";
    cin >> numOfSubjects;

    cout << "CGPA: ";
    cin >> cgpa;
    cin.ignore();

    // Get new id
    int studentId = 0;

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

    // Assign to empty location in `Accounts` array
    Students[empty] = newStudent;

    writeStudents();

    cout << "Student is successfully added. Student ID: " << studentId << "\n";
    pressEnterToContinue("\n[Go to Main Menu] ");

    return;
}

/**
 * Update the student data to the new one if provided.
*/
void editStudent()
{
    system("cls");

    string firstName, lastName, icNumber, programme;
    int studentId, age, numOfSubjects, pos;
    double cgpa;

    cout << "Edit a Student" << endl;

    do
    {
        cout << "Enter the student ID: ";
        cin >> studentId;
        cin.ignore();

        // Find position of this student in array
        pos = findStudent(studentId);

        if (pos != -1)
        {
            system("cls");
            cout << "Student with id of " << Students[pos].id << " found.\n";
            break;
        }
        cout << "Student with id of " << studentId << " does not exist.\n";

    } while (true);

    while (true)
    {
        char editOption;

        cout << "Choose your action to edit the data\n";
        cout << "1.First Name\n"
             << "2.Last Name\n"
             << "3.Age\n"
             << "4.IC Number\n"
             << "5.Programme\n"
             << "6.Number of Subjects\n"
             << "7.CGPA\n"
             << "8.Go to Main Menu\n";

        cin >> editOption;
        cin.ignore();

        switch (editOption)
        {
            case '1':
            {
                cout << "Current First Name: " << Students[pos].firstName << "\n";
                cout << "New First Name: ";
                getline(cin, firstName);
                Students[pos].firstName = firstName;
                break;
            }
            case '2':
            {
                cout << "Current Last Name: " << Students[pos].lastName << "\n" << "\n";
                cout << "New Last Name: ";
                getline(cin, lastName);
                Students[pos].lastName = lastName;
                break;
            }
            case '3':
            {
                cout << "Current Age: " << Students[pos].age << "\n"; 
                cout << "New Age: ";
                cin >> age;
                cin.ignore();
                Students[pos].age = age;
                break;
            }
            case '4':
            {
                cout << "Current IC Number: " << Students[pos].icNumber << "\n";
                cout << "New IC Number: ";
                getline(cin, icNumber);
                Students[pos].icNumber = icNumber;
                break;
            }
            case '5':
            {
                cout << "Current Programme: " << Students[pos].programme << "\n";
                cout << "New Programme: ";
                getline(cin, programme);
                Students[pos].programme = programme;
                break;
            }
            case '6':
            {
                cout << "Current Number of Subjects: " << Students[pos].numOfSubjects << "\n";
                cout << "New Number of Subjects: ";
                cin >> numOfSubjects;
                cin.ignore();
                Students[pos].numOfSubjects = numOfSubjects;
                break;
            }
            case '7':
            {
                cout << "Current CGPA: " << Students[pos].cgpa << "\n";
                cout << "New CGPA: ";
                cin >> cgpa;
                cin.ignore();
                Students[pos].cgpa = cgpa;
                break;
            }
            case '8':
            {
                return;
            }
            default:
                cout << "Please enter a number between 1 and 8.\n";
                continue;
        }
        cout << "Data has been updated successfully.\n";
        pressEnterToContinue();
        system("cls");
    }

    writeStudents();
    
    return;
}

/**
 * Delete a student
*/
void deleteStudent()
{
    system("cls");

    int studentId, studentIndex;

    cout << "Edit a Student" << endl;

    do
    {
        cout << "Enter the student ID: ";
        cin >> studentId;
        cin.ignore();

        // Find position of this student in array
        studentIndex = findStudent(studentId);

        if (studentIndex != -1)
        {
            cout << "Student with id of " << Students[studentIndex].id << " found.\n";
            break;
        }
        cout << "Student with id of " << studentId << " does not exist.\n";

    } while (true);

    char assure;
    do
    {
        cout << "Are you sure you want to perform this action? It can't be reversed. [Y/n]: ";
        cin >> assure;
        assure = tolower(assure);

        if (assure == 'y')
        {
            break;
        }
        else if (assure == 'n')
        {
            return;
        }
        else
            cout << "Hint: Please enter 'y' for yes or 'n' for no.\n";
    } while (true);

    int initLen = lenStudents();
    Student reset;

    // Reset the data at index
    Students[studentIndex] = reset;

    // Move other elements forward to fill empty spaces
    for (int i = studentIndex; i < initLen - 1; i++)
    {
        // Swap the position of element in the array
        swap(Students[i], Students[i+1]);
    }

    writeStudents();

    return;
}

/**
 * Get the number of elements in the Students array
*/
int lenStudents()
{
    // Search for unused position in array (i.e. id which value is -1)
    for (int i = 0; i < MAX_SIZE; i++)
    {
        if (Students[i].id <= 0)
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

/**
 * Prompt the user to press Enter to continue the program
*/
void pressEnterToContinue(string message)
{
    string _;
    cout << message;
    getline(cin, _, '\n');
    return;
}
