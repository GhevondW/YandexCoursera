#include <iostream>
#include "Element.h"
#include "ElemReaderJSON.h"
#include "ElemReaderXML.h"
#include "ElemWriterJSON.h"
#include "ElemWriterXML.h"
using namespace std;

int main()
{
    cout << "Adapter" << endl;

    {   
        ElemReaderJSON reader{"json.txt"};
        ElemWriterXML writter{"json_to_xml.txt"};
        while (reader.HasNext())
        {
            auto elem = reader.ReadNext();
            writter.AcceptElement(elem);
        }

        writter.Close();
    }
    return 0;
}