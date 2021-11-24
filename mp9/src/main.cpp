/*
    Mark Reyes Cabalona                             November 24, 2021
    BSCS - 2A                                       12:27 PM
                ================== Machine Problem 4 LINKED LIST APPROACH ===================
*/

#include "providers/listprovider.h"
#include "screens/mainscreen.h"

//declared as extern in listProvider.h
StudentList List;

int main(int argc, char const *argv[])
{
    MainScreen screen = MainScreen();
    while (screen.isRunning())
    {
        switch (screen.menu())//menu returns enum {add,update,etc} (defined in mainscreen.h)
        {
        case ADD:
        {
            screen.addstudent();
            break;
        }
        case UPDATE:
        {
            screen.updateStudent();
            break;
        }
        case DELETE:
        {
            screen.deleteStudent();
            break;
        }
        case DISPLAY:
        {
            screen.displayStudents();
            break;
        }
        case EXIT:
        {
            screen.close();
            break;
        }
        default:
            break;
        }
    }

    system("pause");
    return 0;
}
