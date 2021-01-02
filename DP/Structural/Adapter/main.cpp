#include <iostream>
#include "Element.h"
#include "ElemReaderJSON.h"
#include "ElemReaderXML.h"
using namespace std;

int main()
{
    cout << "Adapter" << endl;

{
    ElemReaderJSON reader{"json.txt"};
    while (reader.HasNext())
    {
        auto elem = reader.ReadNext();
        elem.Print();
    }
}
{   
    ElemReaderXML reader{"xml.txt"};
    while (reader.HasNext())
    {
        auto elem = reader.ReadNext();
        elem.Print();
    }
}
    return 0;
}