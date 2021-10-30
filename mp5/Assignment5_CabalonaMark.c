/*
MARK REYES CABALONA             Assignment 5        October 12, 2021
BSCS - 2A

=======================LIST======================

*/
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#define MAX 5
#define STR_MAX 255
#define FILEPATH "db/records.dbf"

typedef struct
{
    char name[STR_MAX];
    float g1, g2, g3;
} REC;

typedef struct
{
    REC stud[MAX];
    int last;
} LIST;

LIST L;

//file handling functions
void retrieve();
void save();

//list operations
int locate(char *name); //returns the index of L.stud[name] if name is existing, returns -1 otherwise
void makeNull();        //makes L.list = -1
void display();
int isFull();        //returns 1 for true, 0 for false
int isEmpty();       //returns 1 for true, 0 for false
int insert(REC rec); //returns 0 on successful insertion, returns -1 otherwise
void del(char *name);
int update(char *name); //returns 0 on successful update, returns -1 otherwise

void menu();

//utilities
char *get_string(); //returns a pointer to a string
int get_int();      //returns an integer input from user, this filters nonnumeric characters
float get_float();  //same as get_int

void getRec(REC *rec); //assign values to REC parameter, returns when name is already existing
int main(void)
{
    makeNull();
    retrieve();

    while (1)
    {
        menu();
        int response = 0;
        do
        {
            response = get_int("\nSelect (1 - 5): ");
        } while (response < 1 || response > 5);

        switch (response)
        {
        case 1:
        {
            REC rec;
            getRec(&rec);
            if (insert(rec) < 0)
            {
                //check what error message will display

                if (isFull())
                {
                    printf("\nList is full.\n");
                }
                else
                {
                    printf("\n%s already has a record.\n", rec.name);
                }

                break;
            }
            printf("Record Added.\n");
            break;
        }
        case 2:
        {
            char *name = get_string("Enter Name: ");

            if (update(name) < 0)//on error
            {
                printf("\n%s has no record in our system.\n", name);
                break;
            }
            else//on success
            {
                printf("\nUpdate successfully.\nChoose display option to see %s's new record.\n", name);
            }
            free(name);
            break;
        }
        case 3:
        {
            char *name = get_string("Enter name to be deleted: ");
            del(name);
            free(name);
            break;
        }
        case 4:
        {
            system("cls");
            display();
            break;
        }
        case 5:
        {
            system("cls");
            save();
            exit(1);
            break;
        }
        default:
            break;
        }

        printf("\n\n");
        system("pause");
        system("cls");
    }
}
void getRec(REC *rec)
{
    strcpy(rec->name, get_string("\nEnter Name: "));
    if (locate(rec->name) > -1)
    {
        return;
    }
    rec->g1 = get_float("Enter Grade #1: ");
    rec->g2 = get_float("Enter Grade #2: ");
    rec->g3 = get_float("Enter Grade #3: ");
}

void menu()
{
    char *options[STR_MAX] = {"Insert", "Update", "Delete", "Display", "Exit"};
    int optionsCount = 5;

    printf("\tMENU\n\n");
    for (int i = 0; i < optionsCount; i++)
    {
        printf("%d.) %s\n", i + 1, options[i]);
    }
}

void makeNull()
{
    L.last = -1;
}

void display()
{
    if (isEmpty())
    {
        printf("no records found.\n");
        return;
    }
    float ave;

    printf("Name\t  G1\tG2\tG3\tAverage\tRemarks\n\n");
    for (int i = 0; i < L.last + 1; i++)
    {
        ave = (L.stud[i].g1 + L.stud[i].g2 + L.stud[i].g3) / 3;
        printf("%s\t%6.2f\t%6.2f\t%6.2f\t%.2f\t%s\n", L.stud[i].name, L.stud[i].g1, L.stud[i].g2, L.stud[i].g3, ave, ave >= 75 ? "Passed" : "Failed");
    }
}

int isFull()
{
    return L.last + 1 == MAX;
}

int isEmpty()
{
    return L.last == -1;
}

int locate(char *name) //returns the index if name is in the List, returns -1 if not
{
    for (int i = 0; i < L.last + 1; i++)
    {
        if (strcmp(L.stud[i].name, name) == 0)
        {
            return i;
        }
    }
    return -1;
}

int insert(REC rec)
{
    if (isFull() || locate(rec.name) >= 0)
    {
        //printf("\nList is full.\n");
        return -1;
    }
    // else if ()
    // {
    //     printf("\n%s already has a record.\n", rec.name);
    //     return -1;
    // }

    else
    {
        L.last++;
        if (L.last == 0)
        {
            L.stud[L.last] = rec;
        }
        else
        {
            for (int i = 0; i <= L.last; i++)
            {
                if (strcasecmp(rec.name, L.stud[i].name) < 0)
                {
                    for (int j = L.last; j >= i; j--)
                    {
                        L.stud[j] = L.stud[j - 1];
                    }
                    L.stud[i] = rec;
                    return 0;
                }
            }
            L.stud[L.last] = rec;
        }

        return 0;
    }
}

void del(char *name)
{
    if (isEmpty())
    {
        printf("\nNo records found.\n");
    }
    else
    {
        int index = locate(name);
        if (index < 0)
        {
            printf("\n%s\'s record not found\n", name);
        }
        else
        {
            for (int i = index; i < MAX; i++)
            {
                if (i == MAX - 1)
                    continue;
                L.stud[i] = L.stud[i + 1];
            }
            L.last--;
            printf("\nRecord deleted.\n");
        }
    }
}

int update(char *name)
{
    int index = locate(name);
    if (index < 0)
    {
        return -1;
    }

    L.stud[index].g1 = get_float("Enter new score for Quiz 1: ");
    L.stud[index].g2 = get_float("Enter new score for Quiz 2: ");
    L.stud[index].g3 = get_float("Enter new score for Quiz 3: ");

    return 0;
}

//file handling functions
void retrieve()
{
    FILE *fp = fopen(FILEPATH, "r");

    if (!fp)
    { //if the dbf is not found, make a new one in a new directory called db
        fclose(fp);
        system("mkdir db");
        fp = fopen(FILEPATH, "w");
        fclose(fp);
        printf("Error opening dbfile.\nNew dbfile is created inside a new directory 'db'.\n");
        system("pause");
        system("cls");
        return;
    }
    else
    { //if dbf reading is successfull populate the List
        REC tempRec;

        while (fscanf(fp, "%[^,],%f,%f,%f\n", tempRec.name, &tempRec.g1, &tempRec.g2, &tempRec.g3) != EOF)
        {
            insert(tempRec); //insert the data from dbf to the list
        }
        fclose(fp); //close the file
    }
}
void save()
{
    FILE *fp = fopen(FILEPATH, "w");
    for (int i = 0; i < L.last + 1; i++)
    {
        fprintf(fp, "%s,%.2f,%.2f,%.2f\n", L.stud[i].name, L.stud[i].g1, L.stud[i].g2, L.stud[i].g3);
    }
    fclose(fp);
}

//utilities
char *get_string(char *prompt)
{
    char *temp = (char *)malloc(STR_MAX * sizeof(char)); //allocates memory for a string (char* temp)
    printf("%s", prompt);
    scanf("%[^\n]s", temp); //accepts string input until \n
    getchar();              //flushes the buffer
    return temp;            //return the pointer to a string inputted by the user
}

int get_int(char *prompt)
{
    char buff[STR_MAX];
    int isvalid, num;
    do
    {
        printf("%s",prompt);
        isvalid = scanf("%d",&num);
        fgets(buff,STR_MAX,stdin);
    } while (!isvalid);

    return num;
}

float get_float(char *prompt)
{
    char buff[STR_MAX];
    int isvalid;
    float num;
    do
    {
        printf("%s",prompt);
        isvalid = scanf("%f",&num);
        fgets(buff,STR_MAX,stdin);
    } while (!isvalid);

    return num;
}


/*
#include <iostream>
#include "models/candidate.h"
#include "list_providers/candidateList.h"
#include <map>
#include <list>
#include <iterator>

using namespace std;

int main(void)
{
    CandidateListProvider provider;

    cout << "Hello World";

    string name, pos, pw, id;

    cout << "Enter name: ";
    cin >> name;
    cout << "Enter pos: ";
    cin >> pos;
    cout<<"Enter id: ";
    cin>>id;
    cout<<"Enter pw: ";
    cin>>pw;

    provider.insert(Candidate(pos,name,id,pw));

    cout<<provider.list().candidates[provider.list().last].name<<endl;

    // cout<<"Enter voterId: "<<provider.list().candidates[provider.list().last].voterId<<endl;
    // cout<<"Enter voteCount: "<<provider.list().candidates[provider.list().last].voteCount<<endl;

    
    // cout << provider.list().last;

    cout << "GoodBye World";
}

*/