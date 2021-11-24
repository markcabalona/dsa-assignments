#ifndef UTILS_H
#define UTILS_H
#include "../providers/listprovider.h"
using namespace std;

class Utils{
    public:
        static int getInt(string prompt);
        static string getString(string prompt);
        static float getFloat(string prompt);
        static int getIntRange(string prompt,int min, int max);
        static void printHeader(string title);
        static int generateFourDigitId();
};

#endif