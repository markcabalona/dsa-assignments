/*
    MARK REYES CABALONA         MP7 - Rewrite mp5 in cpp
    BSCS - 2A                   Oct. 30, 2021

*/
#include <iostream>
#include "providers/studentList.h"

using namespace std;

//utils
int getInt(string prompt);
float getFloat(string prompt);

//screens
int menu();//displays the options, returns the user's choice
void insertStudent();//insert student screen
void updateStudent();
void deleteStudent();
void display();


StudentList list;

int main(void)
{

    bool running = true;

    while (running)
    {
        switch (menu())
        {
        case 1:
        {
            insertStudent();
            break;
        }
        case 2:
        {
            updateStudent();
            break;
        }
        case 3:
        {
            deleteStudent();
            break;
        }
        case 4:
        {
            display();
            break;
        }
        case 5:
        {
            running = false;
            break;
        }
        default:
            break;
        }
    }
}

int menu()
{
    int optionsCount = 5;
    string options[optionsCount] = {"Insert", "Update", "Delete", "Display", "Exit"};

    system("cls");
    cout << "====================Main Menu====================" << endl
         << endl;
    for (int i = 0; i < optionsCount; i++)
    {
        cout << "   " << i + 1 << ".) " << options[i] << endl;
    }
    int response;
    while ((response = getInt("Enter Option Number: ")) < 0 || response > optionsCount)
    {
        cout << "***Invalid Option Number***" << endl;
    }
    return response;
}

void insertStudent()
{
    if (list.isFull())//isFull returns boolean
    {
        cout << "List is Full\n";
        system("pause");
        return;
    }

    system("cls");
    cout << "====================Insert Student====================" << endl
         << endl;

    cout << "Enter Student's Name: ";
    string name;
    getline(cin, name);//get string with spaces
    if (list.locate(name) >= 0)
    {
        cout << name << "Already has a record." << endl;
        return;
    }
    //if user's name is unique in the list

    //user can enter multiple quiz scores
    int gradeCount = getInt("Enter the number of grades you're going to enter: ");

    //make an array of quiz scores
    float tempGrades[gradeCount];
    for (int i = 0; i < gradeCount; i++)
    {
        cout << "Enter grade #" << i + 1 << ": ";
        tempGrades[i] = getFloat("");//populate array of quiz scores
        cout << endl;
    }
    //create a student object
    Student temp = Student(name);
    temp.setGrades(tempGrades, gradeCount);
    //insert student to the list
    cout << list.insert(temp);
    cout << "Student Added\n\n";
    system("pause");
}

void updateStudent()
{
    system("cls");
    cout << "====================Update Student====================" << endl
         << endl;
    string name;
    cout << "Enter Name: ";
    getline(cin, name);

    //check name if it is in the list
    int index = list.locate(name);//locate returns the index of the student if found, returns NOT_FOUND(defined in StudentList.h) otherwise
    if (index == NOT_FOUND)
    {
        cout << "   " << name << " has no record in our system." << endl;
        system("pause");
        return;
    }

    //display the student's information
    list.students()[index].display();

    //getting new student's record
    int gradeCount = getInt("\nEnter the number of grades you're going to enter: ");
    float tempGrades[gradeCount];
    for (int i = 0; i < gradeCount; i++)
    {
        cout << "Enter grade #" << i + 1 << ": ";
        tempGrades[i] = getInt("");
        cout << endl;
    }

    //update the student's record
    list.students()[index].setGrades(tempGrades, gradeCount);

    cout << "\nRecord Updated" << endl;

    system("pause");
}

void deleteStudent()
{
    system("cls");
    cout << "====================Update Student====================" << endl
         << endl;
    string name;
    cout << "Enter Name: ";
    getline(cin, name);
    
    int result = list.remove(name);
    if(result == NOT_FOUND){
        cout<<"   "<<name<<" has no record in our system."<<endl;
        system("pause");
        return;
    }
    else if(result == EMPTY){
        cout<<"   List is Empty";
        system("pause");
        return;
    }
    cout<<name<<"'s record has been deleted."<<endl;

    system("pause");

}

void display()
{
    system("cls");
    cout << "====================Records====================" << endl
         << endl;

    for (int i = 0; i < list.length(); i++)
    {
        list.students()[i].display();
    }

    cout << endl
         << endl;
    system("pause");
}

int getInt(string prompt)
{

    string input;
    bool valid = false;
    do
    {
        cout << prompt;
        cin >> input;
        try
        {
            stoi(input);
            valid = true;
        }
        catch (const std::exception &e)
        {
            std::cerr << "Input must be integer." << endl;
        }

    } while (!valid);
    getchar();
    return stoi(input);
}

float getFloat(string prompt)
{

    string input;
    bool valid = false;
    do
    {
        cout << prompt;
        cin >> input;
        try
        {
            stof(input);
            valid = true;
        }
        catch (const std::exception &e)
        {
            std::cerr << "Input must be a float." << endl;
        }

    } while (!valid);
    getchar();
    return stof(input);
}
