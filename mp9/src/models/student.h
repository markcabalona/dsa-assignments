#ifndef STUDENT_H
#define STUDENT_H

#include <iostream>
using namespace std;

class Student
{
    public:
    int id;
    string lastName;
    string firstName;
    float grades[3];

    static Student fromRow(string row);
    string toRow();

    Student(int _id,string lname,string fname,int*_grades);
    Student();

};

#endif