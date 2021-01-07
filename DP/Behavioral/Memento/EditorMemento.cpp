#include "EditorMemento.h"
#include "Editor.h"

EditorMemento::EditorMemento(Editor* editor, const std::string& text, size_t x, size_t y, size_t sw)
:_editor(editor),
_text(text),
_x(x),
_y(y),
_selectionWidth(sw) {}

void EditorMemento::Restore()
{
    if(_editor){
        _editor->SetText(_text);
        _editor->SetX(_x);
        _editor->SetY(_y);
        _editor->SetSelectionWidth(_selectionWidth);
        return;
    }
    throw "null pointer";
}