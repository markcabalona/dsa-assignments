#include"mainscreen.h"
#include"../utils/utils.h"


Screens MainScreen::menu(){
    system("cls");
    Utils::printHeader("Main Menu");
    string options[] = {"ADD","Update","Delete","Display","Exit"};
    for (int i = 0; i< 5; i++){
        cout<<i+1<<" .) "<<options[i]<<endl;
    }

    return Screens(Utils::getIntRange("Enter Option Number: ",1,5));
    

}
void MainScreen::addstudent(){
    system("cls");
    Utils::printHeader("Add Student");
    Student stud;
    stud.firstName.assign(Utils::getString("Enter First Name: "));
    stud.lastName.assign(Utils::getString("Enter Last Name: "));
    
    for (int i = 0 ; i < 3;i++){
        cout<<"Enter grade in quiz #"<<i+1<<": ";
        stud.grades[i] = Utils::getInt("");
    }
    stud.id = Utils::generateFourDigitId();
    List.insert(stud);
    
    cout<<"\nStudet Added!"<<endl;
    system("pause");
}
void MainScreen::updateStudent(){
    system("cls");
    Utils::printHeader("Update Student");
    int student_id = Utils::getInt("Enter Student Id: ");

    if(List.contains(student_id)){
        int new_grades[3];
        for (int i = 0; i< 3; i++){
            cout<< "Enter New Grade for Quiz #"<<i+1<<": ";
            new_grades[i] = Utils::getFloat("");
            cout<<endl;
        }
        List.update(student_id, new_grades);
        cout<<"Records of student with id \'"<<student_id<<"\' updated."<<endl;
    }
    else{
        cout<<"No student with id \'"<<student_id<< "\' found in the list."<<endl;
    }

    system("pause");

}
void MainScreen::deleteStudent(){
    system("cls");
    Utils::printHeader("Delete Student");
    int student_id = Utils::getInt("Enter Student Id: ");
    if(List.contains(student_id)){
        
        List.remove(student_id);
        cout<<"Records of student with id \'"<<student_id<<"\' deleted."<<endl;
    }
    else{
        cout<<"No student with id \'"<<student_id<< "\' found in the list."<<endl;
    }

    system("pause");
}
void MainScreen::displayStudents(){
    system("cls");
    Utils::printHeader("Student List");

    List.display();
    system("pause");

}
