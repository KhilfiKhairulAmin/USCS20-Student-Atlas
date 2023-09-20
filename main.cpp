#include <iostream>

using namespace std;

/* Main program */

int main ()
{
    bool auth = false;

    while (1)
    {
        try
        {
            if (!auth)
            {
                authInterface();
            }
            else
            {
                mainInterface();
            }
        }
        catch (Error err)
        {
            cout << err.message;
        }
    }

    return 0;
}

class Error
{
    public:
        string message;

    Error (string message)
    {
        this->message = message;
    }
};

/* Sub program */

void authInterface ()
{
    
}

void mainInterface ()
{
    
}

/**
 * Register a user into the system
 * @param username Account username of the student
 * @param password Account password
 * @param fullName Student first and last name combined
 * @param icNumber Identification card 12 digit number
 * @param age Student age
 * @param program Type of program enrolled in INTEC
 * @param numOfSubjects Count of subjects taken
*/
bool registerUser (string username, string password, string fullName, string icNumber, int age, string program, int numOfSubjects)
{

}

/**
 * Authenticate user. Only return ```true``` if authorized and ```false``` if unauthorized.
 * @param username Account username
 * @param password Account password
 * @return 
*/
bool loginUser (string username, string password)
{

}

// Student
char get ()
{
    return ' ';
}

void edit (string fullName, string icNumber, int age, string program, int numOfSubjects)
{

}

void deleteStudent (string studentId)
{

}

char sort (string sortKey = "id", bool asc = true)
{
    return ' ';
}