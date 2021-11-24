#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define STR_MAX 69

int get_int(char *prompt);
float get_float(char *prompt);
char *get_string(char *prompt);

int main(void)
{
    int i;
    float f;
    char *s;

    while (1)
    {
        //i = get_int("int");
        f = get_float("in:");
        //s = get_string("string");

        printf("out: %.2f\n",f);
    }
}

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
    float num;
    int isValid;
    char buff[STR_MAX];

    do
    {
        
        printf("%s", promt);
        isValid = scanf("%f", &num);
        printf("%d",isValid);
        
        
    } while (isValid != 1);

    return num;
    // char *temp_str = NULL; //declare variable for a string

    // do
    // {
    //     temp_str = get_string(promt);
    //     if (strcmp(temp_str, "0") == 0) //if input is 0 exit the loop
    //     {
    //         break;
    //     }
    //     //prompts user to enter float input while input is not a valit float
    // } while (atof(temp_str) == 0); //atof returns 0 if the string parameter cannot be converted to a float

    // float num = atof(temp_str); //convert the input to float(atof's parameter will always be a valid float)
    // free(temp_str);             //free the memory allocated to temp_str
    // return num;
}