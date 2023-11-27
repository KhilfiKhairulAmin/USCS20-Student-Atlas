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
void pressEnterToContinue(string = "Press Enter to continue... "),
     inputStringData(string&, string, int),
     // For data validation purpose
     inputIntData(int&, string),
     inputProgramme(string&, string),
     inputCgpa(double&, string);


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
        cin.ignore();
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
                system("cls");
                cout << "Logging out " << globalUsername << "...\n\nBYE ^_^ !\n";
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

    // Header display
    cout << "________________________\n";
    cout << "| ACCOUNT REGISTRATION |\n";
    cout << "------------------------\n";

    bool validUsername = false;
    // Username input and validation
    do 
    {
        // Begin with assumption that username is valid
        validUsername = true;

        // Input username
        inputStringData(username, "Username: ", 1);

        // Read the username already registered
        ifstream readAccount("accounts.txt");
        string usernameRegistered;
        
        // Validate whether the username has been taken or not
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
        inputStringData(password, "Password: ", 1);

        system("cls");

        // Repeat the same password
        inputStringData(repeatPassword, "Repeat password: ", 1);

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

    // Header display
    cout << "_______________\n";
    cout << "|    LOG IN   |\n";
    cout << "---------------\n";

    do
    {
        string usernameIn, passwordIn, username, password;

        // Input username
        inputStringData(usernameIn, "Please enter username: ", 1);

        // Input password
        inputStringData(passwordIn, "Please enter password: ", 1);

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
            
            // Input ID to be searched
            inputIntData(idIn, "Student ID to search for: ");

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
    
            inputStringData(nameIn, "Name to search: ", 2);

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

            inputProgramme(programmeIn, "Programme to search: ");

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
    system("cls");
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

    cout << "Add new Student\n";

    // Input first name
    inputStringData(firstName, "First Name: ", 2);
    // Input last name
    inputStringData(lastName, "Last Name: ", 2);
    // Input age
    inputIntData(age, "Age: ");
    // Input IC number
    inputStringData(icNumber, "IC Number: ", 1);
    // Input programme
    inputProgramme(programme, "Choose Programme: ");
    // Input number of subjects
    inputIntData(numOfSubjects, "Number of Subjects: ");
    // Input CGPA
    inputCgpa(cgpa, "CGPA: ");

    // Generate a new Student ID based on highest Student ID + 1
    int studentId = Students[lenStudents() - 1].id + 1;

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

    cout << "Student is successfully added. Student ID assigned: " << studentId << "\n";
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
        // Input student id
        inputIntData(studentId, "Enter the student ID: ");

        // Find position of this student in array
        pos = findStudent(studentId);

        if (pos == -1)
        {
            cout << "Student with id of " << studentId << " does not exist.\n";
            continue;
        }
        system("cls");
        cout << "Student with id of " << Students[pos].id << " found.\n";
        break;

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
                inputStringData(firstName, "New First Name: ", 2);
                Students[pos].firstName = firstName;
                break;
            }
            case '2':
            {
                cout << "Current Last Name: " << Students[pos].lastName << "\n" << "\n";
                inputStringData(lastName, "New Last Name: ", 2);
                Students[pos].lastName = lastName;
                break;
            }
            case '3':
            {
                cout << "Current Age: " << Students[pos].age << "\n"; 
                inputIntData(age, "New Age: ");
                Students[pos].age = age;
                break;
            }
            case '4':
            {
                cout << "Current IC Number: " << Students[pos].icNumber << "\n";
                inputStringData(icNumber, "New IC Number: ", 1);
                Students[pos].icNumber = icNumber;
                break;
            }
            case '5':
            {
                cout << "Current Programme: " << Students[pos].programme << "\n";
                inputProgramme(programme, "New Programme: ");
                Students[pos].programme = programme;
                break;
            }
            case '6':
            {
                cout << "Current Number of Subjects: " << Students[pos].numOfSubjects << "\n";
                inputIntData(numOfSubjects, "New Number of Subjects: ");
                Students[pos].numOfSubjects = numOfSubjects;
                break;
            }
            case '7':
            {
                cout << "Current CGPA: " << Students[pos].cgpa << "\n";
                inputCgpa(cgpa, "New CGPA: ");
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
        // Input student Id
        inputIntData(studentId, "Enter the student ID: ");

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

/**
 * Get and validate string input by the user. If mode = 1, use cin (get only first word). If mode = 2, use getline (get whole input).
*/
void inputStringData(string& stringIn, string prompt, int mode)
{
    // Reset to default if invalid mode is provided
    if (mode < 1 || mode > 2)
    {
        mode = 2;
    }

    switch (mode)
    {
        // Case 1: Single word input only
        case 1:
        {
            do
            {
                cout << prompt;
                getline(cin, stringIn, '\n');

                // Validate single word input
                if (stringIn == "")
                {
                    cout << "Data can't be empty.\n";
                    continue;
                }
                else if (stringIn.find(" ") != stringIn.npos)
                {
                    cout << "Data can't contain spaces.\n";
                    continue;
                }

                break;
            } while(true);
            break;
        }
        // Case 2: Multiple words input
        case 2:
        {
            do
            {
                cout << prompt;
                getline(cin, stringIn);
                
                // Validate multiword input
                if (stringIn == "")
                {
                    cout << "Data can't be empty.\n";
                    continue;
                }

                break;

            } while(true);
            break;
        }
    }

    return;
}

/**
 * Get and validate integer data
*/
void inputIntData(int& numIn, string prompt)
{
    do
    {
        cout << prompt;
        cin >> numIn;
        cin.ignore();

        if (numIn <= 0)
        {
            cout << "Number must be more than 0.\n";
            continue;
        }

        break;

    } while (true);
    
    return;
}

/**
 * Get and validate Programme data
*/
void inputProgramme(string& programmeIn, string prompt)
{
    cout << "\nProgramme List\n"
         << "1.ACCA\n"
         << "2.ADTP\n"
         << "3.ALG\n"
         << "4.ALUK\n"
         << "5.CFAB\n"
         << "6.DIPLOMA\n"
         << "7.FIA\n"
         << "8.FRANCE\n"
         << "9.ICAEW\n"
         << "10.KTJ\n"
         << "11.KOREA\n"
         << "12.SACE\n";
    do
    {
        char choose;
        cout << prompt;
        cin >> choose;
        cin.ignore();

        switch(choose)
        {
            case '1':
                programmeIn = "ACCA";
                break;
            case '2':
                programmeIn = "ADTP";
                break;
            case '3':
                programmeIn = "ALG";
                break;
            case '4':
                programmeIn = "ALUK";
                break;
            case '5':
                programmeIn = "CFAB";
                break;
            case '6':
                programmeIn = "DIPLOMA";
                break;
            case '7':
                programmeIn = "FIA";
                break;
            case '8':
                programmeIn = "FRANCE";
                break;
            case '9':
                programmeIn = "ICAEW";
                break;
            case '10':
                programmeIn = "KTJ";
                break;
            case '11':
                programmeIn = "KOREA";
                break;
            case '12':
                programmeIn = "SACE";
                break;
            default:
                cout << "Hint: Please enter number between 1 - 12.\n";
                continue;
        }
        break;
    } while (true);
    
    return;
}

/**
 * Get and validate CGPA data
*/
void inputCgpa(double& cgpaIn, string prompt)
{
    do
    {
        cout << prompt;
        cin >> cgpaIn;
        cin.ignore();

        if (cgpaIn < 0 || cgpaIn > 4)
        {
            cout << "Please provide CGPA value between 0.00 - 4.00.\n";
            continue;
        }

        break;

    } while (true);
    
    return;
}
