#include "dbhelper.h"
#include <stdlib.h>


DbHelper::DbHelper(){
    fetch_data();
}

int DbHelper::fetch_data(){
    FILE* fp = fopen(FILEPATH, "r");
    if(!fp){
        cout<<"Error Opening Database."<<endl;
        return -1;
    }
    else{
        char token[256];
        while(fgets(token,256,fp)){
            
            List.insert(Student::fromRow(string(token)));
        }
        fclose(fp);
        return 0;
    }
}
int DbHelper::save_data(LIST *list){
    FILE* fp = fopen(FILEPATH, "w");
    struct node *temp = new struct node;
    temp = list;
    while (temp != nullptr)
    {
        fprintf(fp,"%s\n",temp->data.toRow().c_str());
        temp = temp->next;
    }
    fclose(fp);
    return 0;
}