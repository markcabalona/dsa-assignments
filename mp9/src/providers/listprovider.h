#ifndef LISTPROVIDER_H
#define LISTPROVIDER_H

#include "../models/student.h"

typedef struct node{
    Student data;
    struct  node *next;
    
}LIST;

class StudentList{
    private:
        LIST *list;
        void makeNull();
        int _length;
        void destroyList();
    public:
        void insert(Student stud);
        void display();
        int update(int id,int* new_grades);
        int remove(int id);
        int length();
        bool contains(int id);
        StudentList();
        ~StudentList();
};

extern StudentList List;

#endif