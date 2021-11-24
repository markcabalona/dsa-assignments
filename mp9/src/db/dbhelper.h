#ifndef DBHELPER_H
#define DBHELPER_H
#include <iostream>
#define FILEPATH "../db/records.dbf"

#include "../models/student.h"
#include "../providers/listprovider.h"
using namespace std;

class DbHelper{
    private:
        static int fetch_data();
    public:
        DbHelper();
        static int save_data(LIST* list);
};

#endif