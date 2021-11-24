#ifndef STUDENT_LIST_H
#define STUDENT_LIST_H
#include <iostream>
using namespace std;
#define MAX_STUDENT 5

#define FULL -1
#define NOT_FOUND -404
#define EMPTY 204
#define UNPROCESSABLE_ENTITY 422
#define SUCCESS 0

#define FILEPATH "../db/student_records.dbf"
#define STR_MAX 256

class Student
{
private:
    string _name;
    float _grades[50];
    int _gradeCount;

public:
    string name();
    void display();
    float *grades();
    int gradeCount();
    void setGrades(float *grades, int gradeCount);
    Student(string name);
    Student();
};

class StudentList
{
private:
    Student list[MAX_STUDENT];
    int last;
    void makeNull();

public:
    bool isFull();
    bool isEmpty();
    Student *students();
    int length();
    int locate(string name);
    void retrieve();
    void save();
    int insert(Student stud);
    void update(int index, float* grades, int gradeCount);
    int remove(string name);
    StudentList();
    ~StudentList();
};

#endif