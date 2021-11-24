#ifndef MAINSCREEN_H
#define MAINSCREEN_H

#include "../providers/listprovider.h"

typedef enum{
    ADD = 1,
    UPDATE = 2,
    DELETE = 3,
    DISPLAY = 4,
    EXIT = 5,
}Screens;


class MainScreen{
    private:
        bool _running;

    public:
        bool isRunning(){
            return _running;
        }
        Screens menu();
        void addstudent();
        void updateStudent();
        void deleteStudent();
        void displayStudents();
        void close(){
            _running = false;
        }
        MainScreen(){
            _running = true;
        };
        ~MainScreen(){}
};

#endif