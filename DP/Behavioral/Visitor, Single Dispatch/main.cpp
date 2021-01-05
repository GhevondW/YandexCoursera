#include <iostream>
#include "IVisitor.h"
using namespace std;

#include <vector>

int main()
{
    cout<<"Visitor"<<endl;

    vector<Shape*> arr;
    arr.push_back(new Rect{});
    arr.push_back(new Ellipse{});
    arr.push_back(new Rect{});
    arr.push_back(new Circle{});
    arr.push_back(new Rect{});
    arr.push_back(new Triangle{});
    

    XMLVisitor visitor{};

    for (size_t i = 0; i < arr.size(); i++)
    {
        arr[i]->Accept(&visitor);
    }
    

    for (size_t i = 0; i < arr.size(); i++)
    {
        delete arr[i];
    }
    arr.clear();

    return 0;
}