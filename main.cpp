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

Github: https://github.com/KhilfiKhairulAmin/uscs20-project
*/


/*============================================== SECTION 1: HEADERS AND INITIALIZATIONS ==============================================*/

#include <iostream> // For user input and output
#include <fstream> // For file operations
#include <algorithm> // For string processing
#include <iomanip> // For data manipulation
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
    system("Color 70");
    cout << "+======================================================================================================================+\n"
         << "+                                     WELCOME TO INTEC STUDENT DATA ATLAS!                                             +\n"
         << "+======================================================================================================================+\n";

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
void printStudent(Student),
     printStudentTable(Student[MAX_SIZE]),
     pressEnterToContinue(string = "Press Enter to continue... "),
     // For data validation purpose
     inputStringData(string&, string, int, int = 1, int = 22),
     inputChoice(char&, string),
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
    // Input choice ('y' or 'n')
    inputChoice(choice, "\nDo you have an existing account? [Y/n]: ");
    
    if (choice == 'y')
        login();
    else if (choice == 'n')
        signUp();

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
        cout << "+======================================================================================================================+\n"
             << "+                                                    MAIN MENU                                                         +\n"
             << "+======================================================================================================================+\n"
             << "Welcome " << globalUsername << "!\n\n"
             << "What action do you want to perform?\n"
             << "1.View \n"
             << "2.Search \n"
             << "3.Add \n"
             << "4.Edit \n"
             << "5.Delete \n"
             << "6.Exit \n";

        cout << "\nPlease make your selection [1-6]: ";
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
                cout << "+======================================================================================================================+\n"
                     << "+                                               HAVE A GREAT DAY!                                                      +\n"
                     << "+======================================================================================================================+\n";
                cout << "\nLogging out " << globalUsername << "...\n"
                     << "\nKACHING~DONE!\n"
                     << "\nCheck out our project on GitHub: https://github.com/KhilfiKhairulAmin/uscs20-project\n";
                return;
            default:
                cout << "Invalid selection.\n";
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

    cout << "+======================================================================================================================+\n";
    cout << "+                                             ACCOUNT REGISTRATION                                                     +\n";
    cout << "+======================================================================================================================+\n";

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
        string usernameRegistered, _;
        
        // Validate whether the username has been taken or not
        readAccount >> usernameRegistered >> _;
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
        inputStringData(password, "Password: ", 1, 8);

        system("cls");
        cout << "+======================================================================================================================+\n";
        cout << "+                                             ACCOUNT REGISTRATION                                                     +\n";
        cout << "+======================================================================================================================+\n";

        // Repeat the same password
        inputStringData(repeatPassword, "Repeat password: ", 1);

        if (password == repeatPassword)
            break;

        system("cls");
        cout << "+======================================================================================================================+\n";
        cout << "+                                             ACCOUNT REGISTRATION                                                     +\n";
        cout << "+======================================================================================================================+\n";

        cout << "The repeat password was not correct. Please re-enter password. \n\n";

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
    cout << "+======================================================================================================================+\n";
    cout << "+                                                    ACCOUNT LOG IN                                                    +\n";
    cout << "+======================================================================================================================+\n";

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

    while (readStudentsData.good())
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
    }

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
    cout << "+======================================================================================================================+\n"
         << "+                                             INTEC STUDENT DATA ATLAS                                                 +\n"
         << "+======================================================================================================================+\n"
         << "\nNumber of Student Records: " << lenStudents() << "/" << MAX_SIZE << "\n\n";
    printStudentTable(Students);
    pressEnterToContinue("\n[Back to Main Menu]");
}

/**
 * Search student based on an attribute. Display the student data if found.
*/
void searchStudents()
{
    system("cls");
    char searchKey;
    Student found[MAX_SIZE];
    int count = 0;

    cout << "+======================================================================================================================+\n"
         << "+                                                    SEARCH STUDENT DATA                                               +\n"
         << "+======================================================================================================================+\n";

    cout << "Please choose attribute to search for:\n"
         << "1.Student ID\n"
         << "2.Name\n"
         << "3.Programme\n"
		 << "\nEnter your choice [1-3]: ";
    
    cin >> searchKey;
    cin.ignore();
    cout << endl;

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
                    found[count++] = Students[i];
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
                    found[count++] = Students[i];
                }
            }
            break;
        }
        case '3':
        {
            string programmeIn;

            inputProgramme(programmeIn, "Programme to search [1-12]: ");

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
                    found[count++] = Students[i];
                }
            }
            break;
        }
        default:
            cout << "Invalid option. Search operation cancelled.\n";
            pressEnterToContinue("\n[Exit]");
            return;
    }

    if (count == 0)
    {
        cout << "\nNo student found.\n";
    }
    else
    {
        cout << "\nFound: " << count << " record(s)\n";
        printStudentTable(found);
    }
    pressEnterToContinue("\n[Back to Main Menu]");
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
        cout << "Can't add Student. Maximum size of " << MAX_SIZE << " students reached.\n";
        return;
    }

        cout << "+======================================================================================================================+\n"
             << "+                                                    ADD NEW STUDENT                                                   +\n"
             << "+======================================================================================================================+\n";

    // Input first name
    inputStringData(firstName, "First Name: ", 2);
    // Input last name
    inputStringData(lastName, "Last Name: ", 2);
    // Input age
    inputIntData(age, "Age: ");
    // Input IC number
    inputStringData(icNumber, "IC Number: ", 1, 12, 12);
    // Input programme
    inputProgramme(programme, "Choose Programme [1-12]: ");
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

    cout << "\n+======================================================================================================================+\n";
    printStudent(Students[empty]);
    cout << "+======================================================================================================================+";

    cout << "\n\nStudent is successfully added.\n";
    pressEnterToContinue("\n[OK]");
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

    cout << "+======================================================================================================================+\n"
         << "+                                                EDIT STUDENT DATA                                                     +\n"
         << "+======================================================================================================================+\n";

    do
    {
        // Input student id
        inputIntData(studentId, "\nEnter the student ID: ");

        // Find position of this student in array
        pos = findStudent(studentId);

        if (pos == -1)
        {
            cout << "Student with id of " << studentId << " does not exist.\n";
            continue;
        }
        system("cls");
        break;

    } while (true);

    while (true)
    {
        char editOption;

        cout << "+======================================================================================================================+\n"
             << "+                                                EDIT STUDENT DATA                                                     +\n"
             << "+======================================================================================================================+\n\n";

        printStudent(Students[pos]);
        cout << "\n\nChoose your action to edit the Student data:\n";
        cout << "1.First Name\n"
             << "2.Last Name\n"
             << "3.Age\n"
             << "4.IC Number\n"
             << "5.Programme\n"
             << "6.Number of Subjects\n"
             << "7.CGPA\n"
             << "8.[Exit]\n"
			 << "\nEnter your choice [1-8]: ";

        cin >> editOption;
        cin.ignore();
        cout << "\n";

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
                inputStringData(icNumber, "New IC Number: ", 1, 12, 12);
                Students[pos].icNumber = icNumber;
                break;
            }
            case '5':
            {
                cout << "Current Programme: " << Students[pos].programme << "\n";
                inputProgramme(programme, "New Programme [1-12]: ");
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
        writeStudents();
        cout << "\nStudent data updated successfully.\n";
        pressEnterToContinue("\n[OK]");
        system("cls");
    }
}

/**
 * Delete a student
*/
void deleteStudent()
{
    system("cls");

    int studentId, studentIndex;

    cout << "+======================================================================================================================+\n"
         << "+                                              DELETE STUDENT DATA                                                     +\n"
         << "+======================================================================================================================+\n";

    do
    {
        // Input student Id
        inputIntData(studentId, "\nEnter the student ID: ");

        // Find position of this student in array
        studentIndex = findStudent(studentId);

        if (studentIndex != -1)
        {
            cout << "Student with id of " << Students[studentIndex].id << " found.\n";
            break;
        }
        cout << "Student with id of " << studentId << " does not exist.\n";

    } while (true);

    cout << endl;
    printStudent(Students[studentIndex]);

    char assure;
    inputChoice(assure, "\nAre you sure? [Y/n]: ");
    
    if (assure == 'n')
        return;
    
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

    cout << "\nStudent has been deleted successfully.\n";
    pressEnterToContinue("\n[OK]");
}

/**
 * Display information of a Student
*/
void printStudent(Student s)
{
    cout << "Student Information"
         << "\n|- Student ID: " << s.id
         << "\n|- First Name: " << s.firstName
         << "\n|-  Last Name: " << s.lastName 
         << "\n|-        Age: " << s.age 
         << "\n|-  IC Number: " << s.icNumber
         << "\n|-  Programme: " << s.programme 
         << "\n|-   Subjects: " << s.numOfSubjects 
         << "\n|-       CGPA: " << s.cgpa
         << "\n";
}

/**
 * Display Student data in table
*/
void printStudentTable(Student students[MAX_SIZE])
{
    cout <<"+======================================================================================================================+\n";
    cout <<setw(10)<<setiosflags(ios::left)<<"|ID"<<"|"
		 <<setw(23)<<setiosflags(ios::left) <<"       First Name"<<"|"
		 <<setw(22)<<setiosflags(ios::left)<<"       Last Name"<<"|"
		 <<setw(10)<<setiosflags(ios::left)<<"   Age"<<"|"
		 <<setw(14)<<setiosflags(ios::left)<<"  IC Number"<<"|"
		 <<setw(8)<<setiosflags(ios::left)<<"Programme"<<"|"
		 <<setw(19)<<setiosflags(ios::left)<<"Number Of Subjects"<<"|"
		 <<setw(5)<<setiosflags(ios::left)<<"CGPA"<<"|" << endl;

    int i = 0;
    while (students[i].id > 0)
    {
        Student s = students[i++];
    	cout <<"+======================================================================================================================+\n|";
        cout <<setw(9)<<setiosflags(ios::left)<< s.id << "|" 
			 <<setw(23)<<setiosflags(ios::left)<< s.firstName << "|" 
			 <<setw(22)<<setiosflags(ios::left)<< s.lastName << "|"
             <<setw(10)<<setiosflags(ios::left)<<s.age << "|" 
			 <<setw(14)<<setiosflags(ios::left)<< s.icNumber << "|" 
			 <<setw(9)<<setiosflags(ios::left)<< s.programme << "|"
             <<setw(19)<<setiosflags(ios::left)<< s.numOfSubjects << "|" 
			 <<setw(5)<<setiosflags(ios::left)<<fixed<<setprecision(2)<< s.cgpa <<"|"<< endl;
    }
    cout << "+======================================================================================================================+\n";
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
}

/**
 * Get and validate choice ('y' or 'n')
*/
void inputChoice(char& choiceIn, string prompt)
{
    do
    {
        cout << prompt;
        cin >> choiceIn;
        choiceIn = tolower(choiceIn);
        cin.ignore();

        if (choiceIn != 'n' && choiceIn != 'y')
        {
            cout << "Hint: Please enter 'y' for yes or 'n' for no.\n";
            continue;
        }
        break;
    }
    while(true);
}

/**
 * Get and validate string input by the user. If mode = 1, get only first word. If mode = 2, get whole input.
*/
void inputStringData(string& stringIn, string prompt, int mode, int minSize, int maxSize)
{
    do
    {
        // Mode 1: Singular word input
        // Mode 2: Multiple word Input
        cout << prompt;
        getline(cin, stringIn, '\n');

        // Validate empty
        if (stringIn == "")
        {
            cout << "Data can't be empty.\n";
            continue;
        }
        else if (stringIn.length() > maxSize || stringIn.length() < minSize)
        {
            cout << "Please enter data between " << minSize << " and " << maxSize << " characters.\n";
            continue;
        }

        if (mode == 1)
        {
            if (stringIn.find(" ") != stringIn.npos)
            {
                cout << "Data can't contain spaces.\n";
                continue;
            }
        }

        break;
    } while (true);
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
}

/**
 * Get and validate Programme data
*/
void inputProgramme(string& programmeIn, string prompt)
{
    cout << "Programme Number\n"
         << " 1. ACCA\n"
         << " 2. ADTP\n"
         << " 3. ALG\n"
         << " 4. ALUK\n"
         << " 5. CFAB\n"
         << " 6. DIPLOMA\n"
         << " 7. FIA\n"
         << " 8. FRANCE\n"
         << " 9. ICAEW\n"
         << "10. KTJ\n"
         << "11. KOREA\n"
         << "12. SACE\n";

    do
    {
        string choose;
        inputStringData(choose, prompt, 1, 1, 2);

        if (choose == "1")
            programmeIn = "ACCA";
        else if (choose == "2")
            programmeIn = "ADTP";
        else if (choose == "3")
            programmeIn = "ALG";
        else if (choose == "4")
            programmeIn = "ALUK";
        else if (choose == "5")
            programmeIn = "CFAB";
        else if (choose == "6")
            programmeIn = "DIPLOMA";
        else if (choose == "7")
            programmeIn = "FIA";
        else if (choose == "8")
            programmeIn = "FRANCE";
        else if (choose == "9")
            programmeIn = "ICAEW";
        else if (choose == "10")
            programmeIn = "KTJ";
        else if (choose == "11")
            programmeIn = "KOREA";
        else if (choose == "12")
            programmeIn = "SACE";
        else
        {
            cout << "Hint: Please enter number between 1 - 12.\n";
            continue;
        }
        break;
    } while (true);
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
}
