#ifndef _EDITOR_MEMENTO_H_
#define _EDITOR_MEMENTO_H_

class Editor;

#include <utility>
#include <string>

class EditorMemento
{
private:
    Editor*     _editor{nullptr};
    std::string _text{};
    size_t      _x{};
    size_t      _y{};
    size_t      _selectionWidth{};
public:
    EditorMemento(/* args */) = default;
    EditorMemento(Editor*, const std::string&, size_t, size_t, size_t);
    ~EditorMemento() = default;

    void Restore();
};

#endif