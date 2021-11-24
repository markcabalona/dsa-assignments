/*
MARK REYES CABALONA             Assignment 4
BSCS - 2A

=======================LIST======================

*/
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#define MAX 3
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
void makeNull();
void display();
int isFull();
int isEmpty();
int insert(REC rec);//returns 0 on successful insertion, returns -1 otherwise
void del(char *name);

void menu();

//utilities
char *get_string();
int get_int();
float get_float();

void getRec(REC *rec);
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
            response = get_int("Select (1 - 4): ");
        } while (response < 1 || response > 4);

        switch (response)
        {     
        case 1:
        {
            REC rec;
            getRec(&rec);
            if(insert(rec)==0){//check if insertion is success
                printf("Record Added.\n");
            }
            break;
        }
        case 2:
        {
            char *name = get_string("Enter name to be deleted: ");
            del(name);
            free(name);
            break;
        }
        case 3:
        {
            system("cls");
            display();
            break;
        }
        case 4:
        {
            system("cls");
            save();
            exit(1);
            break;
        }
        default:
            break;
        }

        system("pause");
        system("cls");
    }
}
void getRec(REC *rec)
{
    strcpy(rec->name, get_string("Enter Name: "));
    rec->g1 = get_float("Enter Grade #1: ");
    rec->g2 = get_float("Enter Grade #2: ");
    rec->g3 = get_float("Enter Grade #3: ");
}


void menu()
{
    printf("\tMENU\n\n");
    printf("1.) Insert\n");
    printf("2.) Delete\n");
    printf("3.) Display\n");
    printf("4.) Exit\n\n");
}

void makeNull()
{
    L.last = -1;
}

void display()
{
    if(isEmpty()){
        printf("no records found.\n");
        return;
    }
    float ave;

    printf("Name\t  G1\tG2\tG3\tAverage\tRemarks\n");
    for (int i = 0; i < L.last + 1; i++)
    {
        ave = (L.stud[i].g1 + L.stud[i].g2 + L.stud[i].g3) / 3;
        printf("%s\t%6.2f\t%6.2f\t%6.2f\t%.2f\t%s\n", L.stud[i].name, L.stud[i].g1, L.stud[i].g2, L.stud[i].g3,ave,ave>=75?"Passed":"Failed");
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


int locate(char *name)//returns the index if name is in the List, returns -1 if not
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
    if (isFull())
    {
        printf("List is full.\n");
        return -1;
    }
    else if (locate(rec.name) >= 0)
    {
        printf("%s already has a record.\n", rec.name);
        return -1;
    }
    
    else
    {
        L.last++;
        L.stud[L.last] = rec;
        return 0;
    }
}

void del(char *name)
{
    if(isEmpty())
    {
        printf("No records found.\n");
    }
    else
    {
        int index = locate(name);
        if (index < 0){
            printf("%s\'s record not found\n", name);
        }
        else
        {
            for (int i = index; i < MAX; i++)
            {
                if( i == MAX - 1) continue;
                L.stud[i] = L.stud[i + 1];
            }
            L.last--;
            printf("Record deleted.\n");
        }
    }
}

//file handling functions
void retrieve()
{
    FILE *fp = fopen(FILEPATH,"r");

    if(!fp){//if the dbf is not found, make a new one in a new directory called db
        fclose(fp);
        system("mkdir db");
        fp = fopen(FILEPATH,"w");
        fclose(fp);
        printf("Error opening dbfile.\nNew dbfile is created inside a new directory 'db'.\n");
        system("pause");
        system("cls");
        return;
    }
    else{//if dbf reading is successfull populate the List
        char buffer[STR_MAX];
        char* token;
        
        while(fgets(buffer,STR_MAX,fp)){//get a line until end of file
            REC tempRec;
            int col = 1;//column number
            token = strtok(buffer,",");
            while(token){//parse the line inside the buffer
                switch (col)
                {
                case 1:{//first column is for name
                    strcpy(tempRec.name,token);
                    
                    break;
                }
                case 2:{//2nd col is for g1
                    tempRec.g1 = atof(token);
                    break;   
                }
                case 3:{//3rd col is for g2
                    tempRec.g2 = atof(token);
                    break;
                }
                case 4:{//4th col is for g3
                    tempRec.g3 = atof(token);
                    break;
                }
                default:{
                    break;
                }
                }
                col++;
                token = strtok(NULL,",");
            }
            insert(tempRec);//insert the data from dbf to the list
        }
        fclose(fp);//close the file
    }
}
void save()
{
    FILE *fp = fopen(FILEPATH,"w");
    for(int i = 0; i < L.last + 1; i++){
        fprintf(fp,"%s,%.2f,%.2f,%.2f\n",L.stud[i].name,L.stud[i].g1,L.stud[i].g2,L.stud[i].g3);
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

int get_int(char *promt)
{
    char *temp_str = NULL; //declare variable for a string

    do
    {
        temp_str = get_string(promt);
        if (strcmp(temp_str, "0") == 0) //if input is 0 exit the loop
        {
            break;
        }
        //prompts user to enter float input while input is not a valit float
    } while (atoi(temp_str) == 0); //atof returns 0 if the string parameter cannot be converted to a float

    float num = atoi(temp_str); //convert the input to float(atof's parameter will always be a valid float)
    free(temp_str);             //free the memory allocated to temp_str
    return num;
}

float get_float(char *promt)
{
    char *temp_str = NULL; //declare variable for a string

    do
    {
        temp_str = get_string(promt);
        if (strcmp(temp_str, "0") == 0) //if input is 0 exit the loop
        {
            break;
        }
        //prompts user to enter float input while input is not a valit float
    } while (atof(temp_str) == 0); //atof returns 0 if the string parameter cannot be converted to a float

    float num = atof(temp_str); //convert the input to float(atof's parameter will always be a valid float)
    free(temp_str);             //free the memory allocated to temp_str
    return num;
}
