//MARK CABALONA         BSCS - 2A
// MACHINE PROBlEM 2

// ===========================PARALLEL ARRAYS APPROACH==================

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#define MAX 2
#define STR_MAX 65


char *get_string(char *prompt); //this accepts strings unil \n
float get_float(char *prompt);  // accepts only floating point inputs

void getRecs(char name[MAX][STR_MAX], float g1[MAX], float g2[MAX], float g3[MAX]); //prompts user to enter their infos MAX times
void aver(float g1[MAX], float g2[MAX], float g3[MAX], float average[MAX],int isPassed[MAX]);    //computes the average of of each user
void display(char name[MAX][STR_MAX], float g1[MAX], float g2[MAX], float g3[MAX], float average[MAX], int isPassed[MAX]); //displays the infos


int main(void)
{
    //defining local variables
    char name[MAX][STR_MAX]; // array of strings with STR_MAX number of chars
    float g1[MAX], g2[MAX], g3[MAX], average[MAX];
    int isPassed[MAX];//holds boolean true - 1, false - 0 

    //get infos from user
    getRecs(name, g1,g2,g3);
    //compute average
    aver(g1,g2,g3,average,isPassed);
    //display it to the screen
    display(name,g1,g2,g3,average,isPassed);
}

void getRecs(char name[MAX][STR_MAX], float g1[MAX], float g2[MAX], float g3[MAX])
{
    //get inputs MAX times
    for (int i = 0; i < MAX; i++)
    {
        //infos of every students will be stored in different arrays with the same index
        strcpy(name[i], get_string("Name: ")); //storing name of user in name array in index i
        //storing grade # 1 of the same user in g1 array in index i
        g1[i] = get_float("Enter Grade #1: ");
        //storing grade # 2 of the same user in g2 array in index i
        g2[i] = get_float("Enter Grade #2: ");
        //storing grade # 3 of the same user in g3 array in index i
        g3[i] = get_float("Enter Grade #3: ");
    }
    //pauses the execution of the program until a key is pressed
    system("pause");
    //clears the screen
    system("cls");
}


void aver(float g1[MAX], float g2[MAX], float g3[MAX], float average[MAX],int isPassed[MAX])
{
    for (int i = 0; i < MAX; i++)
    {                                             //computes average MAX times
        average[i] = (g1[i] + g2[i] + g3[i]) / 3; //adds grades stored in g1,g2,g3 arrays and store it in average array with index i
        //if average is greater than or equal to 75 then isPassed is set to true(1), otherwise it is set to false(0)
        isPassed[i] = average[i] >= 75 ? 1 : 0; //1 is true 0 is false,
    }
}


void display(char name[MAX][STR_MAX], float g1[MAX], float g2[MAX], float g3[MAX], float average[MAX], int isPassed[MAX])
{
    printf("   Name\t\tG1\tG2\tG3\tAVERAGE\tREMARKS\n"); //prints the header
    for (int i = 0; i < MAX; i++)                        //prints each record in the arrays
    {
        printf("%d  %.8s\t%.2f\t%.2f\t%.2f\t%.2f\t%s\n", i + 1, name[i], g1[i], g2[i], g3[i], average[i], isPassed[i] ? "Passed" : "Failed");
    }
    printf("\n\n\t\tYUN OH! PERFECT!\n");
    //pauses the execution of the program until a key is pressed
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
