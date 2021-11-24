#include "listprovider.h"
#include "../db/dbhelper.h"
#include <iomanip>

StudentList::StudentList()
{
    makeNull();
    DbHelper();
}
StudentList::~StudentList()
{
    DbHelper::save_data(list);
    destroyList();
}
void StudentList::makeNull()
{
    list = new LIST;
    list = nullptr;
    _length = 0;
}
int StudentList::length()
{
    return _length;
}
void StudentList::insert(Student stud)
{
    struct node *newNode = new struct node;
    newNode->data = stud;
    newNode->next = nullptr;

    if (list == nullptr)
    {
        list = newNode;
        return;
    }
    else
    {
        struct node *temp = new struct node;
        struct node *prev = new struct node;
        temp = prev = list;
        while (temp != nullptr && (temp->data.lastName.compare(newNode->data.lastName) < 0))
        {
            prev = temp;
            temp = temp->next;
        }
        if (temp == list) //if new node is to be inserted in the first index
        {
            newNode->next = temp;
            list = newNode;
        }
        else
        {
            prev->next = newNode;
            newNode->next = temp;
        }
    }
    _length++;
}

void StudentList::display()
{
    struct node *temp = new struct node;
    temp = list;
    cout << setw(4) << "ID\t"
         << "LastName\t"
         << "FirstName\t  "
         << "Quiz 1\t  "
         << "Quiz 2\t  "
         << "Quiz 3\t"
         << "Remarks" << endl
         << endl;
    while (temp != NULL)
    {
        cout << setw(4) << temp->data.id
             << setw(4) << "\t" << temp->data.lastName
             << setw(8) << "\t" << temp->data.firstName << "\t";
        float ave = 0;
        for (int i = 0; i < 3; i++)
        {
            ave += temp->data.grades[i];
            cout << "\t" << setw(8) << fixed << temp->data.grades[i] << setprecision(2);
        }
        temp = temp->next;
        cout << "\t" << (ave < 75 ? "Failed" : "Passed") << endl;
    }
}

int StudentList::update(int id, int *new_grades)
{
    // if (!contains(id)) // not necessary because this is already checked in the ui
    // {
    //     return -1;
    // }
    struct node *temp = new struct node;
    temp = list;

    while (temp != nullptr && (temp->data.id != id))
    {
        temp = temp->next;
    }

    for (int i = 0; i < 3; i++)
    {
        temp->data.grades[i] = new_grades[i];
    }
}
int StudentList::remove(int id)
{
    if (!contains(id))
    {
        return -1;
    }

    struct node *temp = new struct node;
    struct node *prev = new struct node;
    temp = prev = list;

    while (temp != nullptr && (temp->data.id != id))
    {
        prev = temp;
        temp = temp->next;
    }

    if (temp == list)
    {
        list = temp->next;
    }
    else
    {
        prev->next = temp->next;
        delete (temp);
    }
    _length--;
    return 0;
}

bool StudentList::contains(int id)
{
    struct node *temp = new struct node;
    temp = list;
    while (temp != nullptr)
    {
        if (temp->data.id == id)
        {
            return true;
        }
        temp = temp->next;
    }
    return false;
}

void StudentList::destroyList()
{
    struct node *temp = new struct node;
    temp = list;
    while (temp != NULL)
    {
        delete (list);
        list = NULL;
        list = temp = temp->next;
    }
    delete (temp);
    temp = NULL;
    delete (list);
    list = NULL;
}