//MARK CABALONA         BSCS - 2A
// MACHINE PROBlEM 3

// ===========================STRUCT APPROACH==================

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#define MAX 2
#define STR_MAX 65

typedef struct
{
    char name[STR_MAX];
    float g1;
    float g2;
    float g3;
    float average;
    int isPassed;//holds boolean true - 1, false - 0 
} student_recs;

char *get_string(char *prompt);
float get_float(char *prompt);

void getRecs(student_recs studs[MAX]);
void display(student_recs studs[MAX]);

int main(void)
{
    //declaration of local variable
    student_recs studs[MAX];
    getRecs(studs);
    display(studs);
}

void getRecs(student_recs studs[MAX])
{
    for (int i = 0; i < MAX; i++)
    {
        strcpy(studs[i].name, get_string("Name: "));
        //get_float filters non numeric chars
        studs[i].g1 = get_float("Enter Grade #1: ");
        studs[i].g2 = get_float("Enter Grade #2: ");
        studs[i].g3 = get_float("Enter Grade #3: ");
        studs[i].average = (studs[i].g1 + studs[i].g2 + studs[i].g3) / 3.0;
        studs[i].isPassed = studs[i].average >= 75 ? 1 : 0; //1 is true, 0 is false
    }
    system("pause");
    system("cls");
}

void display(student_recs studs[MAX])
{
    printf("   Name\t\tG1\tG2\tG3\tAVERAGE\tREMARKS\n");
    for (int i = 0; i < MAX; i++)
    {
        printf("%d  %.8s\t%.2f\t%.2f\t%.2f\t%.2f\t%s\n", i + 1, studs[i].name, studs[i].g1, studs[i].g2, studs[i].g3, studs[i].average, studs[i].isPassed ? "Passed" : "Failed");
    }
    printf("\n\n\t\tYUN OH! PERFECT!\n");
    system("pause");
}

char *get_string(char *prompt)
{
    char *temp = (char *)malloc(STR_MAX * sizeof(char)); //allocates memory for a string (char* temp)
    printf("%s", prompt);
    scanf("%[^\n]s", temp); //accepts string input until \n
    getchar();              //flushes the buffer
    return temp;            //return the pointer to a string inputted by the user
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
