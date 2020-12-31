#include <iostream>
#include "Database.h"
using namespace std;

int main()
{
    cout<<"Singleton"<<endl;

    Database& db = Database::Get();

    db.Connect("localhost:8888");
    db.PrintConnectionString();

    Database& db2 = Database::Get();

    db2.PrintConnectionString(); 

    return 0;
}