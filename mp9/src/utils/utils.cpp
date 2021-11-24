#include "utils.h"
#include<time.h>

int Utils::getInt(string prompt)
{
    string input;
    bool valid = false;
    do
    {
        cout << prompt;
        cin >> input;
        cin.ignore();
        try
        {
            stoi(input);
            valid = true;
        }
        catch (const std::exception &e)
        {
            std::cerr << "Input must be integer." << endl;
        }

    } while (!valid);
    return stoi(input);
}
int Utils::getIntRange(string prompt, int min, int max)
{
    string input;
    bool valid = false;
    do
    {
        cout << prompt;
        cin >> input;
        cin.ignore();
        try
        {
            int int_input = stoi(input);
            if(int_input < min || int_input > max)
            {
                cout<<"Input must be between "<<min<<" and "<<max<<"."<<endl;
            }
            else
                valid = true;
        }
        catch (const std::exception &e)
        {
            std::cerr << "Input must be integer." << endl;
        }

    } while (!valid);
    return stoi(input);
}
string Utils::getString(string prompt)
{

    cout<<prompt;
    string input;
    getline(cin,input);
    return input;
}
float Utils::getFloat(string prompt)
{
    string input;
    bool valid = false;
    do
    {
        cout<<prompt;
        cin>>input;
        cin.ignore();
        try
        {
            stof(input);
            valid = true;
        }
        catch(const std::exception& e)
        {
            std::cerr << "Input must be Float."<<endl;
        }
        
    } while (!valid);
    return stof(input);
}
void Utils::printHeader(string title){
    cout<<"======================= "<<title<<" ======================="<<endl<<endl;
}

int Utils::generateFourDigitId(){
    srand((unsigned)time(0));
    int tempId = 1000 + rand() % 9000;
    while (List.contains(tempId))
    {
        tempId = 1000 + rand() % 9000;
    }
    return tempId;
}