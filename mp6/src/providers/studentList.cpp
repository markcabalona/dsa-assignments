#include "studentList.h"
#include <string.h>

Student::Student(string name)
{
    _name = name;
}

void Student::display()
{
    cout << "\n============================================\n"
         << endl;
    cout << "   Name: " << _name << endl
         << endl;
    float total = 0;
    for (int j = 0; j < _gradeCount; j++)
    {
        total += _grades[j];
        cout << "   Grade #" << j + 1 << ": " << _grades[j] << "\n";
    }
    float ave;
    cout << "\n   Average:  " << (ave = (total / _gradeCount)) << "\n";
    cout << "   Remarks:  " << (ave < 75 ? "Failed" : "Passed") << endl;
}

void Student::setGrades(float *grades, int gradeCount)
{
    _gradeCount = gradeCount;
    for (int i = 0; i < gradeCount; i++)
    {
        _grades[i] = grades[i];
    }
}
Student::Student()
{
}
string Student::name()
{
    return _name;
}

int Student::gradeCount()
{
    return _gradeCount;
}

float *Student::grades()
{
    return _grades;
}

StudentList::StudentList()
{
    makeNull();
    retrieve();
}

StudentList::~StudentList()
{
    save();
}

Student *StudentList::students()
{
    return list;
}

void StudentList::makeNull()
{
    last = -1;
}

int StudentList::length()
{
    return last + 1;
}

int StudentList::insert(Student stud)
{
    if (isFull())
    {
        return FULL;
    }
    else if (locate(stud.name()) >= 0)
    {
        return UNPROCESSABLE_ENTITY;
    }

    last++;
    if (last == 0)
    {
        list[last] = stud;
    }
    else
    {
        for (int i = 0; i <= last; i++)
        {
            if (stud.name().compare(list[i].name()) < 0)
            {
                for (int j = last; j >= i; j--)
                {
                    list[j] = list[j - 1];
                }
                list[i] = stud;
                return 0;
            }
        }
        list[last] = stud;
    }

    return SUCCESS;
}

void StudentList::update(int index, float *grades, int gradeCount)
{
    list[index].setGrades(grades, gradeCount);
}

int StudentList::remove(string name)
{
    int index = locate(name);

    if (index == NOT_FOUND)
    {
        if (isEmpty())
        {
            return EMPTY;
        }
        return NOT_FOUND;
    }
    else
    {
        for (int i = index; i < last; i++)
        {
            list[index] = list[index + 1];
        }
        last--;
        return SUCCESS;
    }
}

int StudentList::locate(string name)
{
    for (int i = 0; i <= last; i++)
    {
        if (name.compare(list[i].name()) == 0)
        {
            return i;
        }
    }
    return NOT_FOUND;
}

bool StudentList::isFull()
{
    return (last == MAX_STUDENT - 1);
}

bool StudentList::isEmpty()
{
    return (last == -1);
}

void StudentList::retrieve()
{
    FILE *fp = fopen(FILEPATH, "r");
    if (!fp)
    {
        return;
    }
    char buff[STR_MAX];

    while (!feof(fp))
    {
        fgets(buff, STR_MAX, fp); // get a row

        // parse row
        char *tokens = strtok(buff, ",");
        Student tempStud = Student(tokens); // get the name
        int gradeCount = 0;
        float *tempGrades = (float *)malloc(gradeCount * sizeof(float));
        tokens = strtok(NULL, ","); // proceed to next column
        while (tokens != NULL)
        {
            gradeCount++;
            tempGrades = (float *)realloc(tempGrades, gradeCount * sizeof(float)); // allocate more memory
            tempGrades[gradeCount - 1] = stof(tokens);
            tokens = strtok(NULL, ","); // get next col
        }
        tempStud.setGrades(tempGrades, gradeCount);
        if (insert(tempStud) == FULL)
        {
            break;
        };
        free(tempGrades); // free allocated memory in tempGrades
    }
    fclose(fp);
}

void StudentList::save()
{
    FILE *fp = fopen(FILEPATH, "w");
    for (int i = 0; i <= last; i++)
    {
        fprintf(fp, "%s", list[i].name().c_str());
        for (int j = 0; j < list[i].gradeCount(); j++)
        {
            fprintf(fp, ",%.2f", list[i].grades()[j]);
        }

        if (i < last)
            fprintf(fp, "\n");
    }
    fclose(fp);
}
