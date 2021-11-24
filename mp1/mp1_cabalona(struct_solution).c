//MARK CABALONA         BSCS - 2A
// MACHINE PROBlEM 1

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
    int isPassed;
} student_recs;

student_recs studs[MAX];
char *get_string(char *prompt);
float get_float(char *prompt);

void getRecs();
void display();

int main(void)
{
    getRecs();
    display();
}

void getRecs()
{
    for (int i = 0; i < MAX; i++)
    {
        strcpy(studs[i].name, get_string("Name: "));
        //get_float filters alphabet characters
        studs[i].g1 = get_float("Enter Grade #1: ");
        studs[i].g2 = get_float("Enter Grade #2: ");
        studs[i].g3 = get_float("Enter Grade #3: ");
        studs[i].average = (studs[i].g1 + studs[i].g3 + studs[i].g3) / 3;
        studs[i].isPassed = studs[i].average >= 75 ? 1 : 0; //1 is true, 0 is false
    }
    system("pause");
    system("cls");
}

void display()
{
    printf("   Name\t\tG1\tG2\tG3\tAVERAGE\tREMARKS\n");
    for (int i = 0; i < MAX; i++)
    {
        printf("%d  %.8s\t%.2f\t%.2f\t%.2f\t%.2f\t%s\n", i + 1, studs[i].name, studs[i].g1, studs[i].g2, studs[i].g3, studs[i].average, studs[i].isPassed == 1 ? "Passed" : "Failed");
    }
    printf("\n\n\t\tYUN OH!\n");
    system("pause");
}

char *get_string(char *prompt)
{
    //whenever you call get_string you need to free the memory allocated by it
    char *temp = (char *)malloc(STR_MAX * sizeof(char));
    char *buff = malloc(sizeof(char));
    printf("%s", prompt);
    scanf("%[^\n]", temp);
    getchar();
    return temp;
}

float get_float(char *promt)
{
    //same logic as the get_int function above
    char *temp_str = NULL;

    do
    {
        temp_str = get_string(promt);
        if (strcmp(temp_str, "0") == 0)
        {
            break;
        }
    } while (atof(temp_str) == 0);

    float num = atof(temp_str);
    free(temp_str);
    return num;
}
