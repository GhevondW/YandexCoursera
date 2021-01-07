#include <iostream>
#include "Editor.h"
#include <vector>
using namespace std;

int main()
{
    cout<<"Memento"<<endl;
    
    std::vector<EditorMemento> history;

    Editor editor{};
    editor.SetText("text1");
    editor.SetX(1);
    editor.SetY(0);
    editor.SetSelectionWidth(1);

    history.push_back(editor.Save());
    editor.Print();

    editor.SetX(3);
    editor.SetSelectionWidth(2);

    history.push_back(editor.Save());
    editor.Print();

    editor.SetText("fffffffffffffffffffffffff");
    editor.SetX(5);
    editor.SetY(0);
    editor.SetSelectionWidth(5);
    
    history.push_back(editor.Save());
    editor.Print();

    cout<<"-----------------------Restore-----------------------"<<endl;

    history[0].Restore();
    editor.Print();

    history[1].Restore();
    editor.Print();

    return 0;
}