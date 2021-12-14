#include <iostream>
#include <time.h>
#include <conio.h>
#include <sstream>
#include <vector>
#include <string.h>

#define MAX_RECORD 5
#define FILEPATH "dsa.dbf"

using namespace std;
class Record
{
public:
    int id;
    string fullName;
    int quiz1, quiz2, quiz3;

    static Record fromRow(string row);
    string toRow();
};

namespace ListArray
{
    class ArrayRecordList
    {
    private:
        Record *_records;
        void save();
        void retrieve();
        void freeList();
        int _last;
        int locate(string *fname, int *id);
        void makeNull()
        {
            _last = -1;
            _records = (Record *)malloc(_last + 1 * sizeof(Record));
        }

    public:
        int insert(Record);
        int generateId();
        int deleteRecord(int id);
        void display(int id);
        void displayAll();

        ArrayRecordList()
        {
            cout<<"Welcome";
            makeNull();
            retrieve();
        }
        ~ArrayRecordList()
        {
            // freeList();
            save();
        }
    };
} // namespace ListArrayImplementation

namespace ListPointer
{

} // namespace ListPointerImplementation

//item 5
string getPincode();
int main(int argc, char const *argv[])
{
    ListArray::ArrayRecordList myList;

    Record test;

    test.id = 0;
    test.fullName = "foo";
    test.quiz1 = 75;
    test.quiz2 = 75;
    test.quiz3 = 75;

    myList.insert(test);
    myList.display(test.id);
    return 0;
}

void ListArray::ArrayRecordList::retrieve()
{
    FILE *fp = fopen(FILEPATH, "r+");
    char token[256];
    while (fgets(token, 256, fp))
    {
        insert(Record::fromRow(string(token)));
    }
    fclose(fp);
}

void ListArray::ArrayRecordList::save()
{
    FILE *fp = fopen(FILEPATH, "w");
    for (int i = 0; i <= _last; i++)
    {
        fprintf(fp, _records[i].toRow().c_str());
        fprintf(fp, "\n");
    }
    fclose(fp);
}

int ListArray::ArrayRecordList::generateId()
{
    srand((unsigned)time(0));
    int temp = 1000 + rand() % 9000;
    while (locate(nullptr, &temp) >= 0)
    {
        temp = 1000 + rand() % 9000;
    }

    return 1;
}

int ListArray::ArrayRecordList::locate(string *fname, int *id)
{

    if (fname != nullptr)
    {
        for (int i = 0; i <= _last; i++)
        {
            if ((*fname).compare(_records[i].fullName) == 0)
            {
                return i;
            }
        }
    }
    else
    {
        for (int i = 0; i <= _last; i++)
        {
            if (*id == _records[i].id)
            {
                return i;
            }
        }
    }
    return -1;
}

int ListArray::ArrayRecordList::insert(Record newRec)
{
    if (locate(&newRec.fullName, nullptr) > 0)
    {
        return -1;
    }

    _last++;
    _records = (Record *)realloc(_records, (_last + 1) * sizeof(Record));
    if (_last == 0)
    {
        _records[_last] = newRec;
        return 0;
    }
    else
    {
        for (int i = 0; i <= _last; i++)
        {
            if (newRec.id < _records[i].id)
            {
                for (int j = _last; j >= i; j--)
                {
                    _records[j] = _records[j - 1];
                }
                _records[i] = newRec;
                return 0;
            }
        }
        _records[_last] = newRec;
    }
    return 0;
}

void ListArray::ArrayRecordList::display(int id)
{
    for (int i = 0; i <= _last; i++)
    {
        if (id == _records[i].id)
        {
            float average = (_records[i].quiz1 + _records[i].quiz2 + _records[i].quiz3) / 3;
            string remarks = (average < 75) ? "Failed" : "Passed";
            cout << _records[i].id << "\t"
                 << _records[i].fullName << "\t\t"
                 << _records[i].quiz1 << "\t"
                 << _records[i].quiz2 << "\t"
                 << _records[i].quiz3 << "\t"
                 << average << "\t"
                 << remarks;
        }
    }
}

int ListArray::ArrayRecordList::deleteRecord(int id)
{
    int index = locate(nullptr, &id);
    if (index < 0)
    {
        return -1;
    }
    else
    {
        for (int i = index; i <= _last; i++)
        {
            if (i == _last - 1)
                continue;
            _records[i] = _records[i + 1];
        }
        _last--;
        printf("\nRecord deleted.\n");
    }
    return 0;
}

//item 5
string getPincode()
{
    int code = 69;
    cout << "Enter PIN (4-digit integer): ";

    int i = 0;
    char pw[7]; // = (char *)malloc(i * sizeof(char));
    char temp;
    while ((temp = getch()) != 13 || i == 0)
    {
        if ((temp >= '0' && temp <= '9') && i < 4)
        {
            if (temp != '\b')
            {
                pw[i] = temp + code;
                putchar('*');
                i++;
            }
        }
        else if (temp == '\b' && i > 0)
        {
            pw[i] = '\0';
            i--;
            printf("\b  \b\b");
        }
    }
    pw[i] = '\0';

    return string(pw);
}

Record Record::fromRow(string row)
{
    Record rec;

    char delimiter = ',';

    istringstream split(row);
    vector<string> tokens;
    for (string col; getline(split, col, delimiter); tokens.push_back(col))
        ;

    for (int colNum = 0; colNum < 5; colNum++)
    {
        switch (colNum)
        {
        case 0:
        {
            rec.id = stoi(tokens[colNum]);
            break;
        }
        case 1:
        {
            rec.fullName.assign(tokens[colNum]);
            break;
        }
        case 2:
        {
            rec.quiz1 = stoi(tokens[colNum]);
            break;
        }
        case 3:
        {
            rec.quiz2 = stoi(tokens[colNum]);
            break;
        }
        case 4:
        {
            rec.quiz3 = stoi(tokens[colNum]);
            break;
        }
        default:
            break;
        }
    }

    return rec;
}

string Record::toRow()
{
    string row = (to_string(id) + "," + fullName +"," + to_string(quiz1)+"," + to_string(quiz2) +"," + to_string(quiz3));
    return row;
}