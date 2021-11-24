#include "student.h"
#include <sstream>
#include <vector>
#include <string>

Student::Student(int _id, string lname, string fname, int *_grades)
{
    id = _id;
    lastName = lname;
    firstName = fname;
    for (int i = 0; i < 3; i++)
    {
        grades[i] = _grades[i];
    }
}

Student::Student() {}

Student Student::fromRow(string row)
{
    Student stud;

    char delimiter = ',';

    istringstream split(row);
    vector<string> tokens;
    for (string col; getline(split, col, delimiter); tokens.push_back(col));

    for (int colNum = 0; colNum < 6; colNum++)
    {
        switch (colNum)
        {
        case 0:
        {
            stud.id = stoi(tokens[colNum]);
            break;
        }
        case 1:
        {
            stud.lastName.assign(tokens[colNum]);
            break;
        }
        case 2:
        {
            stud.firstName.assign(tokens[colNum]);
            break;
        }
        case 3:
        {
            stud.grades[0] = stoi(tokens[colNum]);
            break;
        }
        case 4:
        {
            stud.grades[1] = stoi(tokens[colNum]);
            break;
        }
        case 5:
        {
            stud.grades[2] = stoi(tokens[colNum]);
            break;
        }
        default:
            break;
        }
    }

    return stud;
}

string Student::toRow()
{
    string row(to_string(id) + "," + lastName + "," + firstName);

    for (int i = 0; i < 3; i++)
    {
        row += ("," + to_string(grades[i]));
    }

    return row;
}
