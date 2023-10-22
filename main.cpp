#include <iostream>
#include <vector>
#include <fstream>
using namespace std;

/** TODO
 * 1. CRUD operations for database (txt file)
 *      - Account data
 *      - Student data
 * 2. Parser for txt file
*/

struct Account;
struct Student;


int main ()
{
    cout << "Project Time";

    return 0;
}

/**
 * Account datatype
*/
struct Account
{
    string username;
    string password;
    string authority;
};

/**
 * Student datatype
*/
struct Student
{
    string studentId;
    string icNumber;
    int age;
    string programme;
    int numOfSubjects;
    float cgpa;
};
