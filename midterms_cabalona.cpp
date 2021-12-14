/*

    MARK CABALONA                   MIDTERMS
    BSCS - 2A

*/


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
        Record _records[MAX_RECORD];
        int _last;
        void save();
        void retrieve();
        int locate(string *fname, int *id);
        void makeNull()
        {
            _last = -1;
        }
        bool isFull()
        {
            return _last == (MAX_RECORD - 1);
        }

    public:
        int insert(Record);
        int generateId();
        int deleteRecord(int id);
        void display(int id);
        void displayAll();

        ArrayRecordList()
        {
            makeNull();
            retrieve();
        }
        ~ArrayRecordList()
        {
            save();
        }
    };
} // namespace ListArrayImplementation

namespace PointerArray
{
    typedef struct RecordNode
    {
        Record val;
        RecordNode *next = nullptr;
    } RecordList;

    class PointerRecordList
    {
    private:
        RecordList *_records;
        int _length;
        void save();
        void retrieve();
        bool locate(string *fname, int *id);
        void makeNull()
        {
            _records = new RecordList;
            _records = nullptr;
            _length = 0;
        }

    public:
        int insert(Record);
        int generateId();
        int deleteRecord(int id);
        void display(int id);
        void displayAll();

        PointerRecordList()
        {
            makeNull();
            retrieve();
        }
        ~PointerRecordList()
        {
            save();
        }
    };
} // namespace PointerArray

//item 5
string getPincode();
int main(int argc, char const *argv[])
{
    PointerArray::PointerRecordList myList;
    Record test;

    test.id = myList.generateId();
    cout<<"Hello"<<endl;
    test.fullName = "gfoo";
    test.quiz1 = 75;
    test.quiz2 = 75;
    test.quiz3 = 75;
    cout<<"Hello"<<endl;
    myList.insert(test);
    myList.display(test.id);
    cout<<endl;

    return 0;
}

//item 1
void ListArray::ArrayRecordList::retrieve()
{
    FILE *fp = fopen(FILEPATH, "r");
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

    return temp;
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
    cout << "called insert func" << endl;
    if (locate(&newRec.fullName, nullptr) >= 0)
    {
        cout << "Duplicate Name" << endl;
        return -1;
    }
    else if (isFull())
    {
        cout << "Full list" << endl;
        return -1;
    }

    _last++;
    if (_last == 0)
    {
        cout << "First insertion" << endl;
        _records[_last] = newRec;
        return 0;
    }
    else
    {
        for (int i = 0; i <= _last; i++)
        {
            if (newRec.id < _records[i].id)
            {
                cout << "New first " << _last + 1 << endl;
                for (int j = _last; j >= i; j--)
                {
                    _records[j] = _records[j - 1];
                }
                cout << "Inserted this many times " << _last + 1 << endl;
                _records[i] = newRec;
                return 0;
            }
        }
        cout << "Inserted this many times " << _last + 1 << endl;
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

//item 2
void PointerArray::PointerRecordList::retrieve()
{
    FILE *fp = fopen(FILEPATH, "r");
    char token[256];
    while (fgets(token, 256, fp))
    {
        insert(Record::fromRow(string(token)));
    }
    fclose(fp);
}

void PointerArray::PointerRecordList::save()
{
    FILE *fp = fopen(FILEPATH, "w");
    RecordNode *temp_head = new RecordNode;
    temp_head = _records;
    while (temp_head != nullptr)
    {
        fprintf(fp, temp_head->val.toRow().c_str());
        fprintf(fp, "\n");
        temp_head = temp_head->next;
    }
    fclose(fp);
}

int PointerArray::PointerRecordList::generateId()
{
    srand((unsigned)time(0));
    int temp = 1000 + rand() % 9000;
    while (locate(nullptr, &temp))
    {
        temp = 1000 + rand() % 9000;
    }

    return temp;
}

bool PointerArray::PointerRecordList::locate(string *fname, int *id)
{
    RecordNode *temp = new RecordNode;
    temp = _records;
    if (fname != nullptr)
    {
        while (temp != nullptr)
        {
            if (temp->val.fullName.compare(*fname) == 0)
            {
                return true;
            }
            temp = temp->next;
        }
    }
    else
    {
        while (temp != nullptr)
        {
            if (temp->val.id == *id)
            {
                return true;
            }
            temp = temp->next;
        }
    }
    return false;
}

int PointerArray::PointerRecordList::insert(Record newRec)
{
    cout << "called insert func" << endl;
    if (locate(&newRec.fullName, nullptr))
    {
        cout << "Duplicate Name" << endl;
        return -1;
    }

    RecordNode *newNode = new RecordNode;
    newNode->val = newRec;
    newNode->next = nullptr;

    if (_records == nullptr)
    {
        _records = newNode;
        return 0;
    }
    else
    {
        RecordNode *temp_head = new RecordNode;
        RecordNode *prev = new RecordNode;
        temp_head = prev = _records;
        while (temp_head != nullptr && (temp_head->val.fullName.compare(newNode->val.fullName) < 0))
        {
            prev = temp_head;
            temp_head = temp_head->next;
        }
        if (temp_head == _records) //if new node is to be inserted in the first index
        {
            newNode->next = temp_head;
            _records = newNode;
        }
        else
        {
            prev->next = newNode;
            newNode->next = temp_head;
        }
    }
    _length++;
    return 0;
}

void PointerArray::PointerRecordList::display(int id)
{
    RecordNode *temp_head = new RecordNode;
    temp_head = _records;
    while (temp_head != nullptr)
    {
        if (id == temp_head->val.id)
        {
            float average = (temp_head->val.quiz1 + temp_head->val.quiz2 + temp_head->val.quiz3) / 3;
            string remarks = (average < 75) ? "Failed" : "Passed";
            cout << temp_head->val.id << "\t"
                 << temp_head->val.fullName << "\t\t"
                 << temp_head->val.quiz1 << "\t"
                 << temp_head->val.quiz2 << "\t"
                 << temp_head->val.quiz3 << "\t"
                 << average << "\t"
                 << remarks;
        }
        temp_head = temp_head->next;
    }
}

int PointerArray::PointerRecordList::deleteRecord(int id)
{
    if (!locate(nullptr, &id))
    {
        return -1;
    }

    RecordNode *temp = new RecordNode;
    RecordNode *prev = new RecordNode;
    temp = prev = _records;

    while (temp != nullptr && (temp->val.id != id))
    {
        prev = temp;
        temp = temp->next;
    }

    if (temp == _records)
    {
        _records = temp->next;
    }
    else
    {
        prev->next = temp->next;
        delete (temp);
    }
    _length--;
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
    string row = (to_string(id) + "," + fullName + "," + to_string(quiz1) + "," + to_string(quiz2) + "," + to_string(quiz3));
    return row;
}